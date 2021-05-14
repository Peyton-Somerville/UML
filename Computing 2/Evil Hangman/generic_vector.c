#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

struct g_vector
{
	int word_length;
	int size;
	int capacity;
	MY_STRING* words;
	void(*string_assign)(Item_ptr, Item);
	void(*string_destroy)(Item_ptr);
};
typedef struct g_vector G_Vector;


G_VECTOR g_vector_init_default(void(*string_assign)(Item_ptr, Item), void(*string_destroy)(Item_ptr), int letter_count)
{
	G_Vector* pVector;
	//int i;

	pVector = (G_Vector*)malloc(sizeof(G_Vector));
	if (pVector != NULL)
	{
		pVector->word_length = letter_count;
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->string_destroy = string_destroy;
		pVector->string_assign = string_assign;
		pVector->words = (MY_STRING*)malloc(sizeof(MY_STRING) * (pVector->capacity));
		if (pVector->words == NULL)
		{
			//object was not created
			free(pVector);
			pVector = NULL;
		}
		else
		{
			for (i = 0; i < pVector->size + 1; i++)
				pVector->words[i] = NULL;
		}
	}

	return pVector;
}

void g_vector_push_back(G_VECTOR hVector, const char* data, int position)
{
	G_Vector* pVector = (G_Vector*)hVector;
	MY_STRING temp = NULL;

	if (pVector->size >= pVector->capacity)
	{
		temp = (MY_STRING*)malloc(sizeof(MY_STRING) * (pVector->capacity) * 2);
		pVector->words = temp;
		pVector->capacity *= 2;
	}

	pVector->words[position] = my_string_init_c_string(data);
	pVector->size++;

	pVector->string_assign(&pVector->data[pVector->size], item);
}


Item g_vector_at(G_VECTOR hVector, int index) 
{
	G_Vector* pVector = (G_Vector*)hVector;
	if (index < 0 || index >= pVector->capacity) {
		return NULL;
	}
	return pVector->data[index];    //pG_VECTOR->data+index;
}

int  g_vector_get_word_length(G_VECTOR hVector)
{
	G_Vector* pVector = (G_Vector*)hVector;
	return pVector->word_length;
}

int g_vector_get_size(G_VECTOR hVector)
{
	G_Vector* pVector = (G_Vector*)hVector;
	return pVector->size;
}

int g_vector_get_capacity(G_VECTOR hVector)
{
	G_Vector* pVector = (G_Vector*)hVector;
	return pVector->capacity;
}

void print_vector_strings(G_VECTOR hVector)
{
	int i;
	G_Vector* temp = (G_Vector*)hVector;

	if (temp == NULL)
	{
		printf("BIG OOF\n");
		return;
	}

	for (i = 0; i < g_vector_get_size(temp); i++)
	{
		my_string_insertion(temp->words[i], stdout);
		//printf("\n");
	}
}

void g_vector_destroy(G_VECTOR* phG_Vector)
{
	G_Vector* pVector = (G_Vector*)*phG_Vector;
	int i;

	for (i = 0; i < pVector->capacity; i++)
	{
		if (pVector->words[i] != NULL)
		{
			my_string_destroy((Item*)&pVector->words[i]);
		}
	}

	free(pVector->words);
	free(pVector);
	*phG_Vector = NULL;
}







//struct vector
//{
//	int word_length;
//	MY_STRING* words;
//};
//typedef struct vector Vector;
//
//VECTOR vector_init_default(int word_length)
//{
//	Vector* pVector = NULL;
//
//	pVector = (Vector*)malloc(sizeof(Vector));
//	if (pVector != NULL)
//	{
//		pVector->word_length = word_length;
//		pVector->words = (MY_STRING*)malloc(sizeof(MY_STRING) * (pVector->word_length + 1));
//		if (pVector->words == NULL)
//		{
//			free(pVector);
//			pVector = NULL;
//		}
//	}
//	return pVector;
//}
//
//int vector_get_word_length(VECTOR hVector)
//{
//	Vector* pVector = (Vector*)hVector;	//cast to known type
//	return pVector->word_length;
//}
//
//void vector_push_back(VECTOR hVector, char* temp, int position)
//{
//	Vector* pVector = (Vector*)hVector;	//cast to known type
//	
//	pVector->words[position] = temp;
//}
//
//void vector_at(VECTOR hVector, int index)
//{
//	Vector* pVector = (Vector*)hVector;	//cast to known type
//	
//	my_string_insertion(pVector->words[index], stdout);
//}
//
//void vector_destroy(VECTOR* phVector)
//{
//	Vector* pVector = (Vector*)*phVector;	//cast to known type
//	int i = 0;
//
//	while (pVector->words != NULL)
//	{
//		my_string_destroy((Item*)&pVector->words[i]);
//		i++; 
//	}
//	//free(pVector->words);
//	free(pVector);
//	*phVector = NULL;
//}


