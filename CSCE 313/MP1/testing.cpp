#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "linked_list2.h"

node* memory;
node** heads;
node** tails;
char** pointers;
int block_size;
int mp;
int* size_lists;
int divisions;
int size_of_divisions;
int num_div;
node* test;
int node_count;
int t;

void 	Init (int M, int b, int t){

	memory = (node*)malloc(M);
	pointers = new char*[t];
	heads = new node*[t];
	tails = new node*[t];
	size_lists = new int[t];
	divisions = M/t;
	size_of_divisions = INT_MAX/t;

	for(int i = 0; i < t; ++i)
	{
		pointers[i] = new char;
		pointers[i] = ((char*)memory) + (i*divisions);
		size_lists[i] = 0;
		heads[i] = tails[i] = NULL;
	}

	if(memory == NULL)
	{
		printf("You are wrong.\n");
		exit(1);
	}

	mp = M;			
	block_size = b;		
	num_div = t;
} 

void 	Destroy (){
	free(memory);
} 	
	 
int 	Insert (int key,char * value_ptr, int value_len){
	//error: check space
	
	int this_tier = key/size_of_divisions;
	node	*testpointer = (node*)pointers[this_tier];

	if(node_count >= mp / block_size){
		printf("Error: No space for node with key: %d\n", key);
		//print error
		return -1;
	}
	
	//error: check block_size of value given
	if(value_len > block_size - (sizeof(key)+sizeof(value_len)+sizeof(pointers[this_tier]))){
		printf("Error: Size given is too large\n");
		//print error
		return -1;
	}
	

	if(heads[this_tier] == NULL || tails[this_tier] == NULL)
	{
		testpointer->k = key;
		testpointer->next = NULL;
		testpointer->value_len = value_len;
		memcpy((pointers[this_tier] + sizeof(node)), value_ptr, value_len);		//copy value
		pointers[this_tier] = pointers[this_tier] + block_size;
		heads[this_tier] = tails[this_tier] = testpointer;
		return 0;
	}

	//testpointer node at pointers[this_tier]
	tails[this_tier]->next = testpointer;
	testpointer->k = key;
	testpointer->next = NULL;
	testpointer->value_len = value_len;
	memcpy((pointers[this_tier] + sizeof(node)), value_ptr, value_len);		//copy value
	pointers[this_tier] = pointers[this_tier] + block_size;
	tails[this_tier] = testpointer;
	
	//increase node count
	node_count++;
	return key;
	
}

int 	Delete (int key){
	//head pointer = current
	int this_tier = key/size_of_divisions;
	if(heads[this_tier] == NULL) return 0;
	if(heads[this_tier]->k == key) 
	{
			heads[this_tier] = heads[this_tier]->next;
			return 0;
	}
	
	node* prev = heads[this_tier];
	node* current = heads[this_tier]->next;

	//keep track of erase
	//int erase = 0;
	
	while(current != NULL)	
	{
		if(current->k == key){
			if(current->next != NULL){
				prev->next = current->next;
				return 0;
			}

			else if(prev->next != NULL)
			{
				prev->next = NULL;
				return 0;
			}

			//decrease node count
			node_count--;
			printf("\nNode with key: %d deleted\n", key);
		}	
		prev = current;
		current = current->next;
	}

	return 0;

}

char* 	Lookup (int key){
	//head pointer = current
	node* current = heads[0];
	
	for(int i = 1; i <= node_count; i++){
		if(current->k == key){
			//find location of node
			char* loc = (char*) current + sizeof(node*);
			return loc;
		}
		current = current->next;
	}
	return NULL;
}

void 	PrintList (){
	//head pointer = current
	node* current;

	for(int i = 0; i < num_div; i++){

		current = heads[i];

		if(current != NULL)
		{
			printf("\nTIER %d\n", i+1);
			std::cout << std::endl;
		}

		while(current != NULL)
		{
			printf("Key: %d, Value length is %d\n", current->k, current->value_len);
			current = current->next;
		}

		
		
	}
}