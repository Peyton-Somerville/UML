#include "scan.hpp"
#include <iostream>

using std::cout;
using std::string;

string tmp_str;

class Syntax_Error {
public:
	Syntax_Error (const string& msg) : msg_(msg) {}
	Syntax_Error () {}
	
	string getMsg() const { return(msg_); }
private:
	string msg_;
};

const string names[] = { "read", "write", "id", "literal", "gets",
					   "add", "sub", "mul", "div", "lparen", "rparen", "eof",
						"eq", "neq", "less", "greater", "lesseq", "greatereq",
						"if", "while", "end" };

static token input_token;

void error() {
	cout << "syntax error\n";
	return;
}

void match(token expected) {
	if (input_token == expected) {
		// cout << "matched " << names[input_token];
		// if (input_token == t_id || input_token == t_literal)
			// cout << ": " << token_image;
		// cout << "\n";
		input_token = scan();
	}
	else {
		error();
		input_token = expected;		// Wirth's method
		throw Syntax_Error("\nmatch: input_token did not match expected\n");
	}
}

void program();
void stmt_list();
void stmt();
void cond_expr();
void expr();
void term();
void term_tail();
void factor();
void factor_tail();
void r_op();
void add_op();
void mul_op();

void program() {
	switch (input_token) {
		case t_id:
		case t_read:
		case t_write:
		case t_if:
		case t_while:
		case t_eof:
			// cout << "predict program --> stmt_list eof\n";
			cout << "(program\n[ ";
			stmt_list();
			match(t_eof);
			cout << "]\n)\n";
			break;
		default: error();
	}
}

void stmt_list() {
	switch (input_token) {
		case t_id:
		case t_read:
		case t_write:
		case t_if:
		case t_while:
			// cout << "predict stmt_list --> stmt stmt_list\n";
			cout << "(";
			stmt();
			cout << ")\n";
			stmt_list();
			break;
		case t_end:
		case t_eof:
			// cout << "predict stmt_list --> epsilon\n";
			break;          /* epsilon production */
		default: error();
	}
}

void stmt() {
	try {
		switch (input_token) {
			case t_id:
				// cout << "predict stmt --> id gets expr\n";
				cout << ":= ";
				cout << "\"" << token_image << "\" ";
				match(t_id);
				match(t_gets);
				expr();
				cout << "(" << tmp_str << ")";
				break;
			case t_read:
				// cout << "predict stmt --> read id\n";
				cout << token_image << " ";
				match(t_read);
				cout << "\"" << token_image << "\"";
				match(t_id);
				break;
			case t_write:
				// cout << "predict stmt --> write expr\n";
				cout << token_image << " ";
				match(t_write);
				expr();
				cout << "(" << tmp_str << ")";
				break;
			case t_if:
				// cout << "predict stmt --> if cond_expr stmt_list end\n";
				cout << token_image << "\n";
				match(t_if);
				cout << "(";
				cond_expr();
				cout << ")\n[ ";
				stmt_list();
				cout << "]\n";
				match(t_end);
				break;
			case t_while:
				// cout << "predict stmt --> while cond_expr stmt_list end\n";
				cout << token_image << "\n";
				match(t_while);
				cout << "(";
				cond_expr();
				cout << ")\n[ ";
				stmt_list();
				cout << "]\n";
				match(t_end);
				break;
			default: error(); throw Syntax_Error("\nstmt: expected id, read, write, if, or while\n");
		}
	}
	catch (Syntax_Error se) {
		cout << se.getMsg();
		while (1) {
			switch (input_token) {
				/* FIRST (stmt) */
				case t_id:
					expr();
					return;
				case t_read:
					return;
				case t_write:
					expr();
					return;
				case t_if:
					cond_expr();
					stmt_list();
					return;
				case t_while:
					cond_expr();
					stmt_list();
					return;

				/* FOLLOW (stmt) */
				case t_eof:
					return;

				default:
					input_token = scan();
			}
		}
	}
}

void cond_expr() {
	try {
		switch (input_token) {
			case t_id:
			case t_literal:
			case t_lparen:
				// printf("predict cond_expr --> expr r_op expr\n");
				expr();
				r_op();
				cout << "(" << tmp_str << ") ";
				expr();
				cout << "(" << tmp_str << ")";
				// cout << "(" << tmp_str << ")";
				break;
			default: error(); throw Syntax_Error("\ncond_expr: expected id, literal, or lparen\n");
		}
	}
	catch (Syntax_Error se) {
		cout << se.getMsg();
		while (1) {
			switch (input_token) {
				/* FIRST (cond_expr) */
				case t_id:
				case t_literal:
				case t_lparen:
					expr();
					r_op();
					expr();
					return;

				/* FOLLOW (cond_expr) */
				case t_read:
				case t_write:
				case t_if:
				case t_while:
				case t_rparen:
				case t_eof:
					return;

				default:
					input_token = scan();
			}
		}
	}
}

void expr() {
	try {
		switch (input_token) {
			case t_id:
			case t_literal:
			case t_lparen:
				// cout << "predict expr --> term term_tail\n";
				term();
				term_tail();
				break;
			default: error(); throw Syntax_Error("\nexpr: expected id, literal, or lparen\n");
		}
	}
	catch (Syntax_Error se) {
		cout << se.getMsg();
		while (1) {
			switch (input_token) {
				/* FIRST (expr) */
				case t_id:
				case t_literal:
				case t_lparen:
					term();
					term_tail();
					return;

				/* FOLLOW (expr) */
				case t_read:
				case t_write:
				case t_if:
				case t_while:
				case t_rparen:
				case t_less:
				case t_lesseq:
				case t_neq:
				case t_eq:
				case t_greater:
				case t_greatereq:
				case t_eof:
					return;

				default:
					input_token = scan();
			}
		}
	}
}

