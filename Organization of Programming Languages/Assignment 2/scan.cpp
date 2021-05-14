#include "scan.hpp"
#include <iostream>

std::string token_image;

token scan() {
	static int c = ' ';
		/* next available char; extra (int) width accommodates EOF */	
	int i = 0;		/* index into token_image */

	token_image = "";

	/* skip white space */
	while (isspace(c)) {
		c = getchar();
	}
	if (c == EOF)
		return t_eof;

	if (isalpha(c)) {
		do {
			token_image += c;
			if (i >= MAX_TOKEN_LEN) {
				std::cout << "max token length exceeded\n";
				exit(1);
			}
			c = getchar();
		} while (isalpha(c) || isdigit(c) || c == '_');

		if (!token_image.compare("read")) return t_read;
		else if (!token_image.compare("write")) return t_write;
		else if (!token_image.compare("if")) return t_if;
		else if (!token_image.compare("while")) return t_while;
		else if (!token_image.compare("end")) return t_end;
		else return t_id;
	}

	else if (isdigit(c)) {
		do {
			token_image += c;
			c = getchar();
		} while (isdigit(c));
	
		return t_literal;
	}

	else switch (c) {
		case ':':
			if ((c = getchar()) != '=') {
				std::cerr << "error\n";
				exit(1);
			}
			else {
				c = getchar();
				return t_gets;
			}
			break;

		case '<':
			c = getchar();
			if (c == '>') {
				c = getchar();
				return t_neq;
			}
			else if (c == '=') {
				c = getchar();
				return t_lesseq;
			}
			else {
				c = getchar();
				return t_less;
			}
			break;

		case '>':
			if ((c = getchar()) == '=') {
				c = getchar();
				return t_greatereq;
			}
			else {
				c = getchar();
				return t_greater;
			}
			break;

		case '(': c = getchar(); return t_lparen;
		case ')': c = getchar(); return t_rparen;
		case '+': c = getchar(); return t_add;
		case '-': c = getchar(); return t_sub;
		case '*': c = getchar(); return t_mul;
		case '/': c = getchar(); return t_div;
		case '=': c = getchar(); return t_eq;

		default:
			std::cerr << "error\n";
			exit(1);
	}
}