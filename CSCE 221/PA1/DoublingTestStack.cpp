// DoublingTestStack.cpp -- Inherited from TestStack.cpp

#include "DoublingArrayStack.h" 
#include "ListStack.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

const int NUM = 10;

ofstream outfile ( "Doubling.txt" );
clock_t start = clock();
clock_t stop;

using namespace std;

//Test correctness over all stack functions
template <typename ST, typename T>
void 
TestStack_correctness(ST _s1, T& _input, size_t _size){
  
  //test correctness of pushing onto an empty stack
  try{
    for(size_t i = 0; i < _size; ++i){
      _s1.push(_input[i]);
            
      //checking if push and top are implemented correctly
      if(_s1.size() != i+1){
        cerr << "Error::incorrect push" << endl;
        exit(1);
      }
      else if(_s1.top() != _input[i]){
        cerr << "Error::incorrect top/push" << endl;
        exit(1);
      }
      else {
      	stop = clock();
      	double ms = (double)(stop-start)/CLOCKS_PER_SEC;
      	if(_s1.size() % 100 == 0)
      	outfile << _s1.size() << "\t" << ms << "\n";
        cout << "Pushing " << _input[i] << endl;
        cout << "Stack size after push " << _s1.size() << endl;
      }
      
    }
    cout << "PASSED::push, size, top" << endl;
  }
  catch(...){
    cerr << "Error::EmptyStackException, something is amiss!" << endl;
    exit(1);
  }

  //test correctness of assignment, copy, and pop
  ST s2;
  s2 = _s1;
  ST s3(s2);
  
  //double check the order on being popped against ordering in v
  try{
    for(size_t i = _size; i > 0; --i){
       //checking if pop is implemented correctly
       if(_s1.pop() != _input[i-1]){
         cerr << "Error::pop did not preserve order or pop incorrect " << endl;
         exit(1);
       }
       else if(_s1.size() != i-1){
        cerr << "Error::pop incorrect" << endl;
        exit(1);
      } 
      else {
        cout << "Popping " << _input[i-1] << endl;
        cout << "Stack size after popping: " << _s1.size() <<endl;
      } 

      //checking if assignment operator is implemented correctly
      if(s2.pop() != _input[i-1]){
        cerr << "Error::assignment did not preserve order or pop not correct" << endl;
        exit(1);
      }

      //checking if copy constructor implemented correctly
      if(s3.pop() != _input[i-1]){
        cerr << "Error::copy constructor did not preserve order or pop not correct" << endl;
        exit(1);
      }
    }
   cout << "PASSED::pop, assignment, copy constructor" << endl;
  }
  catch(...){
    cerr << "Error::EmptyStackException, something is amiss!" << endl;
    exit(1);
  }
}

//Testing DoublingArrayStack
template <typename T, typename IT>
void test_DoublingArrayStack(IT& _in, int _n){
  cout << "Please enter stack capacity: ";
  int stack_capacity;
  cin >> stack_capacity;
  DoublingArrayStack<T> as1(stack_capacity);
  TestStack_correctness<DoublingArrayStack<T>, IT>(as1, _in, _n);
  cout << "End Test Array" << endl;
}

//Testing ListStack
template <typename T, typename IT>
void test_ListStack(IT& _in, int _n){
  ListStack<T> ls1;
  TestStack_correctness<ListStack<T>, IT>(ls1, _in, _n);
}


int main(){
  string in[NUM] = {
    " 1: cashew", " 2: Brazil nut",
    " 3: chestnut", " 4: pistachio",
    " 5: walnut", " 6: pecan",
    " 7: peanut", " 8: coconut",
    " 9: hazelnut", " 10: pine nut"};
  
  vector<int> v;  
  for(size_t i = 0; i < 10000000; ++i){
    int r = rand(); // Get a random number
    v.push_back(r);
  }

  //Test array stacks
  //////////////////////////////////////////////////////////
  // Test the array stack using array of
  // strings as input to stack
  //////////////////////////////////////////////////////////
 test_DoublingArrayStack<string, string[NUM]>(in, NUM);
  ///////////////////////////////////////////////////////////
  // Test array stack using vector of 
  // random numbers as input to stack
  ///////////////////////////////////////////////////////////
 test_DoublingArrayStack<int, vector<int> >(v, 10000000);
  

  //Test list stack
  //////////////////////////////////////////////////////////
  // Test list stack using array of
  // strings as input to stack
  //////////////////////////////////////////////////////////
	//test_ListStack<string, string[NUM]>(in, NUM);
  //////////////////////////////////////////////////////////
  // Test list stack using vector of
  // random numbers as input to stack
  //////////////////////////////////////////////////////////
  	//test_ListStack<int, vector<int> >(v, 1000);
  
}