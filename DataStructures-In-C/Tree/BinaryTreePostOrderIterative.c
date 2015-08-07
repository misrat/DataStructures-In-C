#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
	treeNode* tempNode = malloc(sizeof(treeNode));
	if(tempNode == NULL){
		puts("No memory");
		return NULL;
	}
	tempNode->left = NULL;
	tempNode->right = NULL;
	tempNode->key = strdup(key);
	tempNode->value = strdup(value);
	return tempNode;
}

void deleteNode(Node x){
	if (x != NULL){
		free(x->key);
		free(x->value);
		free(x);
	}
}

// struct for a stack of nodes
typedef struct stackNode{
	Node node;
	struct stackNode* next;
}stackNode;

typedef stackNode* Stack;

//Stack constructor - not required
stackNode* createStack(){
	stackNode* tempStack = malloc(sizeof(stackNode));
	if(tempStack == NULL){
		puts("No memory");
		return NULL;
	}
	return tempStack;
}

//	push element e into the stack top, return new stack top
void push(stackNode** stack, Node e){
	stackNode* newNode = createStack();
	newNode->node = e;
	newNode->next = NULL;

	stackNode* currPtr = *stack;//point to stack head
	if (currPtr == NULL){//empty stack
		currPtr = newNode;
	}
	else{
		stackNode* oldTop = *stack;
		*stack = newNode; //modify stack to point to newNode
		newNode->next = oldTop;
	}
}

Node top(Stack stack){
	if(stack == NULL){
		return NULL;
	}
	else{
		return stack->node;
	}
}

Node pop(Stack* stack){
	if(*stack == NULL)
		return NULL;
	else{
		stackNode* oldTop = *stack;
		treeNode* result = (*stack)->node;
		*stack = oldTop->next;
		free(oldTop);
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

	int inserted = 0;
	while (!inserted) {
		int cmp = strcmp(strKey, x->key); //to go left or right
		if (cmp < 0){
			if (x->left == NULL) {
				x->left = newNode;
				inserted = 1;
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
		else {//(newNode->key == x->key), cmp = 0
			x->value = strValue;
			inserted = 1;
		}
	}
}


void printPostIterative(Node x){
	Stack stackHead = NULL;//stack functions
	Node current = x;
	Node isVisited = NULL;
	while(current != NULL || !isEmpty(stackHead) ){
		if(current != NULL){
			push(&stackHead, current );
			current = current->left;
		}
		else{
			current = top(stackHead);
			if(current->right == NULL || current->right == isVisited){
				printf("%s \n", current->key);
				isVisited = current;
				pop(&stackHead);//delete the node here
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
	insert(&treeRoot, "j","one");
	insert(&treeRoot, "x","one");
	insert(&treeRoot,"z","one");
	printPostIterative(treeRoot);



	return EXIT_SUCCESS;
}
