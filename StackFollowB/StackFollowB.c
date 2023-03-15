#define _CRT_SECURE_NO_WARNINGS
#define MAXSIZE  6
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} node;

typedef struct {
	node* top;
} Stack;

//Note the signatures of the functions are the same as in the array implementation!

void initStack(Stack* stack);
char isStackEmpty(const Stack* stack);
void push(Stack* stack, int n);
int  pop(Stack* stack);
void display(const Stack* stack);
void removeFirst(Stack* stack);
node* addFirst(node* head, int val);
void print(node* head);
typedef struct elem {// an element in the queue
	int val;
	struct elem* next;
} elem;

typedef struct queue
{
	int count;
	elem* front;
	elem* rear;
} Queue;


//Initializes front and rear
void initQueue(Queue* Q);
void enqueue(Queue* Q, int n);
int dequeue(Queue* Q);
void printQueue(const Queue Q);
char isQueueEmpty(const Queue Q); //returns 1 if Q is Empty- Otherwise 0.
char isFull(Queue Q); //returns 1 if Q is Full Otherwise, 0.
void A(Stack* s1, int b, int d);


void A(Stack* s1, int b, int d) {
	Queue q;
	initQueue(&q);
	Stack s2;
	initStack(&s2);
	int c = 0;
	while (!isStackEmpty(s1)) {
		enqueue(&q, pop(s1));
		c++;
	}
	if (b + d >= c) {
		printf("Illegal");
		return;
	}
	c = 0;
	while (!isQueueEmpty(q)) {
		if (c >= b && c < (b + d)) {
			push(s1, dequeue(&q));
		}
		else {
			push(&s2, dequeue(&q));
		}
		c++;
	}
	while (!isStackEmpty(&s2)) {
		push(s1, pop(&s2));
	}
}

int main() {
	Stack stack;
	initStack(&stack);
	int values[] = { 40, 20, 12, 30, 25, 80 };
	for (int i = 0; i < MAXSIZE; i++)
	{
		push(&stack, values[i]);
	}
	display(&stack);
	A(&stack, 2, 7);
	display(&stack);
}



void initStack(Stack* stack) {
	stack->top = NULL;
}

char isStackEmpty(const Stack* stack) {
	return (!(stack->top));
}

void push(Stack* stack, int val) {
	stack->top = addFirst(stack->top, val);
}

node* addFirst(node* head, int val)
{
	node* tmp = (struct node*)malloc(sizeof(node));
	if (tmp) {
		tmp->val = val;
		tmp->next = head;
		return tmp;
	}
	else {
		puts("allocation failed - item not added");
		return head;
	}
}

int pop(Stack* stack) {
	if (isStackEmpty(stack)) {
		printf("\nSTACK  IS EMPTY");
		return;
	}
	int val = stack->top->val;
	removeFirst(stack); //pop it from the stack    
	return val;
}

void removeFirst(Stack* stack) {
	node* tmp = stack->top;
	stack->top = stack->top->next;
	free(tmp);
}

void display(Stack* S)
{
	print(S->top);
	printf("\n");
}


void print(node* head)
{
	node* tmp;
	tmp = head;
	while (tmp != NULL) {
		printf(" % d ", tmp->val);
		tmp = tmp->next;
	}
}


void initQueue(Queue* Q) {
	Q->count = 0;
	Q->front = NULL;
	Q->rear = NULL;
}

char isFull(const Queue Q) {
	return Q.count == MAXSIZE;
}
char isQueueEmpty(const Queue Q) {
	return Q.front == NULL;
}
void enqueue(Queue* Q, int val) {
	if (isFull(*Q)) { printf("Queue is Full\n"); return; }
	elem* element = (elem*)malloc(sizeof(elem));
	if (!element) { printf("Mem Allocation failed\n"); return; }
	element->val = val;
	element->next = NULL;

	if (isQueueEmpty(*Q))
		Q->front = element;
	else
		Q->rear->next = element;

	Q->rear = element;
	Q->count++;
}

int dequeue(Queue* Q) {
	
	int res = Q->front->val;
	elem* elemToDelete = Q->front;
	Q->front = Q->front->next;

	if (Q->front == NULL) // there was only one item in the queue
		Q->rear = NULL;

	Q->count--;
	free(elemToDelete);
	return res;
}

void printQueue(const Queue Q) {

	elem* elemToPrint = Q.front;
	while (elemToPrint) {
		printf("%d, ", elemToPrint->val);
		elemToPrint = elemToPrint->next;
	}

}
