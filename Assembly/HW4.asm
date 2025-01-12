.data

saveReg:	.word	0:10				# extra register space!
# NULL or 0 in tabToken prematurely terminates dumping
#   tabToken. Use blanks instead.
TOKEN:		.word 	0x20202020:3			# 2-word TOKEN & its TYPE
tabToken:	.word	0x20202020:60			# initializing with blanks
inBuf:		.space	80
space:		.asciiz		"             "
linePrompt:	.asciiz	"Enter a new input line. \n"
errorPrompt:	.asciiz	"An error has occurred. \n"	
tabTokenHeader:	.asciiz "  TOKEN        TYPE\n"
error:		.asciiz	"Double Definition Error"
hex:		.asciiz	"0x"
symTab:		.word	0:40
symTabHead:	.asciiz	"Token              Value          Status     \n"
dashLine:	.asciiz	"---------------------------------------------\n"
tempNewLine:	.asciiz	"\n"
.text

	li	$s4, 0x400		# $s4 = LOC
	li	$t7, 0			# symTab index
newline:
	jal	getline			# jumps to getLine function
	
	li	$t5,0			# inbuf index
	li	$a3,0			# tabToken index

	# State table driver
	la	$s1, Q0			# Q0 initial state
st_driver:	lw	$s2, 0($s1)	
	jalr	$v1, $s2		# execute action

	sll	$s0, $s0, 2		# T << 2
	add	$s1, $s1, $s0		# t1 += T
	la	$s1, ($s1)
	lw	$s1, ($s1)		# load state into $s1
	sra	$s0, $s0, 2		# T >> 2
	b	st_driver		# go to the next state

dump:	
	lb	$t3, tabToken		
	beq	$t3, 0x23, exit		# if (tabToken[0][0] == #) goto exit
	li	$s5, 0	
nextTok:
	lb	$t3, tabToken+12($s5)
	bne	$t3, ':', operator	# if(tabToken[i+1][0] == ':') goto operator
	lw	$t4, tabToken+0($s5)	# get current token
	sw	$t4, TOKEN
	lw	$t4, tabToken+4($s5)
	sw	$t4, TOKEN+4
	li	$s6, 1			# $s6 = DEFN = 1
	jal	VAR
	addi	$s5, $s5, 24		# skip next token: �:�
operator:
	addi	$s5, $s5, 12		# get next token index
	li	$s7, 1			# isComma = true
chkVar:
	lb	$t3, tabToken+0($s5)
	beq	$t3, '#', realDump
	bne	$s7, 1, nextVar		# if(!isComma) goto nextVar
	lb	$t3, tabToken+10($s5)   	
	subi	$t3, $t3, 0x30		
	bne	$t3, 2, nextVar		#if(!isComma) goto nextVar
	lw	$t4, tabToken+0($s5)	# get current token
	sw	$t4, TOKEN
	lw	$t4, tabToken+4($s5)
	sw	$t4, TOKEN+4
	li	$s6, 0			# DEFN = 0
	jal	VAR			# call VAR function
nextVar:
	lb	$t3, tabToken+0($s5)	# check if token is �,�
	beq	$t3, 0x2C, yup		# #if(tabToken[i][0] == ',') goto yup
	bne	$t3, 0x2C, nope		#if(tabToken[i][0] != ',') goto nope
yup:
	li	$s7, 1			# isComma = true
	j	after			# goto after
nope:
	li	$s7, 0			# isComma = false
	j	after			# goto after
after:
	addi	$s5, $s5, 12		# get next token index
	b	chkVar			# check next token
realDump:
	jal	clearInBuf		# clear input buffer
	jal	clearTokArray		# clear token array
	jal	clearTok
	jal	printsymTab
	addi	$s4, $s4, 4		# LOC +=4
	b 	newline			# get next input line
exit:
	li	$v0, 10
	syscall

VAR:
	sw	$ra, saveReg		
	jal	srchSymTab		# goto srchSymTab
	bge	$t8, $zero, else	# if(symIndex >= 0) goto else
	li	$s0, 0x4		
	or	$t9, $s0, $s6		# newStatus = $t9
	jal	saveSymTab		# saveSymTab(TOKEN, symTab, symTabIndex, newstatus, foundindex)
	b	varEnd
