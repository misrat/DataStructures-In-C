#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vld.h"

/* Accidentally realized one good use of PostOrderTraversal - to delete a BST */

typedef struct treeNode{
	char* 				key;
	char* 				value;
	struct treeNode* 	left;
	struct treeNode* 	right;
} treeNode;

// Node is a pointer to treeNode
typedef treeNode* Node;


//constructor
Node createNode(char* key, char* value){
	//first allocate memory for the tree node pointer
	treeNode* tempNode = malloc(sizeof(treeNode));
	// check if memory has been allocated
	if(tempNode == NULL){
		puts("No memory");
		return NULL;
	}
	// assign members of the structure
	tempNode->left = NULL;
	tempNode->right = NULL;
	// char* used to point to strings, 
	// dynamically allocate memory for the string, and copy from 
	// the char* passed to the method. 
	// strdup() does that
	tempNode->key = strdup(key);
	tempNode->value = strdup(value);
	return tempNode;
}

/* free the dynamically  allocated memory for all the members of the struct and 
the struct pointer. 
free the members first(only dynamically allocated) and then the containing struct pointer
TIP - for every malloc() or calloc() there should be a free() */

void deleteNode(Node x){
	if (x != NULL){
		free(x->key); // free memory created by the strdup()
		free(x->value);// same as above
		free(x); // free memory allocated for struct pointer
	}
}

// struct for a stack of nodes
// stack is a linked structure, each Node of the Stack contains 
// reference to a tree node and the next pointer- which points to a stack node
typedef struct stackNode{
	Node node;
	struct stackNode* next;
}stackNode;

typedef stackNode* Stack;

//Stack constructor
stackNode* createStack(){
	stackNode* tempStack = malloc(sizeof(stackNode));
	if(tempStack == NULL){
		puts("No memory");
		return NULL;
	}
	return tempStack;
}		

//	push element e into the stack top, return new stack top
// pass the pointer to pointer to stack top, no values returned 
void push(stackNode** stack, Node e){
	stackNode* newNode = createStack(); // need to free memory
	newNode->node = e;
	newNode->next = NULL;

	stackNode* currPtr = *stack;//point to stack head
	if (currPtr == NULL){//empty stack
		*stack = newNode; // directly modify by de-referencing pointer to pointer to stack top
	}
	else{
		stackNode* oldTop = *stack; // keep track of old stack top
		*stack = newNode; //modify stack to point to newNode
		newNode->next = oldTop;
	}
}

/*Peek into the stack top*/
Node top(Stack stack){
	if(stack == NULL){
		return NULL;
	}
	else{
		return stack->node;
	}
}

/* Pop a node from the stack - either return the stackNode or just the element
   In case only element is returned, the stack node pointer has to be freed */
Node pop(Stack* stack){
	if(*stack == NULL)
		return NULL;
	else{
		stackNode* oldTop = *stack;
		treeNode* result = oldTop->node;
		*stack = oldTop->next; //pointer-to-pointer to point to next stack node
		free(oldTop); // frees memory allocated in stack constructor
		return result;
	}
}

//return true(1) if empty
int isEmpty(Stack stack){
	return (stack == NULL) ? 1 : 0;
}


//insert into tree
void insert(Node *root, char* strKey, char* strValue){
	treeNode* newNode = createNode(strKey, strValue);
	treeNode* x = *root; //x is current pointer

	if (x == NULL){
		*root = newNode;
		return;
	}

	int inserted = 0; //use a flag condition instead of breaks or continues
	while (!inserted) {
		int cmp = strcmp(strKey, x->key); //to go left or right
		if (cmp < 0){
			if (x->left == NULL) {
				x->left = newNode;
				inserted = 1; // node inserted in tree -exit while loop
			}
			else {
				x = x->left;
			}
		}
		else if (cmp > 0) {
			if (x->right == NULL) {
				x->right = newNode;
				inserted = 1;
			}
			else {
				x = x->right;
			}
		}
		else {// cmp = 0, node exists, update value.
			//x->value = strValue;	// DO NOT - simply update 
			//before updating the value, free memory for previously allocated value
			char* deleteString = x->value;
			x->value = strdup(strValue);
			free(deleteString);
			deleteNode(newNode);	// unused node deleted - else memory leak
			inserted = 1;
		}
	}
}

void printPostIterative(Node x){
	Stack stackHead = NULL;//stack functions
	Node current = x;
	Node isVisited = NULL; // a flag to check if a node has been previously visited or not
	while(current != NULL || !isEmpty(stackHead) ){
		if(current != NULL){
			push(&stackHead, current );
			current = current->left;
		}
		else{
			current = top(stackHead);
			if(current->right == NULL || current->right == isVisited){
				printf("Key = %s, Value = %s\n", current->key, current->value);
				isVisited = current;
				Node temp = pop(&stackHead); 
				deleteNode(temp);
				current = NULL;
			}
			else{
				current = current->right;
			}
		}
	}
}

/* test code */


int main(void) {
	Node treeRoot = NULL;
	insert(&treeRoot, "i", "one"); 
	insert(&treeRoot, "j", "one");
	insert(&treeRoot, "a","one");
	insert(&treeRoot, "b","one");
	insert(&treeRoot, "j","two"); //update
	insert(&treeRoot, "x","one");
	insert(&treeRoot,"z","one");
	insert(&treeRoot, "z", "three"); //update
	printPostIterative(treeRoot);

	

	return EXIT_SUCCESS;
}
