#include <ctype.h>
#include "my_string.h"

struct string
{
	int size;
	int capacity;
	char* data;
};
typedef struct string String;

MY_STRING my_string_init_default(void)
{
	String* pString = NULL;
	pString = (String*)malloc(sizeof(String));
	if (pString != NULL)
	{
		pString->size = 0;
		pString->capacity = 7;
		pString->data = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->data == NULL)
		{
			free(pString);
			pString = NULL;
		}
	}
	return pString;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	String* pString = NULL;
	int i;
	int size;
	for (size = 0; c_string[size] != '\0'; size++)
	{
	}

	pString = (String*)malloc(sizeof(String));
	if (pString != NULL)
	{
		pString->size = size;
		pString->capacity = size + 1;
		pString->data = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->data == NULL)
		{
			free(pString);
			pString = NULL;
		}
		for (i = 0; i < size; i++)
			pString->data[i] = c_string[i];
	}
	return pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	String* pLeft_string = (String*)hLeft_string;
	String* pRight_string = (String*)hRight_string;
	int left_size;
	int right_size;

	pLeft_string = my_string_init_c_string(hLeft_string);
	left_size = my_string_get_size(pLeft_string);

	//printf("Left string '%s'- Size: %d Capacity: %d\n", (char*)hLeft_string, left_size, my_string_get_capacity(pLeft_string)); 

	my_string_destroy((Item*)&pLeft_string);

	pRight_string = my_string_init_c_string(hRight_string);
	right_size = my_string_get_size(pRight_string);

	//printf("Right string '%s'- Size: %d Capacity: %d\n", (char*)hRight_string, right_size, my_string_get_capacity(pRight_string));

	my_string_destroy((Item*)&pRight_string);

	return left_size - right_size;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	String* pString = (String*)hMy_string;
	int i = 0;
	char c;

	pString->size = 0;
	pString->capacity = 1;

	c = getc(fp);

	while (c != EOF && isspace(c))
	{
		c = getc(fp);
	}

	if (c == EOF)
	{
		return FAILURE;
	}

	pString->data[i] = (char)c;
	pString->size++;
	pString->capacity++;
	i++;

	c = getc(fp); //try

	//is the file empty, do i want it, do i have room 
	while (c != EOF && !isspace(c)) //check
	{
		pString->data[i] = c; //do
		pString->size++;
		pString->capacity++;
		i++;
		c = getc(fp); //try
	}

	if (c != EOF)
	{
		ungetc(c, fp);
	}
	pString->data[i] = '\0';

	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	String* pString = (String*)hMy_string;

	if (pString == NULL)
		return FAILURE;

	printf("%s\n", (char*)pString->data);

	return SUCCESS;
}

void my_string_destroy(Item* pItem)
{
	String* pString = (Item)*pItem;

	free(pString->data);
	free(pString);
	*pItem = NULL;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	String* pString = (String*)hMy_string;	//cast to known type
	char* temp;
	int i;

	if (pString->size >= pString->capacity)
	{
		temp = (char*)malloc(sizeof(char)*pString->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}

		for (i = 0; i < pString->capacity; ++i)
		{
			temp[i] = pString->data[i];
		}
		free(pString->data);

		pString->data = temp;
		pString->capacity *= 2;
	}

	pString->data[pString->size] = item;
	pString->size++;
	pString->capacity++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;	//cast to known type

	if (pString->size <= 0)
	{
		return FAILURE;
	}

	pString->size--;
	pString->capacity--;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	String* pString = (String*)hMy_string;	//cast to known type

	if (index < 0 || index >= pString->size)
	{
		return NULL;
	}

	return &pString->data[index];
}

char* my_string_c_str(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;	//cast to known type
	char* temp;
	int i;

	if (pString->size >= pString->capacity)
	{
		temp = (char*)malloc(sizeof(char)*pString->capacity + 1);
		if (temp == NULL)
		{
			return FAILURE;
		}

		for (i = 0; i < pString->capacity; ++i)
		{
			temp[i] = pString->data[i];
		}
		free(pString->data);

		pString->data = temp;
		pString->capacity += 1;
	}

	pString->data[pString->size] = '\0';

	return &pString->data[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	String* pStringAppend = (String*)hAppend;	//cast to known type
	int i;
	int result;

	for (i = 0; i < my_string_get_size(hAppend); i++)
	{
		result = my_string_push_back(hResult, pStringAppend->data[i]);
		if (result == 0)
			return FAILURE;
	}

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;	//cast to known type

	if (pString->size > 0)
		return FALSE;
	return TRUE;
}

void my_string_assignment(Item* pLeft, Item Right)
{
	my_string_concat((MY_STRING)*pLeft, (MY_STRING)Right);
}