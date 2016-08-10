#include "SortedPriorityQueue.h"
#include "UnsortedPriorityQueue.h"
#include "HeapPQ.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int type;
	int size;
	int value;
	
	ifstream numbers;
	numbers.open("numbers.txt");
	
	ofstream outfile("Outfile.txt");
	
	numbers >> type >> size;
	
	clock_t start = 0, stop = 0;
	double ms = 0;
	
	switch(type)
	{
		case 0:{	// UNS, cout
			UnsortedPriorityQueue<int> uns;
			start = clock();
				while(numbers>>value){
					uns.insertItem(value);
					}
				while(!uns.isEmpty()){
					stop = clock();
					ms = (double)(stop-start)/CLOCKS_PER_SEC;
					cout << uns.removeMin() << "\t" << ms << endl;
				}
			start = 0;
			break;
		}
		
		case 1:{	// SORT
			SortedPriorityQueue<int> s;
			start = clock();
				while(numbers>>value){
					s.insertItem(value);
					}
				while(!s.isEmpty()){
					stop = clock();
					ms = (double)(stop-start)/CLOCKS_PER_SEC;
					cout << s.removeMin() << "\t" << ms << endl;
				}
			
			break;
		}
		
		default:{	// HEAP
			HeapPQ<int> h(size);
			start = clock();
				while(numbers>>value){
					h.insertItem(value);
					}
				while(!h.isEmpty()){
					stop = clock();
					ms = (double)(stop-start)/CLOCKS_PER_SEC;
					cout << h.removeMin() << "\t" << ms << endl;
				}
				
			break;
		}
	}
}