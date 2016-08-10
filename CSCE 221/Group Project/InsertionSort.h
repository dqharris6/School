// InsertionSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class InsertionSort
{
public :
	InsertionSort(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~InsertionSort() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //navigate between s, uns, reversed
	
	void set_size(int size) {s = size;} //change array size
	
	void sort() {sortHelper();} //generic method
	
	void sortHelper(); // handles sorting
	
	void print(); //writes elements
	
	long comp() {return comparisons;} //# comparisons
	
protected:
	T* sorted;
	int s,k,temp;
	long comparisons;
};

template <typename T>
void
InsertionSort<T>::sortHelper()
{
	for(int i = 2; i < s; i++)
	{
		k = i;
		
		while(k > 0 && sorted[k] < sorted[k-1]) //swaps until greater than predeccesor
		{
			++comparisons;
			temp = sorted[k];
			sorted[k] = sorted[k-1]; //swaps
			sorted[k-1] = temp;
			k--;
			comparisons++;
		}
	}
}

template <typename T>
void
InsertionSort<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}