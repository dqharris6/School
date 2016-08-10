// RadixSort
// Dalton Harris, Parker Ransleben

#include <iostream>

using namespace std;

template <class T>
class RadixSort
{
public :
	RadixSort(T* data, int size) : sorted(data), s(size) {} //constructor
	
	~RadixSort() {delete sorted;} //destructor
	
	void set_data(T* data) {sorted = data;} //changes arrays between sorted, unsorted and reversed
	
	void set_size(int size) {s = size;} //changes arrays with size
	
	void sort() {sortHelper();} //generic method
	
	void sortHelper(); //where the actual sorting is done
	
	void shift(int shifter); //shifts elements
	
	void print(); //writes all elements of the array
	
	int comp() {return 0;} //for template arguement
	
	//bucket Structure
	struct bucket 
	{						
		T  element; //element
		bucket* below; //bucket below

		//constructor
		bucket(T const& e, bucket* b) : element(e), below(b) {}
	};
	
protected:
	T* sorted;
	int s;
};

template <typename T>
void
RadixSort<T>::sortHelper()
{
	bucket** buckets = new bucket*[10]; //an array of 10 bucket pointers, one for each 
	//finding max number
	int max = sorted[0];
	for(int x = 1; x < s; ++x)
		if(sorted[x] > max)
			max = sorted[x];
	//sorting...
	for(int digit = 1; max/digit > 0; digit *= 10) //sorts by all digits
	{
		for(int i = 0; i < s; ++i) //sorts by 1 digit at a time
		{
			T store = (sorted[i] / digit) % 10; //Stores which digit it goes to
			bucket* temp = new bucket(sorted[i], buckets[store]);
			buckets[store] = temp; //puts pointer to the digit from buckets[0-9]
		}
		int count = 9;
		int index = s-1; //goes from 10 -> 0 because pointers are stored in reverse order
		while(count > -1) //copies buckets[] to sorted[] array
		{
			if (buckets[count] != nullptr) //if it's not empty
			{
				sorted[index] = buckets[count]->element; //put element at end of array
				--index;
				while(buckets[count]->below != nullptr) //if there are more of the same digit elements, go more down the buckets
				{
					sorted[index] = buckets[count]->below->element;
					--index;
					buckets[count] = buckets[count]->below;
				}
			}
			--count;
		}

		for(int i = 0; i < s; ++i) //clears buckets array
		{
			buckets[i] = nullptr;
		}

	}
}


template <typename T>
void
RadixSort<T>::shift(int shifter)
{
	for(int x = 0; x < s; ++x)
	{
		sorted[x] -= abs(shifter);
	}
}

template <typename T>
void
RadixSort<T>::print()
{
	for(int x = 0; x < s; ++x)
		cout << sorted[x] << endl;
}
