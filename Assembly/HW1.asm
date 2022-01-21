.data
	X: .word 1, 2, 3, 4, 5 # manually initialize array X
	length: .word 5
	sum: .word 0
.text 
	main:
		jal get_sum
		
		#print sum
		li $v0, 1
		move $a0, $t3
		syscall
		
		#end program
		li $v0, 10
		syscall
	
	get_sum:
		la $t0, X	#base address
		li $t1, 0	#i = 0
		lw $t2, length	#$t2 = length
		li $t3, 0	#sum = 0
		
		sumLoop:
			lw $t4, ($t0)		#$t4 = X[i]
			add $t3, $t3, $t4	#sum = sum + X[i]
			
			add $t1, $t1, 1		#i++
			add $t0, $t0, 4		#update array address
			
			blt $t1, $t2, sumLoop	#if(i < length) -> loop again

		jr $ra
