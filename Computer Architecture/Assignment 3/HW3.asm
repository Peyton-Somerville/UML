LOOP:   lodd PasCnt:  	; num of fibs to do in PasCnt
		jzer DONE:		; no more passes, go to done
		subd c1:
		stod PasCnt:	; - - passes remaining
P1:		lodd daddr:		; load a pointer to fib arg
		pshi			; push arg for fib on stack
		addd c1:
		stod daddr:		; inc, store pointer for next d[n] 
		lodd c0:		; load AC with 0
		stod tmp:		; tmp is current fib num
		stod fm1:		; fib(n-1) starting at 0
		lodd c1:		; load AC with 1
		stod fm2:		; fib(n-2) starting at 1
		call FIB:		; call fib (arg on stack)

P2:		lodd tmp:		; load AC with current fib num
		push			; put return AC (fib(n)) on stack
		lodd faddr:		; load a pointer to result f[n]
		popi			; pop result off stack into f[n]
		addd c1:		
		stod faddr:		; inc, store pointer for next f[n]
		jump LOOP:		; go to top for next pass

FIB:	lodl 1			; fib func loads arg from stack
		jzer P2:		; when fib is 0
		lodd fm1:		; load AC with fib(n-1)
		addd fm2:		; load AC with fib(n-2)
		stod tmp:		; store fib(n-1)+fib(n-2) in tmp
		lodd fm1:		; load fib(n-1)
		stod fm2:		; store fib(n-2)
		lodd tmp:		; load result
		stod fm1:		; store fib(n-1)
		lodl 1			; load PasCnt
		subd c1:
		push			; update
		call FIB:		; recursive loop

DONE:	halt

daddr:  d0:				; start address of fib args 
faddr:  f0:				; start address of fib results
c0: 	0				; constants 
c1: 	1	
PasCnt: 5				; number of data elements to process
LpCnt:	0				; number of fib iterations
tmp:	0				; initial value for fib(2)
fm1:	0				; at any point fib(n-1)
fm2:	0				; at any point fib(n-2)
.LOC 	100				; locate data beginning at 100
d0:  	3				; array of args for fib function
     	9
     	18
     	23
     	25
f0:  	0				; array of result locs for fib returns
     	0
     	0
     	0 
     	0
