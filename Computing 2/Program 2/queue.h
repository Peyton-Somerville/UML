#pragma once
#include <stdio.h>
#include "status.h"

typedef void* QUEUE;

struct node;
typedef struct node Node;
struct node
{
	int data;
	Node* next;
};

struct queue
{
	Node* front;
	Node* rear;
};
typedef struct queue Queue;

Node* new_node(int k);

QUEUE queue_init_default(void);

Status queue_enqueue(QUEUE hQueue, int k);

Status queue_dequeue(QUEUE hQueue);

void clear_keyboard_buffer(void);

int queue_front(QUEUE hQueue);

int number_of_trips(int boat_size, QUEUE hLeft_Queue, QUEUE hRight_Queue, int cars_in_left_q, int cars_in_right_q);

void ferry_loading(void);

void queue_destroy(QUEUE* phQueue);