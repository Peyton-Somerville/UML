/*
	Program: Reverse List
	Author: Peyton Somerville
	Date: 2/10/19
	Time spent: About an hour.
	Purpose: This program reverses the order of a linked list without using another list.
*/

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

//declare your function here.
void reverse_list(Node** head);

int main(int argc, char* argv[])
{
	Node* head = NULL;
	int i;
	Node* temp;

	//set up a test list with values 9->8->7->...->0
	for (i = 0; i < 10; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory?\n");
			exit(1);
		}
		temp->data = i;
		temp->next = head;
		head = temp;
	}

	//call your function to reverse the list (should work for any list given the head node).
	reverse_list(&head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

//Define your function here
void reverse_list(Node** head)
{
	Node* previous = NULL;
	Node* top = *head;
	Node* next = NULL;

	while (top != NULL)
	{
		next = top->next;
		top->next = previous;
		previous = top;
		top = next;
	}
	*head = previous;
}
