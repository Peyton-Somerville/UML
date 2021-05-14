/**** This is the Mic-1 linker ****/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct nament {
	char name[26];
	int addr;
	struct nament *next;
} SYMTABENTRY;

void add_symbol(char *, int);
void generate_code(int);
void print_first_pass(void);
void append_table(void);

SYMTABENTRY *symtab = NULL;
FILE *p1, *p2;
char cstr_12[13];

int main(int argc, char* argv[]) {
	int  i, start, pc_offset = 0, pc = 0;
	int  linum = 0, object_file = 0, dump_tab = 0;
	int  line_number, new_pc;
	char instruction[18];
	char symbol[26];

	/***
		for(i=0; i<argc; i++){
		  printf("arg %d is %s\n", i, argv[i]);
		}
	***/

	if (argc > 1 && (strcmp(argv[1], "-s") == 0)) dump_tab = linum = 1;
	else if (argc > 1 && (strcmp(argv[1], "-o") == 0)) object_file = 1;

	if (dump_tab == 1 | object_file == 1)start = 2;
	else start = 1;

	p1 = fopen("/tmp/passone", "w+");
	unlink("/tmp/passone");

	for (i = start; i < argc; ++i) {
		if ((p2 = fopen(argv[i], "r")) == NULL) {
			printf("ERROR: cannot open file %s\n", argv[i]);
			exit(6);
		}
		while (fscanf(p2, "%d %s", &pc, instruction) != EOF) {
			if (pc == 4096)break;
			new_pc = pc + pc_offset;
			symbol[0] = '\0';
			if (instruction[0] == 'U') {
				fscanf(p2, "%s", symbol);
			}
			fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
		}
		while (fscanf(p2, "%s %d", symbol, &line_number) != EOF) {
			add_symbol(symbol, line_number + pc_offset);
		}
		pc_offset = new_pc + 1;
		fclose(p2);
	}

	if (object_file == 1) {
		print_first_pass();
		append_table();
		return 0;
	}

	if (linum == 1) {
		print_first_pass();
	}

	generate_code(linum);

	return 0;

}

void print_first_pass() {
	char in[81];

	rewind(p1);
	while (fgets(in, 80, p1) != NULL) {
		printf("%s", in);
	}
}

void generate_code(int linum) {
	char instr[18];
	char sym[26];
	int lineNum = 0;
	int prevPc = 0;
	int pc, mask, symVal, i, j, dif;
	int compare;

	rewind(p1);
	while (fscanf(p1, "%d %s", &pc, instr) != EOF) {
		dif = pc - prevPc;
		if (dif > 1) {
			for (j = 1; j < dif; j++) {
				printf("1111111111111111 \n");
			}
		}
		prevPc = pc;


		if (instr[0] == 'U') {
			fscanf(p1, "%s", sym);

			SYMTABENTRY *getVal = symtab;
			while (getVal != NULL) {
				compare = strcmp(getVal->name, sym);

				if (compare == 0) {
					symVal = getVal->addr;
					break;
				}
				else {
					getVal = getVal->next;
				}
			}

			for (i = 0; i < 12; i++) {
				cstr_12[i] = '0';
			}

			cstr_12[12] = '\0';
			mask = 2048;

			for (i = 0; i < 12; i++) {
				if (symVal & mask) {
					cstr_12[i] = '1';
				}
				mask = mask >> 1;
			}

			for (i = 0; i < 12; i++) {
				instr[i + 5] = cstr_12[i];
			}

			printf("%s\n", &instr[1]);

		}
		else {
			printf("%s\n", instr);
		}
	}

	return;
}

void add_symbol(char *symbol, int line_number) {
	SYMTABENTRY *addSym;
	addSym = (SYMTABENTRY *)malloc(sizeof(SYMTABENTRY));

	if (symtab == NULL) {
		symtab = addSym;
		addSym->next = NULL;
	}
	else {
		addSym->next = symtab;
		symtab = addSym;
	}

	strcpy(addSym->name, symbol);
	addSym->addr = line_number;

	return;
}

void append_table() {
	while (symtab != NULL) {
		printf("%s %d\n", symtab->name, symtab->addr);
		symtab = symtab->next;
	}

	return;
}