#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define null NULL
//create a linked list
typedef struct node{
	int key;
	char* value;
	struct node* next;
} node;

typedef node* Node;
//constructor
Node createNode(int key, char* value, Node next){
	Node newNode = malloc(sizeof(node));
	if (newNode == null){
		return EXIT_FAILURE;
	}
	newNode->key = key;
	newNode->value = strdup(value);
	newNode->next = next;

	return newNode;
}

typedef struct map{
	//const int CAP;
	Node buckets[4];
	int size;
} *Map;

//create Map
Map createMap(){
	Map map = malloc(sizeof(*map));
	map->size = 0;
	//initialize each pointer in bucket array to NULL
	size_t bucketSize = sizeof(map->buckets);
	size_t nodeSize = sizeof(Node);

	int n = sizeof(map->buckets) / sizeof(Node);
	for (int i = 0; i < n; ++i){
		(map->buckets)[i] = NULL;
		map->buckets[i] = NULL;
	}
	return map;
}

//put key value pair into map
int hash(const int key, const int M){
	long hashCode = 0;
	int tkey = key;
	while (tkey != 0){
		hashCode += (tkey % 10) * 26;
		tkey /= 10;
	}
	return (int)(hashCode % M);
}

int put(Map thisMap, const int key, const char* value){

	int M = sizeof(thisMap->buckets) / sizeof(Node);
	int index = hash(key, M);

	Node newNode = createNode(key, value, NULL);

	Node bucket = thisMap->buckets[index];
	//insert into the bucket
	if (thisMap->buckets[index] == NULL){ //empty bucket
		thisMap->buckets[index] = newNode;
		return 1;
	}
	else{
		//first search for an existing node
		Node current = thisMap->buckets[index];
		while (current != NULL){
			if (current->key == key){
				current->value = strdup(value); // need to free memory for prev value
				return 1;
			}
			current = current->next;
		}
	}
	//add a new node to the head
	newNode->next = thisMap->buckets[index];
	thisMap->buckets[index] = newNode;
}

char* get(Map map, const int key){
	if (map->size == 0){
		puts("Empty List");
		return null;
	}
	int M = sizeof(map->buckets) / sizeof(Node);
	Node current = map->buckets[hash(key, M)];
	while (current != NULL){
		if (current->key == key){
			return current->value;
		}
		else{
			current = current->next;
		}
	}
	return NULL;
}

/*test code*/
int main(){
	Map phoneBook = createMap();
	put(phoneBook, 6767069, "tm");
	put(phoneBook, 4977069, "tc");
	put(phoneBook, 8847069, "pc");
	put(phoneBook, 8847066, "yc");
	put(phoneBook, 8847061, "xc");
	put(phoneBook, 6678069, "gc");
}