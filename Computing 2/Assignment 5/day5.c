/*
	Author: Peyton Somerville
	Date: 2/7/19
	Effort: About an hour.
	Purpose: This program utilizes bitwise operators again but with an array of integers instead of just integers.
*/

#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[])
{
	unsigned int flag_holder[5] = { 0 };

	set_flag(flag_holder, 3);
	set_flag(flag_holder, 16);
	set_flag(flag_holder, 31);
	set_flag(flag_holder, 87);

	display_flags(flag_holder, 5);
	printf("\n\n");

	unset_flag(flag_holder, 31);
	unset_flag(flag_holder, 3);
	set_flag(flag_holder, 99);
	set_flag(flag_holder, 100);

	display_flags(flag_holder, 5);

	return 0;
}

void set_flag(unsigned int flag_holder[], int flag_position)
{
	if (flag_position <= 31)
		flag_holder[0] |= (1 << flag_position);
	else if (flag_position > 31 && flag_position <= 63)
		flag_holder[1] |= (1 << flag_position);
	else if (flag_position > 63 && flag_position <= 95)
		flag_holder[2] |= (1 << flag_position);
	else if (flag_position > 95 && flag_position <= 127)
		flag_holder[3] |= (1 << flag_position);
	else if (flag_position > 127)
		flag_holder[4] |= (1 << flag_position);
}

void unset_flag(unsigned int flag_holder[], int flag_position)
{
	if (flag_position <= 31)
	{
		flag_holder[0] ^= (1 << flag_position);
		flag_holder[0] = ~flag_holder[0];
	}
	else if (flag_position > 31 && flag_position <= 63)
	{
		flag_holder[1] ^= (1 << flag_position);
		flag_holder[1] = ~flag_holder[1];
	}
	else if (flag_position > 63 && flag_position <= 95)
	{
		flag_holder[2] ^= (1 << flag_position);
		flag_holder[2] = ~flag_holder[2];
	}
	else if (flag_position > 95 && flag_position <= 127)
	{
		flag_holder[3] ^= (1 << flag_position);
		flag_holder[3] = ~flag_holder[3];
	}
	else if (flag_position > 127)
	{
		flag_holder[4] ^= (1 << flag_position);
		flag_holder[4] = ~flag_holder[4];
	}
}

int check_flag(unsigned int flag_holder[], int flag_position)
{
	int check_bit;
	if (flag_position <= 31)
		check_bit = (flag_holder[0] >> flag_position) & 1;
	else if(flag_position > 31 && flag_position <= 63)
		check_bit = (flag_holder[1] >> flag_position) & 1;
	else if(flag_position > 63 && flag_position <= 95)
		check_bit = (flag_holder[2] >> flag_position) & 1;
	else if(flag_position > 95 && flag_position <= 127)
		check_bit = (flag_holder[3] >> flag_position) & 1;
	else if(flag_position > 127)
		check_bit = (flag_holder[4] >> flag_position) & 1;
	if (check_bit == 1)
		return 1;
	return 0;
}

void display_32_flags_as_array(unsigned int flag_holder)
{
	int i;
	for (i = 0; i <= 159; i++)
	{
		printf("%d", check_flag(flag_holder, i));
		if ((i + 1) % 4 == 0)
		{
			printf(" ");
		}
		if ((i + 1) % 32 == 0)
		{
			printf("\n");
		}
	}
}
void display_flags(unsigned int flag_holder[], int size)
{
	display_32_flags_as_array(flag_holder);
}
