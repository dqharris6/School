// BubbleSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class BubbleSort
{
public :
	BubbleSort(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~BubbleSort() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //navigates between s, uns, reversed
	
	void set_size(int size) {s = size;} //changes array size
	
	void sort() {sortHelper();} //generic method
	
	void sortHelper(); //sorts
	
	void swap(int left, int right); //handles swaps
	
	void print(); //writes elements
	
	long comp() {return comparisons;} //# comparisons
	
protected:
	T* sorted;
	int s;
	long comparisons;
};

template <typename T>
void
BubbleSort<T>::sortHelper()
{
	int swapped = 1;
	int length = s;
	for(int i = 1; (i <= s) && swapped; ++i)
	{
		swapped = 0; //continue swapping until every element is swapped
		for(int k = 0; k < s-1; ++k) 
		{
			if(sorted[k] > sorted[k+1]) //if element is less than the one before
			{
				++comparisons; 
				swap(k,k+1); //swap each position
				swapped = 1; //this means a swap has occured
			}
		}
	}
}

template <typename T>
void
BubbleSort<T>::swap(int left, int right)
{
	T temp = sorted[left];
	sorted[left] = sorted[right];
	sorted[right] = temp;
}

template <typename T>
void
BubbleSort<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}