else:
	sw	$t2, saveReg+4		# saveReg[1] = oldStatus
	lw	$t2, symTab+12($t8)	# oldstatus = symTab[foundindex + 12]
	and	$t9, $t2, 0x2		# newstatus = oldstatus & 0x2
	and	$t2, $t2, 0x1		# oldstatus &= 0x1
	sll	$t2, $t2, 1		# oldstatus << 1
	or	$t9, $t9, $t2		# newstatus |= oldstatus
	or	$t9, $t9, $s6		# newstatus |= DEFN
	sw	$t9, symTab+12($t8)	# symTab[foundindex + 12] = newstatus
	lw	$t2, saveReg+4	
varEnd:
	b	realEnd
varRealEnd:	
	lw	$ra, saveReg
	jr	$ra			#return

saveSymTab:
	sw	$t9, symTab+12($t7)	#symTab[symTabindex +12] = newstatus
	sw	$t2, saveReg+4
	lw	$t2, TOKEN
	sw	$t2, symTab+0($t7)	#symTab[symTabindex] = TOKEN
	lw	$t2, TOKEN+4
	sw	$t2, symTab+4($t7)	#symTab[symTabindex + 4] = TOKEN +4
	add	$t8, $zero, $t7		#foundindex = symTabindex
	addi	$t7, $t7, 16		#symTabindex += 16
	lw	$t2, saveReg+4
	jr	$ra
		
printsymTab:
	sw	$t2, saveReg+8
	sw	$t3, saveReg+12
	sw	$t4, saveReg+16
	sw	$t5, saveReg+20
	li	$t2, 0
	li	$v0, 4
	la	$a0, symTabHead	
	syscall				#print header
	la	$a0, dashLine
	syscall				#print dashes
repeat:
	beq 	$t2, $t7, ret
	la	$t3, symTab($t2)
	lb	$t4, symTab+8($t2)
	li	$t5, '\0'
	sb	$t5, symTab+8($t2)
	move	$a0, $t3
	syscall				#print label
	sb	$t4, symTab+8($t2)
	addi	$t2, $t2, 8
	la	$a0, space
	syscall				#print spaces
	li	$v0, 1
	lw	$a0, symTab($t2)
	addi	$t2, $t2, 4
	syscall				#print value
	li	$v0, 4
	la	$a0, space
	syscall				#print spaces
	la	$a0, hex
	syscall				#print hex prefix
	li	$v0, 1
	lw	$a0, symTab($t2)
	addi	$t2, $t2, 4
	syscall				#print status
	li	$v0, 4		
	la	$a0, tempNewLine
	syscall				#print newline
	bc1f	repeat
ret:
	lw	$t2, saveReg+8
	lw	$t3, saveReg+12
	lw	$t4, saveReg+16
	lw	$t5, saveReg+20
	jr	$ra
realEnd:	
	la $s0, symACTS 	# load address of symACTS to access the first line
	sll $t9, $t9, 2 	# newStatus * 8
	add $s0, $s0, $t9 	# calculate the address of the correct symACT
	sra $t9, $t9, 2 
	jr $s0
	
symACTS:
	b symACT0
	b symACT1
	b symACT2
	b symACT3
	b symACT4
	b symACT5
	
symACT0:
	lw	$t1, symTab+8($t8)		#retVar = symTab[i+8]
	sw	$s4, symTab+8($t8)		#symTab[i+8] = LOC
	b	varRealEnd			#goto varRealEnd
symACT1:
	lw	$t1, symTab+8($t8)		#retVar = symTab[i+8]
	sw	$s4, symTab+8($t8)		#symTab[i+8] = LOC
	b	varRealEnd			#goto varRealEnd
symACT2:
	lw	$t1, symTab+8($t8)		#retVar = symTab[i+8]
	b	varRealEnd			#goto varRealEnd
symACT3:
	la	$a0, error
	li	$v0, 4
	syscall					#print "Double Definition Error
	li	$t1, -1				#retVar = -1
	b	varRealEnd			#goto varRealEnd
symACT4:
	sw	$s4, symTab+8($t8)		#symTab[i+8] = LOC
	li	$t1, -1				#retVar = -1
	b	varRealEnd			#goto varRealEnd
symACT5:
	sw	$s4, symTab+8($t8)		#symTab[i+8] = LOC
	li	$t1, 0				#retVar = -1
	b	varRealEnd			#goto varRealEnd
	
