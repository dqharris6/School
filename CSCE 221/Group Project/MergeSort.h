// MergeSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class MergeSort
{
public :
	MergeSort(T* data, int size) : sorted(data), s(size) {comparisons = 0;} //Constructor
	
	~MergeSort() {delete sorted;} //Destructor
	
	void set_data(T* data) {sorted = data;comparisons = 0;} //changes arrays between sorted, unsorted and reversed
	
	void set_size(int size) {s = size;} //changes size with array
	
	void sort() {sortHelper(sorted, 0, s-1);} // call sorthelper

	void sortHelper(T* arr, int first, int last); //divides array to its most basic elements
	
	void merge(T* arr, int first, int last, int mid); //puts array back together
	
	long comp() {return comparisons;} //the number of comparisons
	
	void print(); //writes all elements of the array
	
	
protected:
	T* sorted;
	int s;
	long comparisons;
};

template <typename T>
void
MergeSort<T>::sortHelper(T* arr, int first, int last) //Recursive method, splits array up
{
	if (first < last)
	{
		int middle = (first + last)/2;
		sortHelper(arr, first, middle); //sorts left half (recursively)
		sortHelper(arr, middle + 1, last); //sorts right half (recursively)
		merge(arr, first, last, middle); //merges both halves
	}
}

template <typename T>
void
MergeSort<T>::merge(T* arr, int first, int last, int mid) //puts array back together
{
	T* temp = new T[s];
	int count = first;
	int	leftI = first; 
	int rightI = mid + 1;
	while(leftI <= mid && rightI <= last) //initial comparison and merging
	{
		if(arr[leftI] < arr[rightI]) //if right side is bigger, left comes first
		{
			++comparisons;
			temp[count] = arr[leftI];
			++leftI;
		}
		else //if left side is bigger, add right element
		{
			++comparisons;
			temp[count] = arr[rightI];
			++rightI;
		}
		++count;
	}
	while (leftI <= mid) //adding any remaining left elements
	{
		temp[count] = arr[leftI];
		++leftI;
		++count;
	}
	while (rightI <= last) //adding any remaining right elements
	{
		temp[count] = arr[rightI];
		++rightI;
		++count;
	}
	
	for(int x = first; x < count; ++x) //copying over elements
		arr[x] = temp[x];
		
	delete[] temp;	
}

template <typename T>
void
MergeSort<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}
