// SelectionSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class SelectionSort
{
public :
	SelectionSort(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~SelectionSort() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //changes arrays between sorted, unsorted and reversed
	
	void set_size(int size) {s = size;} //changes arrays with size
	
	void sort() {sortHelper();} //generic method
	
	void sortHelper(); //where the actual sorting is done
	
	void swap(int left, int right); //used to switch places easily
	
	void print(); //writes all elements of the array
	
	long comp() {return comparisons;} //the number of comparisons
	
protected:
	T* sorted;
	int s;
	long comparisons;
};

template <typename T>
void
SelectionSort<T>::sortHelper()
{
	int minIndex, length, temp, i;
	
	for (int startIndex = 0; startIndex < s-1; startIndex++) //goes for all elements
	{
		minIndex = startIndex;
		for (i = startIndex + 1; i < s; i++) //goes for 1 element through all
			if (++comparisons && sorted[i] < sorted[minIndex]) 
				minIndex = i;
		//still swaps with itself, therefore, always same number of comparisons
		swap(startIndex, minIndex); //Don't add a comparison if it swaps with itself
	}
}

template <typename T>
void
SelectionSort<T>::swap(int left, int right)
{
	T temp = sorted[left];
	sorted[left] = sorted[right];
	sorted[right] = temp;
}

template <typename T>
void
SelectionSort<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}
