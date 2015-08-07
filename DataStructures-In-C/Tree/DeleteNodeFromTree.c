#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vld.h"

#define null NULL

typedef struct node{
	
	char* key;
	char* value;
	struct node *left;
	struct node *right;
} node;

typedef node* Node;

//constructor
Node createNode(char *key, char* value){
	node* temp = malloc(sizeof(node));
	if(temp == NULL){
		puts("No memory");
		return NULL;
	}
	temp->key = strdup(key);
	temp->value = strdup(value);
	temp->left = temp->right = null;
	return temp;
}

//destructor
void deleteNode(Node x){
	if(x == NULL);
	else{
		free(x->key);
		free(x->value);
		free(x);
	}
}


//build  a tree

//insert a node into a tree
void insert(Node* rootRef, char* key, char* value){
	//create a new node
	node* newNode = createNode(key,value);
	node* current = *rootRef;
	
	if(current == NULL){// tree is empty
		*rootRef = newNode;
	}
	else{
		int inserted = 0;
		while(!inserted){
			int cmp = strcmp(key, current->key);
			if(cmp < 0){
				if(current->left == NULL){
					current->left = newNode;
					inserted = 1;
				}else{
					current = current->left;
				}
			}else if(cmp > 0){
				if(current->right == NULL){
					current->right = newNode;
					inserted = 1;
				}else{
					current = current->right;
				}
			}else{//key exists in the tree
				deleteNode(newNode);
				char* oldValue = current->value;
				free(oldValue);
				
				current->value  = strdup(value);
				inserted = 1;
				
			}
		}
	}
	
}

//delete the given node
void removeNodeFromTree(Node* rootRef, char* key){
	node* x = *rootRef;
	node* parent = NULL;
	//search for the node
	int cmp;

	while(x != NULL && (cmp = strcmp(key,x->key)) ){
		parent = x;
		if(cmp < 0){
			x = x->left;
		}else{
			x = x->right;
		}		
	}
	if(x == NULL ){
		puts("Node not found");
		return;
	}
	
	while(x != null){
		
		//check if node is a leaf or has only one child
		// if(!x->left== NULL || y->left == NULL)
		if(!x->left || !x->right){
			
			//check if node is a leaf
			if(x->left == NULL && x->right == NULL){
				
				// if parent is null and both children are null
				// then tree is a single root node- remove it and tree becomes empty
				if(parent == NULL){
					*rootRef = NULL; //tree is now empty
					//deleteNode(x);
				}
				//check if node is a left child or right child of parent
				else if(parent->left == x){
					parent->left = NULL;
				}
				else{
					parent->right = NULL;
				}
			}
			else if( x->left && !x->right){ // x->left is not null & x->right is null
				if(parent == NULL){ // removing root
					*rootRef = x->left;
				}
				//check if node is a left child or right child of parent
				else if(parent->left == x){
					parent->left = x->left;
				}else{
					parent->right = x->left;
				}
			}
			else if( !x->left && x->right){ // x->left is null & x->right is not null
				if(parent == NULL){ // removing root
					*rootRef = x->right;
				}
				//check if node is a left child or right child of parent
				else if(parent->left == x){
					parent->left = x->right;
				}else{
					parent->right = x->right;
				}
			}
			//free memory
			deleteNode(x);
			x = NULL;
		}
		else{
			node* temp = x->left;
			node* tempParent = x;
			while(temp->right){
				tempParent = temp;
				temp = temp->right;
			}
			// temp has largest key in the sub-tree
			// copy over temp->key and temp->value to root, remove temp
			// free old key,value
			free(x->key);
			free(x->value);
			x->key = strdup(temp->key);
			x->value = strdup(temp->value);
			
			//start over again - to delete temp
			x = temp;
			parent = tempParent;
		}
	}
}

void printInOrder(Node root){
	if(root == NULL){
		return;
	}else{
		printInOrder(root->left);
		printf("Key = %s, Value = %s\n", root->key, root->value);
		printInOrder(root->right);
	}
}


/*test code */
int main(void) {
	Node treeRoot = NULL;
	insert(&treeRoot, "i", "one"); 
	insert(&treeRoot, "c","one");
	//insert(&treeRoot, "k", "one");
	insert(&treeRoot, "d","one");
	insert(&treeRoot, "a", "one");
	//insert(&treeRoot, "j","two"); //update
	//insert(&treeRoot, "x","one");
	//insert(&treeRoot, "z","one");
	//insert(&treeRoot, "z", "three"); //update
	printInOrder(treeRoot);

	//remove nodes
	//removeNodeFromTree(&treeRoot, "z");
	//removeNodeFromTree(&treeRoot, "a");
    //removeNodeFromTree(&treeRoot, "d");
	//removeNodeFromTree(&treeRoot, "c");
	//removeNodeFromTree(&treeRoot, "j");
	//removeNodeFromTree(&treeRoot, "k");
	//removeNodeFromTree(&treeRoot, "x");
	//removeNodeFromTree(&treeRoot, "z");
	removeNodeFromTree(&treeRoot, "i");
	
	puts("After removal");
	printInOrder(treeRoot);

	return EXIT_SUCCESS;
}