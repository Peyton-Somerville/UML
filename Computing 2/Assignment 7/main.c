/*
	Program: Parentheses Balance
	Author: Peyton Somerville
	Date: 3/17/19
	Time Spent: Not sure but a long time
	Purpose: This program checks to see if a set of parentheses/ brackets are balanced meaning each opening bracket has a closing one. A stack is used to complete this task.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
	int n;	//number of cases
	int i;

	scanf("%d", &n);
	clear_keyboard_buffer();

	for (i = 0; i < n; ++i)
	{
		check_string();
	}

	return 0;
}
