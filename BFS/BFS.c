#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
	struct node* next;
}Node;

typedef struct btree {
	Node* root;
}BTree;

typedef struct queue
{
	int count;
	Node* front;
	Node* rear;
} Queue;

Node* createNode(int data);
char isEmpty(const Queue Q);
void init(Queue* Q);
void enqueue(Queue* Q, Node* node);
Node* dequeue(Queue* Q);

void insert(Node* root, Node* newNode);
void freeTreeMemory(Node* root);

void printBFS(Node* root);

void main() {
	int values[] = { 20, 12, 30, 25, 80, 86, 83, 89, 60 };
	Node* root = createNode(40);
	for (int i = 0; i < 9; i++)
	{
		insert(root, createNode(values[i]));
	}
	printBFS(root);
	printf("\n terminating tree");
	freeTreeMemory(root);
}

void printBFS(Node* root) {
	Queue queue;
	init(&queue);
	enqueue(&queue, root);
	while (!isEmpty(queue)) {
		Node* tmp = dequeue(&queue);
		printf("%d ", tmp->data);
		if (tmp->left)
			enqueue(&queue, tmp->left);
		if(tmp->right)
			enqueue(&queue, tmp->right);
	}
}

Node* createNode(int data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	assert(temp);
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	temp->next = NULL;
	return temp;
}

void insert(Node* root, Node* newNode)
{
	if (!root) return;
	if (newNode->data <= root->data) //left subtree (<=)
		if (root->left == NULL)
			root->left = newNode;
		else
			insert(root->left, newNode);

	if (newNode->data > root->data) //right subtree  (>)
		if (root->right == NULL)
			root->right = newNode;
		else
			insert(root->right, newNode);
}

char isEmpty(const Queue Q) {
	return Q.front == NULL;
}

void init(Queue* Q) {
	Q->count = 0;
	Q->front = NULL;
	Q->rear = NULL;
}

void enqueue(Queue* Q, Node* node) {
	if (isEmpty(*Q))
		Q->front = node;
	else
		Q->rear->next = node;

	Q->rear = node;
	Q->count++;
}

Node* dequeue(Queue* Q) {
	if (isEmpty(*Q))
	{
		printf("Queue empty\n"); return 0;
	}
	Node* node = Q->front;
	Q->front = Q->front->next;
	if (Q->front == NULL) // there was only one item in the queue
		Q->rear = NULL;
	Q->count--;
	return node;
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
