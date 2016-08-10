#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H

#include <exception>

using namespace std;

/**
 * Note: in order to try to make things easier, the queue below will only have a single type of value
 * in it instead of a (key, value) pair.  You could still store a (key, value) pair, but you would
 * make a priority queue that stored an object with both the key/value in it and a comparison operator
 * that only compared the keys.
 */

template <class Type>
class SortedPriorityQueue
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
   SortedPriorityQueue(void){
		head = nullptr;			// in sorted, everything is the same except
    	tail = nullptr;			// insertitem, removemin, minvalue
    	length = 0;
    }

   ~SortedPriorityQueue(void){
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
   		node* current = new node(data,nullptr,nullptr);
   		node* after = head;
   		if(isEmpty())
   			head = current;
   		else{
   			int state = 0;
   			while(after->element < current->element){
   				if(state == 0){
   					state = 1;
   				}
   				if(after->next!=nullptr){
   					after = after->next;
   				}
   				else{
   					state = 2;
   					break;
   				}
   			}
   			
   			if(state == 0){
   				head->back = current;
   				current->next = head;
   				head = current;
   			}
   			else if(state == 1){
   				current->back = after->back;
   				current->next = after;
   				after->back->next = current;
   				after->back = current;
   			}
   			else{
   				after->next = current;
   				current->back = after;
   			}
   		}
   		++length;
   }

   Type removeMin ( void ) throw(exception){
   		if(isEmpty()){
   			throw exception();
   		}
   		--length;
   		Type x=head->element;
   		head = head->next;
   		if(head!=nullptr)
   			head->back = nullptr;
   		if(length == 0)
   			tail = nullptr;
   		return x;
   }

   Type minValue ( void ) throw(exception){
   		if(isEmpty()){
   			throw exception();
   		}
   		return head->element;
   }
};

#endif