srchSymTab:
	sw	$t2, saveReg+4
	sw	$t3, saveReg+8
	sw	$t4, saveReg+12
	li	$t2, 0				# i = 0
	li	$t8, -1				# foundindex = -1
startSearch:	
	bge	$t2, $t7, srchEnd		# if(i >= symTabindex) goto srchEnd
	lw	$t3, TOKEN
	lw	$t4, symTab($t2)
	bne	$t3, $t4, update		# if(TOKEN != symTab[i]) goto update
	lw	$t3, TOKEN+4
	lw	$t4, symTab+4($t2)
	bne	$t3, $t4, update		# if(TOKEN+4 != symTab[i+4]) goto update
	add	$t8, $zero, $t2			# foundindex = i
	j	srchEnd
update:
	addi	$t2, $t2, 16			# i += 12
	b	startSearch
srchEnd:
	lw	$t2, saveReg+4
	lw	$t3, saveReg+8
	lw	$t4, saveReg+12
	jr	$ra				

ACT1: 
	lb	$a0, inBuf($t5)			# $a0: next char
	jal	lin_search			# $s0: T (char type)
	addi	$t5, $t5, 1			# $t5++
	jr	$v1
	
ACT2:
	li	$s3, 0				# initialize index to TOKEN char 
	sb	$a0, TOKEN($s3)			# save 1st char to TOKEN
	addi	$t0, $s0, 0x30			# T in ASCII
	sb	$t0, TOKEN+10($s3)		# save T as Token type
	li	$t0, '\n'
	sb	$t0, TOKEN+11($s3)		# NULL to terminate an entry
	addi	$s3, $s3, 1
	jr 	$v1
	
ACT3:
	bgt	$s3, 7, lenError		# TOKEN length error
	sb	$a0, TOKEN($s3)			# save char to TOKEN
	addi	$s3, $s3, 1			# $s3: index to TOKEN
	jr	$v1	
lenError:
	li	$s0, 7				# T=7 for token length error
	jr	$v1
					
ACT4:
	lw	$t0, TOKEN($0)			# get 1st word of TOKEN
	sw	$t0, tabToken($a3)		# save 1st word to tabToken
	lw	$t0, TOKEN+4($0)		# get 2nd word of TOKEN
	sw	$t0, tabToken+4($a3)		# save 2nd word to tabToken
	lw	$t0, TOKEN+8($0)		# get Token Type
	sw	$t0, tabToken+8($a3)		# save Token Type to tabToken
	addi	$a3, $a3, 12			# update index to tabToken
	
	jal	clearTok			# clear 3-word TOKEN
	jr	$v1

RETURN:
	sw	$zero, tabToken($a3)		# force NULL into tabToken
	b	dump				# leave the state table


ERROR:
	la	$a0, errorPrompt		# print error occurrence
	li	$v0, 4
	syscall
	b	dump


clearTok:
	li	$t1, 0x20202020
	sw	$t1, TOKEN($0)
	sw	$t1, TOKEN+4($0)
	sw	$t1, TOKEN+8($0)
	jr	$ra
	
printline:
	la	$a0, inBuf			# input Buffer address
	li	$v0,4
	syscall
	jr	$ra

printTokArray:
	la	$a0, tabTokenHeader		# table heading
	li	$v0, 4
	syscall

	la	$a0, tabToken			# print tabToken
	li	$v0, 4
	syscall

	jr	$ra

clearInBuf:
	li	$t0,0
loopInB:
	bge	$t0, 80, doneInB
	sw	$zero, inBuf($t0)		# clear inBuf to 0x0
	addi	$t0, $t0, 4
	b	loopInB
doneInB:
	jr	$ra
	
clearTokArray:
	li	$t0, 0
	li	$t1, 0x20202020			# intialized with blanks
loopCTok:
	bge	$t0, $a3, doneCTok
	sw	$t1, tabToken($t0)		# clear
	sw	$t1, tabToken+4($t0)		# 3-word entry
	sw	$t1, tabToken+8($t0)		# in tabToken
	addi	$t0, $t0, 12
	b	loopCTok
doneCTok:
	jr	$ra
	
getline: 
	la	$a0, linePrompt			# Prompt to enter a new line
	li	$v0, 4
	syscall

	la	$a0, inBuf			# get a new line
	li	$a1, 80	
	li	$v0, 8
	syscall
	jr	$ra

lin_search:
	li	$t0,0				# index to Tabchar
	li	$s0, 7				# return value of type T
