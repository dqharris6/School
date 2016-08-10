#ifndef DEQUE_H
#define DEQUE_H

#include <exception>

using namespace std;

template <class Type>
class Deque
{
protected: 
   struct node{
      Type element;
      node* next;
      node* back;
      node(const Type&_e = Type(), node*_n = nullptr, node*_b = nullptr) : element(_e), next(_n), back(_b){}
      };
      
	typedef node* node_ptr;
private:
	size_t length;
	node_ptr head;
	node_ptr tail;

public:
// constructor
   Deque(void){					
     head = nullptr;
     tail = nullptr;
     length = 0;
   }

// destructor
   ~Deque(void){		
     delete head;
     delete tail;
   }

// check to see if the queue is empty
   bool isEmpty(void){		
     return length == 0;
   }

// return the size of the queue
   int size(void){
     return length;
   }

// return the first element in the queue
   Type first(void) throw(exception){
     return head->element;
   }

// return the last element in the queue
   Type last(void) throw(exception){
     return tail->element;
   }

// increment the length by 1, add an element at the beginning of the  queue
   void insertFirst(Type o){
     if(++length == 1)
     {
       node* a = new node(o, nullptr, nullptr);
       head = a;
       tail = a;
     }
     else
     {
       node* a = new node(o, head, nullptr);
       head = a;
     }
   }

// increment the length by 1, add an element at the beginning of the queue
   void insertLast(Type o){
     if(++length == 1)
     {
       node* a = new node(o, nullptr, nullptr);
       head = a;
       tail = a;
     }
     else
     {
       node* a = new node(o, nullptr, tail);
       tail = a;
     }
   }

// remove the first element in the queue
   Type removeFirst(void) throw(exception){
     if(isEmpty())
       throw exception();
     Type x = head->element;
     head = head->next;
     if(head != nullptr)
       head->back = nullptr;
     --length;
     if(length == 0)
       tail = nullptr;
     return x;  
   }

// remove the last element in the queue
   Type removeLast(void) throw(exception){
   	 if(isEmpty())
       throw exception();
     Type x = tail->element;
     tail = tail->back;
     if(tail != nullptr)
       tail->next = nullptr;
     --length;
     if(length == 0)
       head = nullptr;
     return x;  
   }
};

#endif
