//#include "generic_vector.h"
//#include "my_string.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include "associativearray.h"
//
//
//typedef struct word_key Key;
//
//typedef struct node Node;
//
//struct node
//{
//	Node* left;
//	Node* right;
//	Key* data;
//};
//
//Node* root = NULL;
//
//struct word_key
//{
//	Item word;
//	Item key;
//	Item vector;
//};
//
//
//Item create_node(Item data, char* guess)
//{
//	Node* node = NULL;
//	node = (Node*)malloc(sizeof(Node));
//
//	if (node == NULL)
//	{
//		printf("BigOooof\n");
//		return NULL;
//	}
//
//	node->left = NULL;
//	node->right = NULL;
//
//	node->data = create_key(data, guess);
//
//	return node;
//}
//
//Status insert_node(Item data, char* guess)
//{
//	Node* next = NULL;
//	Item string = NULL;
//	Item temp = NULL;
//
//	string = generate_string_key(data);
//	temp = my_string_init_default();
//
//	for (int i = 0; i < newstrlen(guess) + 1; i++)
//	{
//		if (guess[i] == '\0')
//		{
//			break;
//		}
//		get_word_key_value(string, temp, data, guess[i]);
//	}
//
//	if (data == NULL)
//	{
//		printf("Initial data is NULL\n");
//	}
//	if (root == NULL)
//	{
//		next = create_node(data, guess);
//		root = next;
//		my_string_destroy((Item*)&string);
//		my_string_destroy((Item*)&temp);
//		return SUCCESS;
//	}
//	next = root;
//
//	while (next != NULL)
//	{
//		if (my_string_compare(next->data->key, temp) < 0)
//		{
//			if (next->right == NULL)
//			{
//				next->right = create_node(data, guess);
//				break;
//			}
//			next = next->right;
//		}
//		else if (my_string_compare(next->data->key, temp) > 0)
//		{
//			if (next->left == NULL)
//			{
//				next->left = create_node(data, guess);
//				break;
//			}
//			next = next->left;
//		}
//		else if (my_string_compare(next->data->key, temp) == 0)
//		{
//			g_vector_push_back(next->data->vector, data);
//			my_string_destroy((Item*)&string);
//			my_string_destroy((Item*)&temp);
//			return FAILURE;
//		}
//	}
//	my_string_destroy((Item*)&string);
//	my_string_destroy((Item*)&temp);
//
//	return SUCCESS;
//}
//
//
//void tree_init(void)
//{
//	root = malloc(sizeof(Node*));
//	root = NULL;
//}
//
//Item create_key(Item string, char* guess)
//{
//	int i, j;
//	Item word = NULL;
//	Item temp = NULL;
//	word = generate_string_key(string);
//	temp = my_string_init_default();
//
//	for (i = 0; i < my_string_get_size(string) + 1; i++)
//	{
//		if (guess[i] == '\0')
//		{
//			break;
//		}
//		for (j = 0; j < strlen(guess); j++)
//		{
//			get_word_key_value(word, temp, string, guess[j]);
//		}
//		word = temp;
//	}
//
//	Key* temp = NULL;
//	temp = malloc(sizeof(Key));
//	temp->word = string;
//	temp->key = temp;
//	temp->vector = NULL;
//	temp->vector = g_vector_init_default(my_string_assignment, my_string_destroy);
//	g_vector_push_back(temp->vector, string);
//	// my_string_destroy(&temp);
//	// my_string_destroy(&word);
//
//	return temp;
//}
//
//
//void print_tree(void)
//{
//	Node* temp = root;
//	inorder_printing(temp);
//}
//
//void inorder_printing(Item temp)
//{
//	Node* tree = (Node*)temp;
//	// my_string_insertion(tree->data->family, stdout);
//
//	if (tree == NULL)
//	{
//		return;
//	}
//	printf("Key: ");
//	my_string_insertion(tree->data->key, stdout);
//	printf("\nSize of Vector: %d", g_vector_get_size(tree->data->vector));
//
//	printf("\n");
//	inorder_printing(tree->left);
//	inorder_printing(tree->right);
//
//}
//
//void find_largest_vector(void)
//{
//	Node* temp = root;
//	vector_search(temp);
//	printf("Size of largest vector: %d\n", g_vector_get_size(root->data->vector));
//	printf("Key for largest vector: ");
//	my_string_insertion(root->data->key, stdout);
//	printf("\n");
//}
//
//void vector_search(Item temp)
//{
//	Node* tree = (Node*)temp;
//	if (tree == NULL)
//	{
//		return;
//	}
//	if (g_vector_get_size(tree->data->vector) > g_vector_get_size(root->data->vector))
//	{
//		root = tree;
//	}
//	vector_search(tree->left);
//	vector_search(tree->right);
//
//}
//
//void destroy_vectors(void)
//{
//	Node* temp = root;
//	destroy_smaller_vectors(temp);
//	printf("\n");
//}
//
//void destroy_smaller_vectors(Item temp)
//{
//	vector_search(temp);
//
//}
//
//Status finaloutput(void)
//{
//	Node* temp = root;
//	if (root == NULL)
//	{
//		printf("You won! Congratulations!\n");
//		return SUCCESS;
//	}
//	else if (root->data != NULL)
//	{
//		if (my_string_compare(temp->data->word, temp->data->key) == 0)
//		{
//			printf("You win!!\nCongratulations on guessing: ");
//			my_string_insertion(temp->data->word, stdout);
//			printf("\n");
//			exit;
//		}
//
//		printf("Thank you for playing!\n");
//		printf("The correct word was: ");
//		my_string_insertion(temp->data->word, stdout);
//		printf("\n");
//		return FAILURE;
//	}
//	else
//	{
//		printf("Something else\n");
//		my_string_insertion(temp->data->word, stdout);
//
//	}
//}
//
//Item generate_key_tree(int size, char guess, Item tree)
//{
//
//	vector_search(root);
//	tree = root;
//
//	if (tree == NULL)
//	{
//		printf("Root is NULL\n");
//		//create a tree
//	}
//	Item stringptr = NULL;
//	stringptr = my_string_init_default();
//	Item string = NULL;
//	string = my_string_init_default();
//
//	while (!(g_vector_empty(tree)))
//	{
//		g_vector_pop_back(tree);
//	}
//
//	if (temp->data == NULL)
//	{
//		printf("DATA NULL\n");
//	}
//
//	get_word_key_value(temp->data->key, string, temp->data->word, guess);
//	temp->data->key = string;
//
//	for (int i = 0; i < g_vector_get_size(temp->data->vector); i++)
//	{
//		stringptr = g_vector_at(temp->data->vector, i);
//		g_vector_push_back(tree, stringptr);
//		// my_string_destroy(&stringptr);
//		// stringptr = my_string_init_default();
//	}
//	temp->data->vector = tree;
//	root = NULL;
//	return tree;
//
//
//}
//
//void destroy(void)
//{
//	node_destroy(root);
//}
//
//void node_destroy(Item node)
//{
//	Node* temp = (Node*)node;
//	if (temp == NULL)
//	{
//		return;
//	}
//	node_destroy(temp->right);
//	node_destroy(temp->left);
//	key_destroy(temp->data);
//
//	free(temp);
//	temp = NULL;
//
//
//
//
//	// my_string_destroy(&(temp->data->word));
//	// my_string_destroy(&(temp->data->key));
//	// g_vector_destroy(&(temp->data->vector));
//
//	// free(temp->data);
//
//	// my_string_destroy(&wordstr);
//	// my_string_destroy(&keystr);
//	// g_vector_destroy(&vec);
//
//}
//
//void key_destroy(Item node)
//{
//	Key* temp = (Key*)node;
//	my_string_destroy(&(temp->word));
//	my_string_destroy(&(temp->key));
//	g_vector_destroy(&(temp->vector));
//	free(temp);
//	temp = NULL;
//
//}
//
//int newstrlen(const char *s)
//{
//	const char *p = s;
//
//	while (*p) ++p;
//
//	return p - s;
//}