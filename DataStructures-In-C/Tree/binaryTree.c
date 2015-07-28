#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "binaryTree.h"

/* stack operations  */

//constructor
static SNodeRef createNode(){
	SNodeRef temp = malloc(sizeof(struct sNode));
	assert(temp != NULL);

	return temp;
}

//destructor
static void deleteNode(SNodeRef n){
	if (n == NULL){/*do nothing*/ }
	else{
		//free(n->element);	// 1.delete the element
		//if(n->next != NULL) free(n->next); // 2.delete the next pointer

		free(n);			// 3.delete the current pointer
	}
}

//push element e into the stack top, return new stack top
static SNodeRef push(SNodeRef stack, TNodeRef e){
	SNodeRef newNode = createNode();
	newNode->element = e;
	newNode->next = NULL;

	SNodeRef x = stack;//point to stack head
	if (x == NULL){//empty stack
		x = newNode;
	}
	else{
		SNodeRef oldTop = x;
		x = newNode;
		x->next = oldTop;
	}
	return x;
}

//pop
//passing the reference to the top of the stack
static TNodeRef pop(SNodeRef* stackTop){
	SNodeRef x = *stackTop; //dereference
	if (x == NULL)
		return NULL;
	else{
		(*stackTop) = x->next;
		TNodeRef result = x->element;
		deleteNode(x);
		return result;
	}
}

//peek
static TNodeRef peek(SNodeRef n){
	if (n == NULL)
		return NULL;
	else
		return n->element;
}

//isEmpty
static bool isEmpty(SNodeRef top){
	if (top == NULL)
		return true;
	else
		return false;
}

/* Tree Methods */

TNodeRef createTreeNode(const char* strKey, const char* strValue){
	TNodeRef temp = malloc(sizeof(struct tNode));
	assert(temp != NULL);

	temp->key = strdup(strKey);
	temp->value = strdup(strValue);
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void deleteTreeNode(TNodeRef x){
	if (x != NULL){
		free(x);
	}
}

//insert into tree
TNodeRef insert(TNodeRef root, char* strKey, char* strValue){
	TNodeRef newNode = createTreeNode(strKey, strValue);
	TNodeRef x = root;

	if (root == NULL){
		return newNode;
	}
	

	while (true) {
		int cmp = strcmp(strKey, x->key);
		if (cmp < 0){
			if (x->left == NULL) {
				x->left = newNode;
				break;
			}
			else {
				x = x->left;
			}
		}
		else if (cmp > 0) {
			if (x->right == NULL) {
				x->right = newNode;
				break;
			}
			else {
				x = x->right;
			}
		}
		else {//(newNode->key == x->key)
			x->value = strValue;
			break;
		}
	}
	return root;
}



//TNodeRef insertRecursive(TNodeRef x, char* strKey, char* strValue){
//	//create a treenode
//	TNodeRef newTreeNode = createTreeNode(strKey, strValue);
//}

void printNode(const TNodeRef x){
	if (x != NULL){
		printf("[ Key = %s, Value = %s ]\n", x->key, x->value);
	}
}



/* Iterative function for inorder tree traversal */
void inOrderIterative(const TNodeRef x){
	TNodeRef curr = x;

	//Create a stack of TNodeRef pointers
	SNodeRef stack = NULL;

	while (curr != NULL || !isEmpty(stack)){
		if (curr != NULL){
			stack = push(stack, curr);
			curr = curr->left;
		}
		else{
			if (!isEmpty(stack))
				curr = pop(&stack);
			printNode(curr);
			curr = curr->right;
		}
	}
}


void postOrderIterative(const TNodeRef x){
	TNodeRef curr = x;
	TNodeRef prev = NULL;
	SNodeRef stack = NULL;
	

	while (curr != NULL || !isEmpty(stack)){
		//traverse left
		if (curr != NULL){
			stack = push(stack, curr);
			curr = curr->left;
		}
		else{

			//get top of stack
			if (!isEmpty(stack)){
				curr = peek(stack);
			}

			//check for right child
			if (curr->right == NULL || curr->right == prev){
				prev = curr;
				printNode(curr);
				pop(&stack);
				curr = NULL;
			}
			else{
				curr = curr->right;
			}
		
		}


	}


}

void preOrderIterative(const TNodeRef x){
	SNodeRef stack = NULL;
	TNodeRef curr = x;

	while (curr != NULL || !isEmpty(stack)){

		if (curr != NULL){
			printNode(curr);

			if (curr->right != NULL){
				stack = push(stack, curr->right);
			}
			curr = curr->left;
		}
		else{
			if (!isEmpty(stack)){
				curr = pop(&stack);
			}
		}
	}
}
