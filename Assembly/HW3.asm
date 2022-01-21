#Peyton Somerville 
#COMP 2030 Section 203

.data
TOKEN:		.word 	0x20202020:2			
TabToken:	.word	0x20202020:30			

inBuf:		.space	80			
prompt:		.asciiz	"Please enter a new line of input>> \n"
err:		.asciiz		
tableHeader:	.asciiz "Token    Token Type\n-----    ----------\n"

	
.text
newline:
	jal	getline		# get new string input
	
			
	la	$s1, Q0
	li	$s0, 1		
nextState:	
	lw	$s2, 0($s1)		
	jalr	$v1, $s2	# return address in $v1	

	sll	$s0, $s0, 2	# Multiply by 4 for word boundary
	add	$s1, $s1, $s0		
	la	$s1, ($s1)
	lw	$s1, ($s1)		
	sra	$s0, $s0, 2		
	b	nextState			

dump:	
	jal	printIn		
	jal	printTabTok		
	jal	clearIn	
	jal	clearTabTok		
	b 	newline


Act1: 
	lb	$a0, inBuf($t9)		# t9=1$t9: next char
	jal	linSearch		# $70: char type
	addi	$t9, $t9, 1		# $t9++
	jr	$v1
	

	
		
				
Act2:
	li	$s3, 0			# index = token char
	sb	$a0, TOKEN($s3)		#token = char[0]
	addi	$t0, $s0, 0x30			
	sb	$t0, TOKEN+10($s3)	# save token type
	li	$t0, '\n'
	sb	$t0, TOKEN+11($s3)	#reaches out to end
	addi	$s3, $s3, 1
	jr 	$v1
	

Act3:
	bgt	$s3, 7, error		
	sb	$a0, TOKEN($s3)		# save char to TOKEN
	addi	$s3, $s3, 1		# $s3 =  index to TOKEN
	jr	$v1	
error:
	li	$s0, 7			# token length er
	jr	$v1
					

Act4:
    	lw	$t0, TOKEN($0)		# get 1st char
	sw	$t0, TabToken($a3)	# save 1st char
	lw	$t0, TOKEN+4($0)	# get 2nd char
	sw	$t0, TabToken+4($a3)	# save 2nd char
	lw	$t0, TOKEN+8($0)	# get chartype type 
	sw	$t0, TabToken+8($a3)	# save type
	addi	$a3, $a3, 12		# index++
	
	jal	clearTok		# clear
	jr	$v1

RETURN:
	sw	$zero, TabToken($a3)		
	b	dump				


ERROR:
	la	$a0, err			
	li	$v0, 4
	syscall
	b	dump


clearTok:
	li	$t1, 0x20202020
	sw	$t1, TOKEN($0)
	sw	$t1, TOKEN+4($0)
	sw	$t1, TOKEN+8($0)
	jr	$ra

printIn:
	la	$a0, inBuf			
	li	$v0,4
	syscall
	jr	$ra

printTabTok:
	la	$a0, tableHeader			
	li	$v0, 4
	syscall

	la	$a0, TabToken		# print
	li	$v0, 4
	syscall

	jr	$ra

clearIn:
	li	$t0,0
loop:
	bge	$t0, 80, donebuf
	sw	$zero, inBuf($t0)	# clear inBuf to 0x0
	addi	$t0, $t0, 4
	b	loop
donebuf:
	jr	$ra
	

clearTabTok:
	li	$t0, 0
	li	$t1, 0x20202020		#blank again
loopingTok:
	bge	$t0, $a3, donewTok
	sw	$t1, TabToken($t0)	# clear
	sw	$t1, TabToken+4($t0)		
	sw	$t1, TabToken+8($t0)		
	addi	$t0, $t0, 12
	b	loopingTok
donewTok:
	jr	$ra	

getline: 
	la	$a0, prompt		# Prompt to enter a new line
	li	$v0, 4
	syscall

	la	$a0, inBuf		# read a new line
	li	$a1, 80	
	li	$v0, 8
	syscall
	jr	$ra


linSearch:
	li	$t0,0			# t0 = i;
	li	$s0, 7			# return value of type T
loopingSearch:
	lb	$t1, Tabchar($t0)	#tabchar[i]
	beq	$t1, 0x7F, notfound
	beq	$t1, $a0, found
	addi	$t0, $t0, 8		#i+=8;
	b	loopingSearch

found:
	lw	$s0, Tabchar+4($t0)	#return chartype
notfound:
	jr	$ra


	
	
	.data

STAB:
Q0:     .word  Act1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  Act2
        .word  Q2   # T1
        .word  Q5   # T2
        .word  Q3   # T3
        .word  Q3   # T4
        .word  Q0   # T5
        .word  Q4   # T6
        .word  Q11  # T7

Q2:     .word  Act1
        .word  Q6   # T1
        .word  Q7   # T2
        .word  Q7   # T3
        .word  Q7   # T4
        .word  Q7   # T5
        .word  Q7   # T6
        .word  Q11  # T7

Q3:     .word  Act4
        .word  Q0   # T1
        .word  Q0   # T2
        .word  Q0   # T3
        .word  Q0   # T4
        .word  Q0   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q4:     .word  Act4
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q5:     .word  Act1
        .word  Q8   # T1
        .word  Q8   # T2
        .word  Q9   # T3
        .word  Q9   # T4
        .word  Q9   # T5
        .word  Q9   # T6
        .word  Q11  # T7

Q6:     .word  Act3
        .word  Q2   # T1
        .word  Q2   # T2
        .word  Q2   # T3
        .word  Q2   # T4
        .word  Q2   # T5
        .word  Q2   # T6
        .word  Q11  # T7

Q7:     .word  Act4
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q8:     .word  Act3
        .word  Q5   # T1
        .word  Q5   # T2
        .word  Q5   # T3
        .word  Q5   # T4
        .word  Q5   # T5
        .word  Q5   # T6
        .word  Q11  # T7

Q9:     .word  Act4
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
	.word 	0x0a, 6		# LF
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

	.word 0x5c, -1
