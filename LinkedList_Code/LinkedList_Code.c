#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	struct node* leader;
	struct node* next;
	int data;
}Node;

typedef struct team {
	Node* leader;
	int size;
}Team;

Node* insertLast(Node* head, Node* newNode);
Node* remove(Node* head, Node* nodeToRemove);
void show(Node* head);

Node* createNode(int data);
void addToTeam(Team* team, Node* newNode);
int isTeamLeader(Node node);
Node* changeLeader(Team team, Node* newLeader);
void removeFromTeam(Node* node, Team* team);
int main()
{
	Team team1 = { NULL, 0 };
	Team team2 = { NULL, 0 };
	addToTeam(&team1, createNode(1));
	addToTeam(&team1, createNode(2));
	addToTeam(&team1, createNode(3));
	addToTeam(&team2, createNode(4));
	addToTeam(&team2, createNode(5));
	addToTeam(&team2, createNode(6));


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
Node* remove(Node* head, Node* nodeToRemove) {
	if (head == nodeToRemove) {
		head = head->next;
		free(nodeToRemove);
	}
	else {
		Node* tmp = head;
		while (tmp->next && tmp->next != nodeToRemove) {
			tmp = tmp->next;
		}
		if (!tmp->next) {
			printf("Node is not in the list");
		}
		else {
			tmp->next = nodeToRemove->next;
			free(nodeToRemove);
		}
	}
	return head;
}

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->next = NULL;
	newNode->leader = NULL;
	newNode->data = data;
}
//2
void addToTeam(Team* team, Node* newNode) {
	team->leader = insertLast(team->leader, newNode);
	newNode->leader = team->leader;
	(team->size)++;
}
//1
int isTeamLeader(Node node) {
	return node.leader == NULL;
}
//3
Node* changeLeader(Team team, Node* newLeader) {
	if (newLeader->leader != team.leader) {
		printf("New Leader is not in the list");
	}
	Node* currLeader = team.leader;
	if (currLeader != newLeader && currLeader == newLeader->leader) {
		//find newLeader in the list
		Node* tmp = currLeader;
		while (tmp->next && tmp->next != newLeader)
			tmp = tmp->next;

		tmp->next = newLeader->next;
		newLeader->next = currLeader;
		newLeader->leader = NULL;
		tmp = newLeader->next;
		while (tmp)
		{
			tmp->leader = newLeader;
			tmp = tmp->next;
		}
		return newLeader;


	}
	return currLeader;
}
//4
void removeFromTeam(Node* node, Team* team) {
	if (node->leader != team->leader) {
		printf("node is not in this team");
	}
	else {
		if (isTeamLeader(*node)) {
			team->leader = changeLeader(*team, node->next);
		}
		else {
			team->leader = remove(team->leader, node);
		}
	}
}


