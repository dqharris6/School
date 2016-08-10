// HeapSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class HeapSort
{
public :
	HeapSort(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~HeapSort() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //navigate between s, uns, reversed
	
	void set_size(int size) {s = size;} //changes array size
	
	void sort() {sortHelper();} //generic method
	
	void sortHelper(); //handles sorting
	
	void downHeap(int parent, int top); //heap, then sort
	
	void swap(int child, int parent); //handles swaps
	
	void print(); //writes elements
	
	long comp() {return comparisons;} //# comparisons
	
protected:
	T* sorted;
	int s;
	long comparisons;
};

template <typename T>
void
HeapSort<T>::sortHelper()
{
	for(int i = s/2; i > -1; --i) //makes data set a heap
	{
		downHeap(i,s);
	} 
	for(int i = 1; i < s; ++i) //sorts the data from the heap
	{
		swap(0, s-i);
		downHeap(0, s-i);
	}
}

template <typename T>
void
HeapSort<T>::swap(int child, int parent)
{
	T temp = sorted[child];
	sorted[child] = sorted[parent];
	sorted[parent] = temp;
}

template <typename T>
void
HeapSort<T>::downHeap(int parent, int top)
{
	int leftChild = 2*parent + 1;//+1 because heap starts at 0
	int rightChild = 2*(parent + 1);

	if(leftChild >= top && rightChild >= top) //if both children don't exist i.e. leaf, then exit
		return;
	if(++comparisons && rightChild >= top && sorted[leftChild] < sorted[parent]) //no right child
	{
		swap(leftChild,parent);
		downHeap(leftChild, top);
	}
	else if (leftChild < top && rightChild < top) //if both children exist and are in range
	{ 
		bool compare = sorted[leftChild] < sorted[rightChild]; //is the left less than right?
		bool lpComp = sorted[leftChild] < sorted[parent]; //is the left less than the parent?
		bool rpComp = sorted[rightChild] < sorted[parent]; //is the right less than the parent

		if(++comparisons && lpComp && compare) //if left is smaller than parent AND right
		{
			swap(leftChild,parent);
			downHeap(leftChild, top);
		}
		else if(++ comparisons && rpComp && !compare) //the right is smaller than the parent AND the left child
		{
			swap(rightChild,parent);
			downHeap(rightChild, top);
		}
	}
}

template <typename T>
void
HeapSort<T>::print()
{
	for(int x = s-1; x > -1; --x)
		cout << sorted[x] << endl;
}
