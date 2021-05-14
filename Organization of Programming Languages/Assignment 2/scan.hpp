/*
	Peyton Somerville
	OPL Assignment 2
*/

#include <string>

#define MAX_TOKEN_LEN 128

enum token {
	t_read, t_write, t_id, t_literal, t_gets,
	t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,
	t_eq, t_neq, t_less, t_greater, t_lesseq, t_greatereq,
	t_if, t_while, t_end };

extern std::string token_image;

token scan();