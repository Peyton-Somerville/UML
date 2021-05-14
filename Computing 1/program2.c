/*
	Author: Peyton Somerville
	Date: 10/16/18

	Purpose: This program takes an input from the user of the starting green crud population in pounds and a number of days and calculates the size of the population after the selected amount of days. 

	Time Spent: 45 minutes.
*/

#include <stdio.h>

int get_size(void);
int get_days(void);
void calculate(int initial_size, int days);

void clear_keyboard_buffer(void);
int user_wishes_to_continue(void);

int main(int argc, char* argv[])
{
	int initial_size, days;

	do
	{
		initial_size = get_size();
		days = get_days();
		calculate(initial_size, days);
	} while (user_wishes_to_continue());

	return 0;
}

int get_size(void)
{
	int noc, size_answer;
	printf("Please enter the initial size of the green crud: ");
	noc = scanf("%d", &size_answer);
	clear_keyboard_buffer();
	while (noc != 1 || size_answer < 0)
	{
		printf("Error: Invalid Input\n");
		printf("Please enter the initial size of the green crud: ");
		noc = scanf("%d", &size_answer);
		clear_keyboard_buffer();
	}
	return size_answer;
}

int get_days(void)
{
	int noc, days_answer;
	printf("Please enter the number of days: ");
	noc = scanf("%d", &days_answer);
	clear_keyboard_buffer();
	while (noc != 1 || days_answer < 0)
	{
		printf("Error: Invalid Input\n");
		printf("Please enter the number of days: ");
		scanf("%d", &days_answer);
		clear_keyboard_buffer();
	}
	return days_answer;
}

void calculate(int initial_size, int days)
{
	int temp_size = 0, next_size = 0, previous_size = 0;
	int x;

	temp_size = initial_size;
	for (x = 0; x <= days; x += 5)
	{
		next_size = temp_size + previous_size;
		previous_size = temp_size;
		temp_size = next_size;
	}

	printf("With an initial population of %d pounds of crud growing for %d days,\n", initial_size, days);
	printf("the final population would be %d pounds\n", previous_size);
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

int user_wishes_to_continue(void)
{
	char answer;

	printf("\n\nDo you wish to continue? (y/n): ");
	scanf(" %c", &answer);
	clear_keyboard_buffer();
	while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
	{
		printf("Invalid Input\n");
		printf("Do you wish to continue? (y/n): ");
		scanf(" %c", &answer);
		clear_keyboard_buffer();
	}

	return answer == 'y' || answer == 'Y';
}