loopSearch:
	lb	$t1, Tabchar($t0)
	beq	$t1, 0x7F, charFail
	beq	$t1, $a0, charFound
	addi	$t0, $t0, 8
	b	loopSearch

charFound:
	lw	$s0, Tabchar+4($t0)		# return char type
charFail:
	jr	$ra


	
	
	.data

STAB:
Q0:     .word  ACT1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  ACT2
        .word  Q2   # T1
        .word  Q5   # T2
        .word  Q3   # T3
        .word  Q3   # T4
        .word  Q0   # T5
        .word  Q4   # T6
        .word  Q11  # T7

Q2:     .word  ACT1
        .word  Q6   # T1
        .word  Q7   # T2
        .word  Q7   # T3
        .word  Q7   # T4
        .word  Q7   # T5
        .word  Q7   # T6
        .word  Q11  # T7

Q3:     .word  ACT4
        .word  Q0   # T1
        .word  Q0   # T2
        .word  Q0   # T3
        .word  Q0   # T4
        .word  Q0   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q4:     .word  ACT4
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q5:     .word  ACT1
        .word  Q8   # T1
        .word  Q8   # T2
        .word  Q9   # T3
        .word  Q9   # T4
        .word  Q9   # T5
        .word  Q9   # T6
        .word  Q11  # T7

Q6:     .word  ACT3
        .word  Q2   # T1
        .word  Q2   # T2
        .word  Q2   # T3
        .word  Q2   # T4
        .word  Q2   # T5
        .word  Q2   # T6
        .word  Q11  # T7

Q7:     .word  ACT4
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q8:     .word  ACT3
        .word  Q5   # T1
        .word  Q5   # T2
        .word  Q5   # T3
        .word  Q5   # T4
        .word  Q5   # T5
        .word  Q5   # T6
        .word  Q11  # T7

Q9:     .word  ACT4
        .word  Q1  # T1
        .word  Q1  # T2
        .word  Q1  # T3
        .word  Q1  # T4
        .word  Q1  # T5
        .word  Q1  # T6
        .word  Q11 # T7

Q10:	.word	RETURN
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q11:    .word  ERROR 
	.word  Q4  # T1
	.word  Q4  # T2
	.word  Q4  # T3
	.word  Q4  # T4
	.word  Q4  # T5
	.word  Q4  # T6
	.word  Q4  # T7
	
	
Tabchar: 
	.word ' ', 5
 	.word '#', 6
 	.word '$', 4 
	.word '(', 4
	.word ')', 4 
	.word '*', 3 
	.word '+', 3 
	.word ',', 4 
	.word '-', 3 
	.word '.', 4 
	.word '/', 3 

	.word '0', 1
	.word '1', 1 
	.word '2', 1 
	.word '3', 1 
	.word '4', 1 
	.word '5', 1 
	.word '6', 1 
	.word '7', 1 
	.word '8', 1 
	.word '9', 1 

	.word ':', 4 

	.word 'A', 2
	.word 'B', 2 
	.word 'C', 2 
	.word 'D', 2 
	.word 'E', 2 
	.word 'F', 2 
	.word 'G', 2 
	.word 'H', 2 
	.word 'I', 2 
	.word 'J', 2 
	.word 'K', 2
	.word 'L', 2 
	.word 'M', 2 
	.word 'N', 2 
	.word 'O', 2 
	.word 'P', 2 
	.word 'Q', 2 
	.word 'R', 2 
	.word 'S', 2 
	.word 'T', 2 
	.word 'U', 2
	.word 'V', 2 
	.word 'W', 2 
	.word 'X', 2 
	.word 'Y', 2
	.word 'Z', 2

	.word 'a', 2 
	.word 'b', 2 
	.word 'c', 2 
	.word 'd', 2 
	.word 'e', 2 
	.word 'f', 2 
	.word 'g', 2 
	.word 'h', 2 
	.word 'i', 2 
	.word 'j', 2 
	.word 'k', 2
	.word 'l', 2 
	.word 'm', 2 
	.word 'n', 2 
	.word 'o', 2 
	.word 'p', 2 
	.word 'q', 2 
	.word 'r', 2 
	.word 's', 2 
	.word 't', 2 
	.word 'u', 2
	.word 'v', 2 
	.word 'w', 2 
	.word 'x', 2 
	.word 'y', 2
	.word 'z', 2

	.word 0x7F, 0
