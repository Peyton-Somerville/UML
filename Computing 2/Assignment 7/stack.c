#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node;
typedef struct node Node;
struct node
{
	char data;
	Node* next;
};

struct stack
{
	Node* top;
};
typedef struct stack Stack;

STACK stack_init_default(void)
{
	Stack* pStack = NULL;
	pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->top = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, char item)
{
	Stack* pStack = (Stack*)hStack;	//cast to known type
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}

	temp->data = item;
	temp->next = pStack->top;
	pStack->top = temp;
	return SUCCESS;
}

Status stack_pop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;	//cast to known type
	Node* temp;
	if (pStack->top == NULL)
	{
		return FAILURE;
	}
	temp = pStack->top;
	pStack->top = pStack->top->next;
	free(temp);
	return SUCCESS;
}
//is empty
Boolean stack_empty(STACK* hStack)
{
	Stack* pStack = (Stack*)hStack;	//cast to known type

	return (Boolean)(pStack->top == NULL);
}

char stack_top(STACK hStack, Status* pStatus)
{
	Stack* pStack = (Stack*)hStack;	//cast to known type
	if (stack_empty(hStack))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return NULL;
	}
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pStack->top->data;
}

void check_string(void)
{
	STACK hStack = NULL;
	char c[1000000] = "\0";
	int flag = 0;
	int i = 0;
	int size;

	hStack = stack_init_default();

	c[i] = getc(stdin);
	while (c[i] != EOF && c[i] != '\n')
	{
		i++;
		c[i] = getc(stdin);
	}

	size = i;
	for (i = 0; i < size; i++)
	{
		if (c[i] == '(' || c[i] == '{' || c[i] == '[')
		{
			stack_push(hStack, c[i]);
		}
		else if (c[i] == ')' || c[i] == '}' || c[i] == ']')
		{
			if (is_match(stack_top(hStack, NULL), c[i]) == FALSE)
			{
				printf("No\n");
				flag = 1;
				break;
			}
			else
			{
				stack_pop(hStack);
			}
		}
	}

	if (stack_empty(hStack) && flag != 1)
		printf("Yes\n");
	else if(flag != 1)
		printf("No\n");

	destroy_stack(&hStack);
}

Boolean is_match(char x, char y)
{
	if (x == '(' && y == ')')
		return TRUE;
	else if (x == '{' && y == '}')
		return TRUE;
	else if (x == '[' && y == ']')
		return TRUE;
	else
		return FALSE;
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

void destroy_stack(STACK* phStack)
{
	Stack* pStack = (Stack*)*phStack;	//cast to known type
	Node* temp;
	while (pStack->top != NULL)
	{
		temp = pStack->top;
		pStack->top = pStack->top->next;
		free(temp);
	}
	free(pStack);
	*phStack = NULL;
}