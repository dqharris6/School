#ifndef UNSORTED_PRIORITY_QUEUE_H
#define UNSORTED_PRIORITY_QUEUE_H

#include <exception>

using namespace std;

/**
 * Note: in order to try to make things easier, the queue below will only have a single type of value
 * in it instead of a (key, value) pair.  You could still store a (key, value) pair, but you would
 * make a priority queue that stored an object with both the key/value in it and a comparison operator
 * that only compared the keys.
 */

template <class Type>
class UnsortedPriorityQueue
{
protected:
	struct node{
		Type element;
		node* next;
		node* back;
		node(const Type&_e = Type(), node*_n = nullptr, node*_b = nullptr) : element(_e), next(_n), back(_b){}
		~node(){delete next;}
	};

private:
	size_t length;
	node* head;
	node* tail;

public:
   UnsortedPriorityQueue(void){
		head = nullptr;			// in sorted, everything is the same except
    	tail = nullptr;			// insertitem, removemin, minvalue
    	length = 0;
    }

   ~UnsortedPriorityQueue(void){
   		delete head;
    	delete tail;
   }

   bool isEmpty(void){
		return length == 0;
	}

   int size(void){
   		return length;
   }

   void insertItem ( Type data ){
   		node* newnode = new node(data,head,nullptr);
   		if(head != nullptr){
   			head->back = newnode;
   		}
   		head = newnode;
   		++length;
   }

   Type removeMin ( void ) throw(exception){
   		if(isEmpty()){
   			throw exception();
   		}
   		node* after = head->next;
   		node* min = head;
   		for(;after != nullptr; after = after->next){
   			if(after->element < min->element)
   				min = after;
   		}
   		if(min->back!=nullptr)
   			min->back->next=min->next;
   		if(min->next!=nullptr)
   			min->next->back=min->back;
   		if(min==head)
   			head = min->next;
   		--length;
   		return min->element;
   }

   Type minValue ( void ) throw(exception){
   		if(isEmpty()){
   			throw exception();
   		}
   		node* after = head->next;
   		node* min = head;
   		for(;after != nullptr; after = after->next){
   			if(after->element < min->element)
   				min = after;
   		}
   		return min->element;
   }
};

#endif