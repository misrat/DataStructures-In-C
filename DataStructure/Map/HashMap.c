#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define null NULL

typedef struct data{
	char* name;
	char* addr;
	int zip;
	long phoneNo; //use as Key
} data;
typedef data* Data;

//constructor	
Data createData(const char* name, char* addr, const int zip, const int phoneZip){
	Data newData = malloc(sizeof(data));
	if (newData == NULL){
		puts("No memory allocated\n");
		return NULL;
	}
	newData->name = strdup(name);
	newData->addr = strdup(addr);
	newData->zip = zip;
	newData->phoneNo = phoneZip;
	return newData;
}
//destroy
void deleteData(Data thisData){
	if (thisData == NULL)
		return;
	else{
		free(thisData->name);
		free(thisData->addr);
	}
	thisData = null;
}
//print data as key - value
void printData(const Data d){
	if (d == NULL)	return;
	printf("Key = %d\n", d->phoneNo);
	printf("Name = %s, \nAddress = %s, \nZip = %d", d->name, d->addr, d->zip);
	printf("\n\n");
}
//create a linked list
typedef struct node{
	Data element; //pointer to a key value pair
	struct node* next;
} node;

typedef node* Node;
//constructor
Node createNode(Data e){
	Node newNode = malloc(sizeof(node));
	if (newNode == null){
		return EXIT_FAILURE;
	}

	newNode->element = e;
	newNode->next = null;

	return newNode;
}

//hash table with a dynamic size bucket array
typedef struct map{
	Node* buckets; //struct node**
	int size;
	int CAPACITY;
} *Map;

//create Map
Map createMap(int s){
	Map map = malloc(sizeof(*map));
	map->size = 0;
	map->CAPACITY = s;
	//dynamically create the bucket array- array of Node( array of pointers to node)
	map->buckets = malloc(sizeof(Node)* (map->CAPACITY));

	for (int i = 0; i < map->CAPACITY; ++i){
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

int put(Map thisMap, int key, Data value){
	int M = thisMap->CAPACITY;
	int index = hash(key, M);

	Node newNode = createNode(value);

	int added = 0; //flag to check if new element added or updated
	int updated = 0;
	//insert into the bucket
	if (thisMap->buckets[index] == NULL){ //empty bucket
		thisMap->buckets[index] = newNode;
		added = 1;
		++(thisMap->size);
	}
	else{
		//first search for an existing node
		Node current = thisMap->buckets[index];
		
		while (current != NULL && !updated){
			if (current->element->phoneNo == key){
				current->element = value; // need to free memory for prev value
				updated = 1;
			}
			current = current->next;
		}
	}
	//add a new node to the head
	if (!added && !updated){
		newNode->next = thisMap->buckets[index];
		thisMap->buckets[index] = newNode;
		++(thisMap->size);
	}
	return 1;
	
}

Data get(Map map, const int key){
	if (map->size == 0){
		puts("Empty List");
		return null;
	}
	int M = map->CAPACITY;
	Node current = map->buckets[hash(key, M)];
	while (current != NULL){
		if (current->element->phoneNo == key){
			return current->element;
		}
		else{
			current = current->next;
		}
	}
	return NULL;
}

//display map
void printList(Node list);
void displayMap(Map map){
	int nBuckets = map->CAPACITY;
	if (map->size == 0){
		puts("Empty Map");
		return;
	}
	for (int i = 0; i < nBuckets; ++i){
		Node bucket = map->buckets[i];
		if (bucket){
			printList(bucket);
		}
	}
}

void printList(Node list){
	while (list){
		printData(list->element);
		list = list->next;
	}
}

/*test code*/
int main(){
	Map phoneBook = createMap(3);

	//create a phonebookentry
	
	Data entry2 = createData("hjm", "def street", 37345, 209567);
	put(phoneBook, 209567, entry2);
	Data entry3 = createData("dfcv", "am street", 45245, 174567);
	put(phoneBook, 674567, entry3);
	Data entry4 = createData("hmt", "timex street", 19710, 751021);
	put(phoneBook, 751021, entry4);
	//update
	displayMap(phoneBook);
	Data entry5 = createData("hmmt", "timmex street", 19710, 751021);
	put(phoneBook, 751021, entry5);
	
	Data entry1 = createData("tm", "xyz street", 37219, 567567);
	put(phoneBook, 567567, entry1);
	displayMap(phoneBook);
}