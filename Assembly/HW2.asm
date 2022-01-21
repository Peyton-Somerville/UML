.data
	inBuf: .space 80 # input line
	outBuf: .space 80 # char types for the input line
	Tabchar: .word 0x0a, 6 # LF
	.word ' ', 5
	.word '#', 4 
	.word '$',4
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

	.word 0x5c, -1 	# if you ‘\’ as the end-of-table symbol
	prompt: .asciiz "\nPlease enter input>> \n"
	prints: .asciiz " "
.text

j main

main:
	jal getline
	jal linear_search 
	jal clear 	#clear(t6-g)
	j main

linear_search:
	li $t0,0	#i=0

loop1: 	
	bge $t0,80 ret 	#while(i>80)

	lb $t1 inBuf($t0)	#load inbuf[i] into t1
	beqz $t1,ret	#if inbuf[i] == '' return 

	bne $t1,35,continue	#if t1 != '#' continue on

	beqz $t0,end	#if i = 0 break out
	li $v0,1 	#else print
	li $a0,6 	#print 6
	syscall
	jr $ra		#return
	
 continue:
        li $t2,0 	#intialize j with 0
        
 loop2:
 	bge $t2,600,ret 
 
	lb $t3,Tabchar($t2)	#load char from table into t3
 
	bne $t3,$t1,loop1end	#if(inbuff[i] != tabchar[j].char) jump to j incrementer
	lw $t5,Tabchar+4($t2)	#else load Tabchar[j].num int t5


	bne $t5,5,printn	#if ( t5 !=' ') print t5
	la $a0,prints	#else print ' '
	li $v0,4	#prints line
	syscall
	j loop1end	#increment i
	
	j end	#jump to end

printn:

	la $a0,($t5) 	#load chartype into a0
	li $v0,1 	#print
	syscall
	j loop2end 	#goto incrementer

loop1end: 
	add $t2,$t2,8 	#increment j by 8 
	j loop2 	#jump back to the loop
	
loop2end:
	add $t0,$t0,1 	#increment i by 1
	j loop1 	#jump back to the loop

getline: 
	la $a0, prompt	#Prompt to enter a new line
	li $v0, 4 	#load registry for input
	syscall

	la $a0, inBuf 	#read new line
	li $a1, 80 
	li $v0, 8 
	syscall

	jr $ra	#return
	
clear :
	li $t6,0	 #g = 0
	
loop3:  
	bge $t6,80,ret	#while(g < 80)
	sb $zero,inBuf($t6)	#replace the spot in the buffer with 0
	add $t6,$t6,1 	#g++
	j loop3 	#jump back to the top of the loop

ret: 	
	jr $ra 	#return

end:
	li $v0,10
	syscall
