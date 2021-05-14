#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Node* new_node(int k)
{
	Node* temp = (Node*)malloc(sizeof(Node));

	temp->data = k;
	temp->next = NULL;

	return temp;
}

QUEUE queue_init_default(void)
{
	Queue* pQueue = (Queue*)malloc(sizeof(Queue));

	pQueue->front = pQueue->rear = NULL;

	return pQueue;
}

Status queue_enqueue(QUEUE hQueue, int k)
{	
	Queue* pQueue = (Queue*)hQueue;	//cast to known type
	Node* temp = new_node(k);

	if (pQueue->rear == NULL)
	{
		pQueue->front = pQueue->rear = temp;
		return FAILURE;
	}

	pQueue->rear->next = temp;
	pQueue->rear = temp;
	return SUCCESS;
}

Status queue_dequeue(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;	//cast to known type
	Node* temp;
	if (pQueue->front == NULL)
	{
		return FAILURE;
	}
	temp = pQueue->front;
	pQueue->front = pQueue->front->next;

	if (pQueue->front == NULL)
		pQueue->rear = NULL;

	free(temp);
	return SUCCESS;
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

int queue_front(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;	//cast to known type

	if (pQueue == NULL)
		return -1000000;

	return pQueue->front->data;
}

int number_of_trips(int boat_size, QUEUE hLeft_Queue, QUEUE hRight_Queue, int cars_in_left_q, int cars_in_right_q)
{
	Queue* pLeft_Queue = (Queue*)hLeft_Queue;	//cast to known type
	Queue* pRight_Queue = (Queue*)hRight_Queue;	//cast to known type

	int current_side = 0; //meaning left
	int available_size = boat_size;
	int total_trips = 0;

	while (cars_in_left_q > 0 || cars_in_right_q > 0)
	{
		if (current_side == 0)
		{
			if (cars_in_left_q == 0)
			{
				current_side = 1;
				available_size = boat_size;
				total_trips++;
			}
			while(cars_in_left_q > 0 && current_side == 0)
			{
				if ((available_size - queue_front(pLeft_Queue)) >= 0)
				{
					available_size = available_size - queue_front(pLeft_Queue);
					queue_dequeue(pLeft_Queue);
					cars_in_left_q--;
				}
				else
				{
					current_side = 1;
					available_size = boat_size;
					total_trips++;
				}
			}
		}
		if (current_side == 1)
		{
			if (cars_in_right_q == 0)
			{
				current_side = 0;
				available_size = boat_size;
				total_trips++;
			}
			while(cars_in_right_q > 0 && current_side == 1)
			{
				if ((available_size - queue_front(pRight_Queue)) >= 0)
				{
					available_size = available_size - queue_front(pRight_Queue);
					queue_dequeue(pRight_Queue);
					cars_in_right_q--;
				}
				else
				{
					current_side = 0;
					available_size = boat_size;
					total_trips++;
				}
			}
		}
	}

	total_trips++;
	return total_trips;
}

void ferry_loading(void)
{
	QUEUE hLeft_Queue = queue_init_default();
	int cars_in_left_q = 0;

	QUEUE hRight_Queue = queue_init_default();
	int cars_in_right_q = 0;

	int number_of_cases = 0;
	int car_size = 0;
	char side;
	int number_of_cars = 0, boat_size = 0;

	scanf("%d", &number_of_cases);
	clear_keyboard_buffer();
	for (; number_of_cases > 0; number_of_cases--)
	{

		scanf("%d %d", &boat_size, &number_of_cars);
		clear_keyboard_buffer();
		boat_size = boat_size * 100;

		while (number_of_cars > 0)
		{
			scanf("%d %c", &car_size, &side);
			clear_keyboard_buffer();
			if ((side == 'L') || (side == 'l'))
			{
				queue_enqueue(hLeft_Queue, car_size);
				cars_in_left_q++;
			}
			else if ((side == 'R') || (side == 'r'))
			{
				queue_enqueue(hRight_Queue, car_size);
				cars_in_right_q++;
			}
			number_of_cars--;
		}
		printf("%d\n", number_of_trips(boat_size, hLeft_Queue, hRight_Queue, cars_in_left_q, cars_in_right_q));
		number_of_cars = 0;
		cars_in_left_q = 0;
		cars_in_right_q = 0;
		boat_size = 0;
	}

	queue_destroy(&hLeft_Queue);
	queue_destroy(&hRight_Queue);
}

void queue_destroy(QUEUE* phQueue)
{
	Queue* pQueue = (Queue*)*phQueue;	//cast to known type
	Node* temp;

	while (pQueue->front != NULL)
	{
		temp = pQueue->front;
		pQueue->front = pQueue->front->next;
		free(temp);
	}
	free(pQueue);
	*phQueue = NULL;
}