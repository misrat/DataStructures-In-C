<<<<<<< HEAD

=======
>>>>>>> origin/master
#include <stdio.h>
#include <stdlib.h>
#include "Tree/binaryTree.h"

int main(void) {
	TNodeRef tree = NULL;
	tree = insert(tree, "i", "one");
	tree = insert(tree, "j", "one");
<<<<<<< HEAD
	tree = insert(tree, "a","one");
	tree = insert(tree, "b","one");
	tree = insert(tree, "j","one");
	tree = insert(tree, "x","one");
	tree = insert(tree,"z","one");
	inOrderIterative(tree);



	return EXIT_SUCCESS;
}
=======
	tree = insert(tree, "a", "one");
	tree = insert(tree, "b", "one");
	tree = insert(tree, "j", "one");
	tree = insert(tree, "x", "one");
	tree = insert(tree, "z", "one");
	
	inOrderIterative(tree);

	return EXIT_SUCCESS;
}
>>>>>>> origin/master
