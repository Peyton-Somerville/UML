#include "generic.h"

typedef void* VECTOR;

VECTOR vector_init_default(int word_length);
int vector_get_word_length(VECTOR hVector);
void vector_push_back(VECTOR hVector, char* temp, int position);
void vector_at(VECTOR hVector, int index);
void vector_destroy(VECTOR* phVector);

#ifndef VECTOR_H
#define VECTOR_H
#include "my_string.h"
#include "generic.h"

typedef void* G_VECTOR;

G_VECTOR g_vector_init_default(void(*string_assign)(Item_ptr, Item), void(*string_destroy)(Item_ptr), int letter_count);

//add item
void g_vector_push_back(G_VECTOR hVector, const char* data, int position);

//see a particular value
Item g_vector_at(G_VECTOR hVector, int index);

// return word length
int g_vector_get_word_length(G_VECTOR hVector);

int g_vector_get_size(G_VECTOR hVector);
int g_vector_get_capacity(G_VECTOR hVector);

void print_vector_strings(G_VECTOR string);

//destroy the objects
void g_vector_destroy(G_VECTOR* phVector);

#endif