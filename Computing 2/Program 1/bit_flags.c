/*
	Author: Peyton Somerville
	Date: 4/11/19
	Effort: Around 2 and a half hours.
	Purpose: This program uses a data structure to store bits.
	Interface proposal: I would add a function to print out the bits called 'display_bit_flags'. This function would cut down on the code needed in the main function, and make the program easier to read.
*/

#include <stdlib.h>
#include <stdio.h>
#include "bit_flags.h"

struct bit_flags
{
	int size;
	int capacity;
	int* data;
};
typedef struct bit_flags Bit_flags;

//Precondition: number of bits is a positive integer.
//Postcondition: Returns the handle to a valid Bit_flags object that has the ability to store up to
// number_of_bits bits but currently all flags are set at zero. Returns NULL on failure. The container
// is assumed to hold size=number_of_bits after the init function runs.
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags = NULL;
	pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
	if (pBit_flags != NULL)
	{
		pBit_flags->size = number_of_bits;
		pBit_flags->capacity = number_of_bits + 1;
		pBit_flags->data = (int*)malloc(sizeof(int) * pBit_flags->capacity);
		if (pBit_flags->data == NULL)
		{
			free(pBit_flags);
			pBit_flags = NULL;
		}
	}
	return pBit_flags;
}

//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 1. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation (except the one being set) will be set as zero.
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;	//cast to known type
	int* temp;
	int i;
	int difference;

	if (flag_position < 1)
	{
		printf("Flag position must be at least 1.\n");
		return FAILURE;
	}
	else if(flag_position > pBit_flags->size)
	{
		difference = flag_position - pBit_flags->size;
		temp = (int*)malloc(sizeof(int) * (pBit_flags->capacity + difference));
		if (temp == NULL)
		{
			return FAILURE;
		}

		for (i = 0; i < pBit_flags->capacity; ++i)
		{
			temp[i] = pBit_flags->data[i];
		}
		free(pBit_flags->data);

		pBit_flags->data = temp;
		pBit_flags->size += difference;
		pBit_flags->capacity += difference;
	}

	if (flag_position >= 1 && flag_position <= pBit_flags->size)
		pBit_flags->data[flag_position - 1] = 1;

	return SUCCESS;
}

//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 0. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation will be set as zero.
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;	//cast to known type
	int* temp;
	int i;
	int difference;

	if (flag_position < 1)
	{
		printf("Flag position must be at least 1.\n");
		return FAILURE;
	}
	else if (flag_position > pBit_flags->size)
	{
		difference = flag_position - pBit_flags->size;
		temp = (int*)malloc(sizeof(int) * (pBit_flags->capacity + difference));
		if (temp == NULL)
			return FAILURE;

		for (i = 0; i < pBit_flags->capacity; ++i)
		{
			temp[i] = pBit_flags->data[i];
		}
		free(pBit_flags->data);

		pBit_flags->data = temp;
		pBit_flags->size += difference;
		pBit_flags->capacity += difference;
	}

	if (flag_position >= 1 && flag_position <= pBit_flags->size)
		pBit_flags->data[flag_position - 1] = 0;

	return SUCCESS;
}

//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the value of the flag at index flag_position if it is in bounds or -1 otherwise.
int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;	//cast to known type
	int check_bit;
	if (flag_position >= 1 && flag_position <= pBit_flags->size)
	{
		if (pBit_flags->data[flag_position - 1] == 1 || pBit_flags->data[flag_position - 1] == 0)
			check_bit = pBit_flags->data[flag_position - 1];
		else
			check_bit = 0;
	}
	else
		return -1;
	return check_bit;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;	//cast to known type
	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;	//cast to known type
	return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;	//cast to known type

	free(pBit_flags->data);
	free(pBit_flags);
	*phBit_flags == NULL;
}