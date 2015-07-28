/*
* LinkedLIstProblems.c
*
*  Created on: Jul 26, 2015
*      Author: tanmay
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vld.h"

typedef struct node{
	char *data;
	struct node* next;
}*Node;

typedef struct {
	Node head;
	int N;
}*LinkedList;

//create list
LinkedList createList(){
	LinkedList temp = malloc(sizeof(*temp));
	temp->head = NULL;
	temp->N = 0;
	return temp;
}

void deleteList(LinkedList list){

	Node x = list->head;
	Node temp;
	while (x != NULL){
		temp = x;
		x = x->next;
		free(temp->data); //delete data before deleting node - this is required if data is dynamically created
		free(temp);		//delete Node
	}
	if (list != NULL)	free(list);
}


//node constructor

Node createNode(const char* data){
	Node tempNode = malloc(sizeof(*tempNode));

	if (tempNode == NULL){ puts("No memory"); exit(0); }

	tempNode->data = _strdup(data); //malloc implicatly called
	tempNode->next = NULL;

	return tempNode;
}



//sorted insert
void push(Node* nodeRef, Node node){
	Node current = *nodeRef;
	node->next = current;
	*nodeRef = node;
}

//build a list
void addLast(LinkedList list, const char* data){
	//create a node
	Node temp = createNode(data);
	//check for head
	if (list->head == NULL){
		push(&(list->head), temp);
	}
	else{
		//traverse to tail
		Node tail = list->head;
		while (tail->next != NULL){
			tail = tail->next;
		} //now tail points to last element
		push(&(tail->next), temp);
	}
	++(list->N);
}

void printNode(const Node n){
	printf("%s \n", n->data);
}

void printList(LinkedList list){
	if (list->head == NULL || list->N == 0)
		puts("Empty List");
	for (Node current = list->head; current != NULL; current = current->next){
		printNode(current);
	}
}


int main(){
	LinkedList list1 = createList();
	
	//Read input from user
	

	/*for (int i = 0; i < 4; ++i){
		char input[100];
		printf("Enter a string ");
		scanf("%s", input);
		addLast(list1,input );a
	}*/



	//
	//addLast(list1, 2);
	//addLast(list1, 3);
	//addLast(list1, 4);
	//addLast(list1, 7);
	//addLast(list1, 0);
	//addLast(list1, 6);

	//printList(list1);
	//deleteList(list1);



	char name[50];
	printf("%s\n", "enter ");
	scanf("%s", name);

	puts("Print Name");
	puts(name);
	puts("COPYINNG\n");
	
	char* name2 = malloc(sizeof(char)*strlen(name));
	strcpy(name2, name);
	//name2[5-2] = '\0';
	puts("Print Name");
	puts(name2);


}
