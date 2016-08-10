// DoublingArrayStack.h
// This class provides a template stack. Internally
// the stack is stored as an array.

#ifndef DoublingArrayStack_H_
#define DoublingArrayStack_H_

#include "RuntimeException.h"

#define CAPACITY 1000 //default capacity of the stack

template <typename T>
class DoublingArrayStack {
  public:
    //exception classes thrown by various functions
    class EmptyStackException : public RuntimeException {
      public:
        EmptyStackException() : RuntimeException("Access to empty stack") {}
    };

    class FullStackException : public RuntimeException {
      public:
        FullStackException() : RuntimeException("Stack overflow") {}
    };

    //constructor given max capacity
    DoublingArrayStack(size_t _cap = CAPACITY);

    //copy constructor
    DoublingArrayStack(const DoublingArrayStack& _st); 
    
    //destructor
    ~DoublingArrayStack() { delete [] s; } 

    //assignment operator
    DoublingArrayStack& operator=(const DoublingArrayStack& _st); 
    
    //is the stack empty?
    bool is_empty() const { return t < 0; } 

    //number of elements in the stack
    size_t size() const { return t+1; } 

    //return the top of the stack
    T& top() throw(EmptyStackException);

    //push object onto the stack
    void push(const T& _elem) throw(FullStackException);

    //pop the stack
    T pop() throw(EmptyStackException);

  private:
    //member data
    size_t       capacity; //actual length of stack array
    T*   s; //the stack array
    int    t; //index of the top of the stack
};

//constructor given max capacity
template <typename T>
DoublingArrayStack<T>::DoublingArrayStack(size_t _cap) {
  capacity  = _cap;
  s         = new T[capacity];
  t         = -1;
}

//copy constructor
template <typename T>
DoublingArrayStack<T>::DoublingArrayStack(const DoublingArrayStack& _st) {
  //initialize internal variables
  capacity  = _st.capacity;
  t         = _st.t;
  s         = new T[capacity];

  //copy contents
  for (int i = 0; i <= t; ++i) {
    s[i] = _st.s[i];
  }
}

//assignment operator
template <typename T>
DoublingArrayStack<T>&
DoublingArrayStack<T>::operator=(const DoublingArrayStack& _st) {
  //avoid self copy (x = x)
  if(this != &_st) {
    
    //delete old contents
    delete [] s;
    
    //initialize internal variables
    capacity  = _st.capacity;
    t         = _st.t;
    s         = new T[capacity];
    
    //copy contents
    for(int i = 0; i <= t; ++i) {
      s[i] = _st.s[i];
    }
  }
  return *this;
}

//return the top of the stack
template <typename T>
T&
DoublingArrayStack<T>::top() throw(EmptyStackException) {
  if (is_empty())
    throw EmptyStackException();
  return s[t];
}

//push object onto the stack
template <typename T>
void
DoublingArrayStack<T>::push(const T& _elem) throw(FullStackException) {
  if (size() == capacity)
  {
  	T* n=new T[capacity*2];
  	
  	for(int i=0; i<capacity; ++i)
  	{
  		n[i] = s[i];
  	}
  	
  	capacity*=2;
  	s=n;
  }
  
  s[++t] = _elem;
}

//pop the stack
template <typename T>
T
DoublingArrayStack<T>::pop() throw(EmptyStackException) {
  if (is_empty())
    throw EmptyStackException();
  return s[t--];
}

#endif