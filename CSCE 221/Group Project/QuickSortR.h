// Randomized QuickSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class QuickSortR
{
public :
	QuickSortR(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //constructor
	
	~QuickSortR() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //changes arrays between sorted, unsorted and reversed
	
	void set_size(int size) {s = size;} //changes size with array
	
	void sort() {sortHelper(sorted, 0, s-1);} //generic method
	
	void sortHelper(T* arr, int from, int to); //sorts the array
	
	int partition(T* arr, int from, int to); //splits array
	
	int comp() {return comparisons;} //return comparisons

	void print(); //prints sorted array
	
	
protected:
	T* sorted;
	int s;
	int comparisons;
};

template <typename T>
void
QuickSortR<T>::sortHelper(T* arr, int from, int to)
{
	if (from < to)
	{
		int pivot = partition(arr, from, to); //get pivot 
		sortHelper(arr, from, pivot); //recurse from front to pivot
		sortHelper(arr, pivot + 1, to); //recurse from pivot to end
	}
}

template <typename T>
int
QuickSortR<T>::partition(T* arr, int from, int to)
{
	int size = to - from;
	T pivot = arr[(rand() % size) + from]; //pivot is random
	int left = from - 1;
	int right = to + 1;
	while(left < right) //goes through array to switch arr[left] < arr[right]
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
QuickSortR<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}