void term() {
	try {
		switch (input_token) {
			case t_id:
			case t_literal:
			case t_lparen:
				// cout << "predict term --> factor factor_tail\n";
				factor();
				factor_tail();
				break;
			default: error(); throw Syntax_Error("\nterm: expected id, literal, or lparen\n");
		}
	}
	catch (Syntax_Error se) {
		cout << se.getMsg();
		while (1) {
			switch (input_token) {
				/* FIRST (term) */
				case t_id:
				case t_literal:
				case t_lparen:
					factor();
					factor_tail();
					return;

				/* FOLLOW (term) */
				case t_read:
				case t_write:
				case t_if:
				case t_while:
				case t_end:
				case t_rparen:
				case t_less:
				case t_lesseq:
				case t_neq:
				case t_eq:
				case t_greater:
				case t_greatereq:
				case t_add:
				case t_sub:
				case t_eof:
					return;

				default:
					input_token = scan();
			}
		}
	}
}

void term_tail() {
	switch (input_token) {
		case t_add:
		case t_sub:
			// cout << "predict term_tail --> add_op term term_tail\n";
			cout << "(";
			add_op();
			cout << "(" << tmp_str << ") ";
			term();
			term_tail();
			break;
		case t_rparen:
		case t_id:
		case t_read:
		case t_write:
		case t_if:
		case t_while:
		case t_end:
		case t_less:
		case t_lesseq:
		case t_neq:
		case t_eq:
		case t_greater:
		case t_greatereq:
		case t_eof:
			// cout << "predict term_tail --> epsilon\n";
			break;          /* epsilon production */
		default: error();
	}
}

void factor() {
	try {
		switch (input_token) {
			case t_literal:
				// cout << "predict factor --> literal\n";
				tmp_str = "num \"" + token_image + "\"";
				match(t_literal);
				break;
			case t_id:
				// cout << "predict factor --> id\n";
				tmp_str = "id \"" + token_image + "\"";
				match(t_id);
				break;
			case t_lparen:
				cout << "predict factor --> lparen expr rparen\n";
				match(t_lparen);
				expr();
				match(t_rparen);
				break;
			default: error(); throw Syntax_Error("\nfactor: expected literal, id, or lparen\n");
		}
	}
	catch (Syntax_Error& se) {
		cout << se.getMsg();
		while (1) {
			switch (input_token) {
				/* FIRST (factor) */
				case t_literal:
				case t_id:
					return;
				case t_lparen:
					expr();
					return;

				/* FOLLOW (factor) */
				case t_read:
				case t_write:
				case t_if:
				case t_while:
				case t_end:
				case t_rparen:
				case t_less:
				case t_lesseq:
				case t_neq:
				case t_eq:
				case t_greater:
				case t_greatereq:
				case t_add:
				case t_sub:
				case t_mul:
				case t_div:
				case t_eof:
					return;

				default:
					input_token = scan();
			}
		}
	}
}

void factor_tail() {
	switch (input_token) {
		case t_mul:
		case t_div:
			// cout << "predict factor_tail --> mul_op factor factor_tail\n";
			cout << "(";
			mul_op();
			cout << "(" << tmp_str << ") ";
			factor();
			factor_tail();
			break;
		case t_add:
		case t_sub:
		case t_rparen:
		case t_id:
		case t_read:
		case t_write:
		case t_if:
		case t_while:
		case t_end:
		case t_less:
		case t_lesseq:
		case t_neq:
		case t_eq:
		case t_greater:
		case t_greatereq:
		case t_eof:
			// cout << "predict factor_tail --> epsilon\n";
			break;          /* epsilon production */
		default: error();
	}
}

void r_op() {
	switch (input_token) {
	case t_eq:
		// cout << "predict r_op --> equals\n";
		cout << "= ";
		match(t_eq);
		break;
	case t_neq:
		// cout << "predict r_op --> not equals\n";
		cout << "<> ";
		match(t_neq);
		break;
	case t_less:
		// cout << "predict r_op --> less than\n";
		cout << "< ";
		match(t_less);
		break;
	case t_greater:
		// cout << "predict r_op --> greater than\n";
		cout << "> ";
		match(t_greater);
		break;
	case t_lesseq:
		// cout << "predict r_op --> less than or equal to\n";
		cout << "<= ";
		match(t_lesseq);
		break;
	case t_greatereq:
		// cout << "predict r_op --> greater than or equal to\n";
		cout << ">= ";
		match(t_greatereq);
		break;
	default: error();
	}
}

void add_op() {
	switch (input_token) {
		case t_add:
			// cout << "predict add_op --> add\n";
			cout << "+ ";
			match(t_add);
			break;
		case t_sub:
			// cout << "predict add_op --> sub\n";
			cout << "- ";
			match(t_sub);
			break;
		default: error();
	}
}

void mul_op() {
	switch (input_token) {
		case t_mul:
			// cout << "predict mul_op --> mul\n";
			cout << "* ";
			match(t_mul);
			break;
		case t_div:
			// cout << "predict mul_op --> div\n";
			cout << "/ ";
			match(t_div);
			break;
		default: error();
	}
}

int main() {
	input_token = scan();
	program();
	return 0;
}
