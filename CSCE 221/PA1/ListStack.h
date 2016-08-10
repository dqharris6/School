//ListStack.h -- a list-based implementation of the stack
//Refer to array_stack.h (Stack implemenation) 
//for array based implemenation.

#ifndef LISTSTACK_H_
#define LISTSTACK_H_

#include "RuntimeException.h"

using namespace std;

template <typename T>
class ListStack {
  public:
    
    class EmptyStackException : public RuntimeException {
      public:
        EmptyStackException() : RuntimeException("Access to empty stack") {}
    };

    //constructor - simply set top element to NULL and size to 0
    ListStack();

    //copy constructor
    ListStack(const ListStack& _st); 

    //destructor
    ~ListStack();

    //assignment operator
    ListStack& operator=(const ListStack& _st); 

    //is the stack empty?
    bool is_empty() const {return length == 0;} 

    //number of elements in the stack
    size_t size() const {return length;}; 

    //return the top of the stack
    T& top() throw(EmptyStackException);

    //push object onto the stack
    void push(const T& _elem); 

    //pop the stack
    T pop() throw(EmptyStackException); 

  protected:

    //node in the node_list
    struct node {						
      T  element; //element
      node*   next;    //next node

      //constructor
      node(const T& _e = T(), node* _n = NULL) : element(_e), next(_n) {}
    };
    
    typedef node* node_ptr; //pointer to a node

  private:
    //member data
    size_t  length; //current length of stack 
    node_ptr head; //top of the stack
};

//constructor - simply set top element to NULL and size to 0
template <typename T>
ListStack<T>::ListStack() : head(NULL), length(0) {}

//copy constructor
template <typename T>
ListStack<T>::ListStack(const ListStack& _st) {

	length = _st.length;
	head = _st.head;
}

//destructor
template <typename T>
ListStack<T>::~ListStack() { 

	node *current;
	
	while(head != NULL)
	{
		current = head;
		head = head -> next;
		delete current;
	}
	
	delete head;
}

//assignment operator
template <typename T>
ListStack<T>&
ListStack<T>::operator=(const ListStack& _st) {

	if(this != &_st)
	{
		length = _st.length;
		head = _st.head;
		
		return *this;
	}
}

//return the top of the stack
template <typename T>
T&
ListStack<T>::top() throw(EmptyStackException) {
  if (is_empty())
    throw EmptyStackException();

	return head->element;
}

//push object onto the stack
template <typename T>
void
ListStack<T>::push(const T& _elem) {

	if(head == NULL)
	{
		head = new node(_elem,NULL);
		length++;
	}
	
	else
	{
		node *temp = new node(_elem,head);
		head = temp;
		length++;
	}
}

//pop the stack
template <typename T>
T
ListStack<T>::pop() throw(EmptyStackException) {
	
	node *firsthead = head;
	node *newhead = head -> next;
	head = newhead;
	--length;
	return firsthead -> element;
	delete firsthead;
}

#endif