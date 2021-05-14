/*
	Program: Number Filter
	Author: Peyton Somerville
	Date: 4/8/19
	Time Spent: A couple of hours.
	Purpose: The purpose of this program is to utilize data structures to sort large inputs of integers.
*/

#include <stdio.h>

struct node;
typedef struct node Node;
struct node
{
	int data;
	Node* left;
	Node* right;
};

void tree_insert(Node** pRoot, int item);
void inorder_traversal(Node* root);
void tree_destroy(Node** pRoot);

int main(void)
{
	Node* root = NULL;
	int num = 0;
	int size = 0;

	while (num != -1)
	{
		scanf("%d", &num);
		if (num >= 0)
		{
			tree_insert(&root, num);
			size++;
		}
	}

	inorder_traversal(root);

	tree_destroy(&root);

	return 0;
}

void tree_insert(Node** pRoot, int item)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Node*)malloc(sizeof(Node));
		if (*pRoot == NULL)
			exit(1);

		(*pRoot)->data = item;
		(*pRoot)->left = NULL;
		(*pRoot)->right = NULL;
	}
	else
	{
		if (item < (*pRoot)->data)
			tree_insert(&(*pRoot)->left, item);
		else if(item > (*pRoot)->data)
			tree_insert(&(*pRoot)->right, item);
	}
}

void inorder_traversal(Node* root)
{
	if (root != NULL)
	{
		inorder_traversal(root->left);
		printf("%d\n", root->data);
		inorder_traversal(root->right);
	}
}

void tree_destroy(Node** pRoot)
{
	if (*pRoot != NULL)
	{
		tree_destroy(&(*pRoot)->left);
		tree_destroy(&(*pRoot)->right);
		free(*pRoot);
		*pRoot = NULL;
	}
}