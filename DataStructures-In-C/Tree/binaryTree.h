#ifndef TREES_BINARYTREES_H_
#define TREES_BINARYTREES_H_

#include <stdbool.h>

//typedef char* Key;
//typedef char* Value;

struct tNode{
	char* 			key;
	char* 			value;
	struct tNode* 	left;
	struct tNode* 	right;
};
typedef struct tNode *TNodeRef;

/* tree methods */
void inOrderIterative(const TNodeRef x);
TNodeRef insert(TNodeRef root, char* strKey, char* strValue);
void printNode(const TNodeRef x);
void postOrderIterative(const TNodeRef x);





/* stack of tree nodes*/
struct sNode{
	TNodeRef 		element;
	struct sNode 	*next;
};
typedef struct sNode *SNodeRef;
/* Stack methods */
/* All stack methods are  static - not exposing them out */






#endif /* TREES_BINARYTREES_H_ */