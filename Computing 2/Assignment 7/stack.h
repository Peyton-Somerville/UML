#pragma once 
#include "status.h"

typedef void* STACK;
STACK stack_init_default(void);
// use stack
// push
// Preconditions: hStack is a handle to a valid object 
// if item is added return SUCCESS, FAILURE otherwise
Status stack_push(STACK hStack, char item);

//pop
// Preconditions: hStack is a handle to a valid object 
// Postconditions: return FAILURE or SUCCESS 
Status stack_pop(STACK hStack);

// top
char stack_top(STACK hStack, Status* pStatus);

//is empty?
Boolean stack_empty(STACK* hStack);

//is string balanced?
void check_string(void);

Boolean is_match(char x, char y);

void clear_keyboard_buffer(void);

//destroy stack
void destroy_stack(STACK* phStack);