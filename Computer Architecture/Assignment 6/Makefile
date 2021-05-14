linker: linker.c
	gcc - ansi - Wall - o linker linker.c

run:
	./masm_mrd - o < main.asm > main.obj
	./masm_mrd - o < xbswt.asm > xbswt.obj
	./masm_mrd - o < rbswt.asm > rbswt.obj
	./linker main.obj xbswt.obj rbswt.obj > main.exe
	./mic1 prom_mrd.dat main.exe 0 2048

dump:
	./masm_mrd - o < main.asm > main.obj
	./masm_mrd - o < xbswt.asm > xbswt.obj
	./masm_mrd - o < rbswt.asm > rbswt.obj
	./linker - o main.obj xbswt.obj rbswt.obj

clean:
	rm * .obj
	rm main.exe
	rm linker
