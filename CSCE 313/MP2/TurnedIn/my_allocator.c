/* 
    File: my_allocator.c

    Author: Dalton Harris and Ashton Binkley
            Department of Computer Science
            Texas A&M University
    Date  : 02/29/2016

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

Header** list_point;
double l_size, base;
uintptr_t mem_begin;

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR MODULE MY_ALLOCATOR */

void head_rem(int i){

    if (list_point[i]!=list_point[i+1]){
        list_point[i]=list_point[i]->next;
        }

    else{
        list_point[i]=NULL;
        list_point[i+1]=NULL;
    }
}

int head_check(Header* ptr){

    if (ptr->symbol=='~'){
        return 1;
    }

    if (ptr->symbol=='!'){  
        return 0;
    }
    
    return -1;
}

int power(int n, int p){
    if (p==0){
        return 1;
    }

    else{
        n=n*power(n,p-1);
    }

    return n;
}

Header* split(int i) {

    unsigned int break_size=base*power(2,(l_size-1-(i/2)));
    
    Header* temp;
    i-=2;

    if (i<=l_size*2&&i>=0){

        if (list_point[i]==NULL){ 
            
            if (split(i)==NULL){
                return NULL;
            }
        }

        temp=list_point[i];

        head_rem(i);
        i+=2;
        temp->size=break_size;
        temp[break_size/sizeof(Header)]=temp[0];
        temp->next=&temp[break_size/sizeof(Header)];
        list_point[i]=temp;
        temp=temp->next;
        temp->next=NULL;
        list_point[i+1]=temp;
        head_check(temp);
        return temp;
    }

    else{
        return NULL;
    }
}

void block_join(Header* ptr){

    uintptr_t temp=(uintptr_t)ptr;
    temp=temp-mem_begin;

    int i=0;
    i=log2(ptr->size);
    temp ^= 1 << i;

    temp=temp+mem_begin;
    Header* buddy=(Header*)temp; 

    if (head_check(buddy)==1&&buddy->size==ptr->size){
        if((int)(buddy-ptr)<0)
            ptr=buddy;

        head_rem((l_size-1-(log2(ptr->size)-log2(base)))*2);
        ptr->size=(ptr->size*2);
        block_join(ptr);
    }
}

unsigned int init_allocator(unsigned int base_size, unsigned int _length){

    unsigned int remainder=_length%base_size;
    unsigned int total=_length-remainder; 

    if (remainder!=0){
        total=total+base_size; 
    }

    _length=total;
    l_size=log2(total)-log2(base_size);
    l_size=round(l_size+.5);
    base=base_size;
    Header** free_list=(Header**)malloc(2*l_size*sizeof(Header*)); 

    free_list[0]=(Header*)malloc(total); 
    mem_begin=(uintptr_t)free_list[0];

    for (int i=1; i<l_size*2; ++i){
        free_list[i]=NULL; 
    }

    Header* ptr=free_list[0]; 
    Header head1;
    head1.symbol='~';
    head1.next=NULL;
   
    for (int i=0; i<l_size*2; i+=2){

        head1.size=(base_size*power(2,(l_size-((i+2)/2))));
     
        if (total>=(base_size*power(2,(l_size-(((i+2)/2)))))){
            free_list[i]=ptr; 
        }

        while (total>=(base_size*power(2,(l_size-(((i+2)/2)))))){

            ptr[0]=head1;
            ptr->next=&ptr[(base_size*power(2,(l_size-(((i+2)/2)))))/sizeof(Header)];
            ptr=ptr->next;
            total=total-base_size*power(2,(l_size-(((i+2)/2))));
       
            if (ptr->size==free_list[i]->size){
                free_list[i+1]=ptr;
            }

            else{
                free_list[i+1]=free_list[i];
            }
        }
    }

    list_point=free_list;

    return  _length; 
}

extern Addr my_malloc(unsigned int _length){

    printf("allocating %d\n",_length);
    int index=0;

    while ((_length+sizeof(Header))/(base*power(2,index))>1){
        ++index;
    }

    if(index>=l_size){
        printf("Error: request exceeds largest block available\n");
        return NULL;
    }

    index=l_size-1-index;
    if (list_point[index*2]==NULL){
        printf("breaking blocks to list_point i=%d\n",index*2);

        if (split(index*2)==NULL){
            printf("Error: No mem left returning NULL. Block break failed\n");
            return (void*)NULL;
        }
    }

    if (head_check(list_point[index*2])==0){
        printf("Error: Accessed used memory\n");
    }

    if (head_check(list_point[index*2])==-1){
        printf("Error: Invalid header symbol\n");
    }

    list_point[index*2]->symbol='!'; 
    Addr my_addr=&list_point[index*2][1];

    head_rem(index*2);
    return my_addr;
}

extern int my_free(Addr _a){

    Header* my_addr=(Header*)_a;
    int* remover;
    remover=(int*)my_addr;
    
    my_addr=&my_addr[-1]; 
    
    
    if (head_check(my_addr)==1){
        printf("Error: Block already free\n");
    }

    if (head_check(my_addr)==-1){
        printf("Error: Not a header\n");
    }

    my_addr->symbol='~';
    block_join(my_addr);
    int i=0;

    while((my_addr->size-sizeof(Header))>(i*sizeof(int))){
        remover[i]&=0;
        ++i;
    }

    i=0;

    while (my_addr->size>(base*power(2,i))){
        ++i;
    }

    i=l_size-1-i;

    if (list_point[i*2]==NULL) {
        list_point[i*2]=my_addr;
        list_point[i*2+1]=my_addr;
    }

    else{
        my_addr->next=list_point[i*2];
        list_point[i*2]=my_addr;
    }

    return 0;
}

int release_allocator(){

    free((void*)list_point);
    free((void*)mem_begin);
    printf("deallocated memory\n");
    return 0;
}