// Deterministic QuickSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class QuickSortD
{
public :
	QuickSortD(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~QuickSortD() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //changes arrays between sorted, unsorted and reversed
	
	void set_size(int size) {s = size;} //changes array with size
	
	void sort() {sortHelper(sorted, 0, s-1);} //generic method
	
	void sortHelper(T* arr, int from, int to); //where actual sorting happens
	
	int partition(T* arr, int from, int to); //splits array up
	
	int comp() {return comparisons;} //return comparisons
	
	void print(); //prints sorted array
	
	
protected:
	T* sorted;
	int s;
	int comparisons;
};

template <typename T>
void
QuickSortD<T>::sortHelper(T* arr, int from, int to)
{
	if (from < to)
	{
		int pivot = partition(arr, from, to); //get pivot point
		sortHelper(arr, from, pivot); //recurse from the front to the pivot point
		sortHelper(arr, pivot + 1, to); //recurse from the pivot to the end
	}
}

template <typename T>
int
QuickSortD<T>::partition(T* arr, int from, int to)
{
	T pivot = arr[(from + to)/2]; //start at half the size
	int left = from - 1;
	int right = to + 1;
	while(left < right) //go through array and switch arr[left] < arr[right]
	{
		++left;
		while(arr[left] < pivot) //increment left until pivot
			++left;
		--right;
		while(arr[right] > pivot) //decrement right until pivot
			--right;
		if(++comparisons && left < right) //swap if the sizes are different
		{
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
	}
	return right;	
}

template <typename T>
void
QuickSortD<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}
