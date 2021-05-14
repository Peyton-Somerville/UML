start:  lodd on:
        stod 4095
        call xbsywt:
        loco str1:
nextw:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer crnl:
        stod 4094
        push
        subd c255:
        jneg crnl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump nextw:
crnl:   lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
		lodd on:                ; mic1 program to print string
        stod 4093               ; and scan in a 1-5 digit number
bgndig:	call rbsywt:            ; using CSR memory locations
        lodd 4092
        subd numoff:
        push
nxtdig: call rbsywt:
        lodd 4092
        stod nxtchr:
        subd nl:
        jzer endnum:
        mult 10
        lodd nxtchr:
        subd numoff:
        addl 0
        stol 0
        jump nxtdig:
endnum: lodd numptr:
        popi
        addd c1:
        stod numptr:
        lodd numcnt:
        jzer addnms:
        subd c1:
        stod numcnt:
        jump start:
addnms: lodd binum1:
		stod sum:
		lodd binum2:
		addd sum:
		stod sum:
		jneg overflow:
		call xbsywt:
		loco str2:
		call xbsywt:
		call convert:
		call xbsywt:
		lodd zero:
		halt
overflow: loco str3:
		call nextw:
		lodd cn1:
		halt
xbsywt: lodd 4095
        subd mask:
        jneg xbsywt:
        retn
rbsywt: lodd 4093
        subd mask:
        jneg rbsywt:
        retn
sb:     loco 8
loop1:  jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:   addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:
finish: lodl 1
        retn
convert: lodd on:
		stod 4095
		lodd cn1:
		push
		lodd mask:
		push
final:  lodd sum:
		jzer display:
		lodd mask:
		push
		lodd sum:
		push
		div
		pop
		stod sum:
		pop
		insp 2
		addd numoff:
		push
		jump final:
display: pop
		jneg done:
		stod 4094
		call xbsywt:
		jump display:
done:   retn
numoff: 48
nxtchr: 0
numptr: binum1:
binum1: 0
binum2: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c10:    10
c255:   255
cn1:	-1
zero:	0
sum:    0
numcnt: 1
pstr1:  0
str1:   "Please enter a 1-5 digit number followed by enter"
str2:	"The sum = "
str3:	"Sum overflowed"