/*
	Author: Peyton Somerville
	Date: 10/11/18

	Purpose: This program takes a start point and an endpoint from the user, and uses the Collatz conjecture to print how many cycles it takes each number in the user's set to get down to 1. 
	It prints the numbers in an organized table.

	Time Spent: 45 minutes
*/

#include <stdio.h>

void clear_keyboard_buffer(void);
void print_table(int sp, int ep);

int main(int argc, char* argv[])
{
	int startpoint, endpoint, noc;

	printf("Enter a starting point between (1, 1000): ");
	noc = scanf("%d", &startpoint);
	clear_keyboard_buffer();
	while (noc != 1 || startpoint <= 1 || startpoint >= 1000)
	{
		printf("Error: Enter a starting point between (1, 1000): ");
		noc = scanf("%d", &startpoint);
		clear_keyboard_buffer();
	}

	printf("\nEnter an ending point > start point and < 10000: ");
	noc = scanf("%d", &endpoint);
	clear_keyboard_buffer();
	while (noc != 1 || endpoint <= startpoint || endpoint >= 10000)
	{
		printf("Error: Enter an ending point > start point and < 10000: ");
		noc = scanf("%d", &endpoint);
		clear_keyboard_buffer();
	}

	print_table(startpoint, endpoint);
	
	return 0;
}

void clear_keyboard_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}

void print_table(int sp, int ep)
{	
	int x, iteration=0;
	int number, amount;

	for(x = sp; x <= ep; x++)
	{
		iteration++;
		amount = 0;
		number = x;
		printf("%5d:", x);
		do
		{
			if (number % 2 == 0)
			{
				number = number / 2;
				amount++;
			}
			else if (number % 2 == 1)
			{
				number = number * 3 + 1;
				amount++;
			}
		} while (number>1);
		if (iteration % 7 == 0)
			printf("%-5d\n", amount);
		else
			printf("%-5d\t", amount);
	} 
}
