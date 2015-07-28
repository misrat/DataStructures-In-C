#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Not working

typedef struct node{
	char *data;
	struct node* next;
}*Node;

//constructor
Node createNode(const char* data){
	Node tempNode = malloc(sizeof(*tempNode));
	char* element = _strdup(data);
	tempNode->next = NULL;
	tempNode->data = element;
	return tempNode;
}

//methos on linkedlist
//add to list
void addToList(Node* head, const char* data){
	Node newNode = createNode(data);
	if (newNode == NULL){
		exit(0);
	}
	if (*head == NULL){
		*head = newNode;
	}
	else{
		Node tail = *head;
		while (tail->next){
			tail = tail->next;
		}
		tail->next = newNode;
	}
}
/* count the number of nodes*/
int count(const Node head){
	int count = 0;
	for (Node curr = head; curr != NULL; curr = curr->next){
		++count;
	}
	return count;
}

//display the list
void printList(const Node head){
	Node curr = head;
	while (curr){
		printf("%s \n", curr->data);
		curr = curr->next;
	}
}


typedef struct tNode{
	char *data;
	struct tNode* left;
	struct tNode* right;
} *TreeNode;

//Constructor
TreeNode createTreeNode( char* data){
	TreeNode tempNode = malloc(sizeof(*tempNode));
	tempNode->data = data;
	tempNode->left = NULL;
	tempNode->right = NULL;
	return tempNode;
}


/* This function counts the number of nodes in Linked List and then calls
sortedListToBSTRecur() to construct BST */
TreeNode sortedListToBSTRecur(Node *head_ref, int n);
TreeNode sortedListToBST(Node head)
{
	/*Count the number of nodes in Linked List */
	int n = count(head);

	/* Construct BST */
	return sortedListToBSTRecur(&head, n);
}

/* The main function that constructs balanced BST and returns root of it.
head_ref -->  Pointer to pointer to head node of linked list
n  --> No. of nodes in Linked List */
TreeNode sortedListToBSTRecur(Node *head_ref, int n)
{
	/* Base Case */
	if (n <= 0)
		return NULL;

	/* Recursively construct the left subtree */
	TreeNode left = sortedListToBSTRecur(head_ref, (int)(n / 2));

	/* Allocate memory for root, and link the above constructed left
	subtree with root */
	TreeNode root = createTreeNode((*head_ref)->data);
	root->left = left;

	/* Change head pointer of Linked List for parent recursive calls */
	*head_ref = (*head_ref)->next;

	/* Recursively construct the right subtree and link it with root
	The number of nodes in right subtree  is total nodes - nodes in
	left subtree - 1 (for root) which is n-n/2-1*/
	root->right = sortedListToBSTRecur(head_ref, n - n / 2 - 1);

	return root;
}



int main(){
	//test list
	Node list = NULL;
	for (int i = 0; i < 7; ++i){
		char input[100];
		printf("Enter a string ");
		scanf("%s", input);
		addToList(&list, input);
	}
	//printList(list);

	TreeNode root = sortedListToBST(&list);


}