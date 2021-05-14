#include <stdlib.h>
#include <stdio.h>
#include "bit_flags.h"

int main(void)
{
	BIT_FLAGS hBit_flags = NULL;
	int size, capacity;
	int bit;
	int number_of_bits = 4;
	int i;

	hBit_flags = bit_flags_init_number_of_bits(number_of_bits);
	if (hBit_flags == NULL)
	{
		printf("Did not create an object\n");
		exit(1);
	}

	size = bit_flags_get_size(hBit_flags);
	capacity = bit_flags_get_capacity(hBit_flags);

	printf("Size: %d\nCapacity: %d\n", size, capacity);

	bit_flags_set_flag(hBit_flags, 1);
	bit_flags_set_flag(hBit_flags, 2);
	bit_flags_set_flag(hBit_flags, 9);

	bit_flags_unset_flag(hBit_flags, 15);

	size = bit_flags_get_size(hBit_flags);
	capacity = bit_flags_get_capacity(hBit_flags);

	printf("Size: %d\nCapacity: %d\n", size, capacity);

	for (i = 1; i <= size; i++)
	{
		bit = bit_flags_check_flag(hBit_flags, i);
		printf("%d", bit);
	}
	printf("\n");

	bit_flags_destroy(&hBit_flags);
}