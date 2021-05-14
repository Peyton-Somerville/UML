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