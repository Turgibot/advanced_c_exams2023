#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	struct node* next;
	struct node* prev;
	char data;
}Node;


Node* insertLast(Node* head, Node* newNode);
Node* createNode(char data);
void A(Node* t);
void B(Node* t);
void freeList(Node* head) {
	while (head) {
		Node* tmp = head;
		head = head->next;
		free(tmp);
	}
}
void main() {
	Node* head = createNode('a');
	head = insertLast(head, createNode('b'));
	head = insertLast(head, createNode('c'));
	head = insertLast(head, createNode('d'));
	head = insertLast(head, createNode('e'));

	head->next->next->prev = head;
	head->next->next->next->prev = head->next;
	head->next->next->next->next->prev = head->next->next;

	Node* t = head;
	while (t) {
		if (t->prev)
			A(t);
		else {
			B(t);
		}
		t = t->next;
	}
	
}
void A(Node* t) {
	Node* c = t;
	while(t->prev)
		t = t->prev;
	while (t != c) {
		printf("%c ", t->data);
		t = t->next;
	}
	printf("%c\n", c->data);
}

void B(Node* t) {
	Node* c = t;
	printf("%c ", c->data);
	while (c) {
		if (c->prev == t || c->prev && c->prev->prev == t)
			printf("%c ", c->data);
		c = c->next;
	}
	printf("\n");
}

Node* insertLast(Node* head, Node* newNode) {
	if (!head)
		return newNode;
	Node* tmp = head;
	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = newNode;
	return head;
}
Node* createNode(char data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->data = data;
}

