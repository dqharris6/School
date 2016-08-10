#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void 	Init (int M, int b){
	head_point = malloc(M);			//obtain M bytes of memory	
	free_point = (char*)head_point;	
	mp = M;			
	block_size = b;						
} 

void 	Destroy (){
	free(head_point);
	head_point = NULL;
} 	
	 
int 	Insert (int key,char * value_ptr, int value_len){
	//error: check space
	if(node_count >= mp / block_size){
		printf("Error: No space for node with key: %d\n", key);
		//print error
		return -1;
	}
	
	//error: check block_size of value given
	if(value_len > block_size - (sizeof(key)+sizeof(value_len)+sizeof(free_point))){
		printf("Error: Size given is too large\n");
		//print error
		return -1;
	}
	
	//new node at free_point
	struct node	*new = (struct node*)free_point;
	new->k = key;
	new->next = (struct node*)(free_point + block_size);
	new->value_len = value_len;
	memcpy((free_point + sizeof(struct node)), value_ptr, value_len);		//copy value
	free_point = free_point + block_size;
	
	//increase node count
	node_count++;
	return key;
	
}

int 	Delete (int key){
	//head pointer = current
	struct node* current = head_point;
	struct node* prev = NULL;
	//keep track of erase
	int erase = 0;
	
	for(int i = 1; i <= node_count; i++){
		if(current->k == key && erase != 1){
			if(prev != NULL){
				prev->next = current->next;
			}
			else{
				head_point = current->next;
			}
			//decrease node count
			node_count--;
			printf("\nNode with key: %d deleted\n", key);
			erase = 1;
		}	
		prev = current;
		current = current->next;
	}
	
	if(erase == 1){
		return key;
	}
	else{
		printf("\nError: No node with key: %d\n", key);
		return -1;
	}
}

char* 	Lookup (int key){
	//head pointer = current
	struct node* current = head_point;
	
	for(int i = 1; i <= node_count; i++){
		if(current->k == key){
			//find location of node
			char* loc = (char*) current + sizeof(struct node*);
			return loc;
		}
		current = current->next;
	}
	return NULL;
}

void 	PrintList (){
	//head pointer = current
	struct node* current = head_point;
	
	for(int i = 1; i <= node_count; i++){
		printf("Key: %d, Value length is %d\n", current->k, current->value_len);
		current = current->next;
	}
}