#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}Node;

Node* createNode(int data);
void freeTreeMemory(Node* root);

void main() {
	Node* root = createNode(40);
	root->left = createNode(120);
	root->left->left = createNode(1);
	root->right = createNode(8);
	root->left->left->right = createNode(-34);
	root->left->right = createNode(99);
	root->right->right = createNode(77);

	freeTreeMemory(root);
}

Node* createNode(int data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	assert(temp);
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void freeTreeMemory(Node* root)
{
	if (root != NULL)
	{
		freeTreeMemory(root->left);
		freeTreeMemory(root->right);
		printf("Freed %d\n", root->data);
		free(root);
	}
}
