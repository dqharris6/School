// main.cpp
// Dalton Harris, Parker Ransleben
// CSCE221-508

#include <iostream>
#include <fstream>
#include <sstream>
#include "BubbleSort.h" //1
#include "SelectionSort.h" //2
#include "InsertionSort.h" //3
#include "HeapSort.h" //4
#include "MergeSort.h" //5
#include "QuickSortD.h" //6
#include "QuickSortR.h" //7
#include "RadixSort.h" //8
#include <string>
#include <cstdlib>
#include<ctime>
#include <stdexcept>

template <typename S>
void test(S so, string name, string test_type)
{
	if (test_type == "1")
	{
		cout <<"\n\n\n\nSorting \"numbers.txt\" using " << name << endl;
		so.sort();
		so.print();
		cout << "Comparisons: " << so.comp() << endl;
	}
	else if (test_type == "2")
	{
		ofstream ost; //writing to the file
		ost.open(name + ".txt");
		ost << name << ":" << endl;
		for(int number = 1000; number <= 50000; number += 1000)
		{
			so.set_size(number);
			int* unsorted = new int[number];
			int* sorted = new int[number];
			int* reversed = new int[number];
			for(int j = 0; j < number; ++j)
			{
				unsorted[j] = rand() % 1000 + 1;
			}
			for(int j = 0; j < number; ++j)
			{
				sorted[j] = j;
				reversed[j] = number - j;
			}
			//unsorted
			so.set_data(unsorted);
			clock_t start1 = clock();
			so.sort();
			clock_t end1 = clock();
			int comp1 = so.comp(); //comparisons for unsorted
			//sorted
			so.set_data(sorted);
			clock_t start2 = clock();
			so.sort();
			clock_t end2 = clock();
			int comp2 = so.comp(); //comparisons for sorted
			//reversed
			so.set_data(reversed);
			clock_t start3 = clock();
			so.sort();
			clock_t end3 = clock();
			int comp3 = so.comp(); //comparisons for reversed
			
			//writing to file
			ost << number << " Elements: " << endl
				<< "Unsorted: " << (double)(end1 - start1)/CLOCKS_PER_SEC << "\t" << comp1 << " comparisons" << endl
				<< "Sorted:   " << (double)(end2 - start2)/CLOCKS_PER_SEC << "\t" << comp2 << " comparisons" << endl
				<< "Reversed: " << (double)(end3 - start3)/CLOCKS_PER_SEC << "\t" << comp3 << " comparisons" << endl;
			cout << number << endl;
		}
		ost.close();
	}
	else
		cout << "Something went wrong";
}

int main()
{
	try
	{
		//data to be read into
		int type, number, input; //ints to store
		string t, n, i, choose; //strings to be converted
		ifstream ist1; //reads in numbers.txt
		int* ar;
		int* sorted;
		int* reversed;
		cout << "What would you like to test: (please use number in front)\n"
			 << "1: Sorting\n"
			 << "2: Time\n"
			 << "3: Special Radix Sort Test (for 2^16 - 1 handling)\n"
			 << "4: Exit\n";
		cin >> choose;
		while (choose != "1" && choose != "2" && choose != "3" && choose != "4") //checks for valid input
		{
			cout << "Error: Invalid Input. Please try again.\n\n";
			cout << "What would you like to test: (please use number in front)\n"
			 << "1: Sorting\n"
			 << "2: Time\n"
			 << "3: Special Radix Sort Test (for 2^16 - 1 handling)\n"
			 << "4: Exit\n";
			cin >> choose; 
		}
		if(choose == "1") //testing the sorting ability of a sort
		{
			//Checking for file
			ist1.open("numbers.txt");	
			if (!ist1) runtime_error("File does not exist.");
		
			//Reading in data here
			getline(ist1, t);
			istringstream is1(t);
			is1 >> type; //gets the type of sort
			getline(ist1, n);
			istringstream is2(n);
			is2 >> number; //the number of elements
			ar = new int[number]; //array to hold the data of the file
			int index = 0;
			while(getline(ist1, i)) //putting the data in the array
			{
				istringstream is3(i);
				is3 >> input;
				ar[index] = input;
				++index;
			}
		}
		else if (choose == "2")//testing time
		{
			//Choosing the sort to test
			cout << "What kind of Sort? (please use number in front)\n"
				 << "1: BubbleSort\n"
				 << "2: SelectionSort\n"
				 << "3. InsertionSort\n"
				 << "4. HeapSort\n"
				 << "5. MergeSort\n"
				 << "6. Deterministic QuickSort\n"
				 << "7. Random QuickSort\n"
				 << "8. RadixSort\n";
			
			string sort;
			cin >> sort;
			while (sort != "1" && sort != "2" && sort != "3" && sort != "4" &&
				   sort != "5" && sort != "6" && sort != "7" && sort != "8")
			{
				cout << "Error: Invalid type. Please try again.\n\n";
				cout << "What kind of Sort? (please use number in front)\n"
				 << "1: BubbleSort\n"
				 << "2: SelectionSort\n"
				 << "3. InsertionSort\n"
				 << "4. HeapSort\n"
				 << "5. MergeSort\n"
				 << "6. Deterministic QuickSort\n"
				 << "7. Random QuickSort\n"
				 << "8. RadixSort\n";
				cin >> sort;
			}
			istringstream is(sort);
			is >> type;
			
			ar = new int[1]; //just so I can pass a dummy parameter
			ar[0] = 0;
		}
		else if (choose == "3") //test the Radix sort's ability to hold 2^16 - 1 integers from [-2^15,2^15 - 1]
		{
			number = 65536;
			ar = new int[number]; //2^16 - 1;
			int low = -32768;
			int move = low;
			int high = 32767;
			for(int i = 0; i < number; ++i)
			{
				ar[i] = move - low; //a number between [0, 2^16 - 1] due to the shift
				++move;
			}
			RadixSort<int> testing(ar,number);
			testing.sort(); //sorting positive values
			testing.print();
			testing.shift(low); //shifting the array back to [-2^15,2^15 - 1]
			testing.print();
			return 0; //we don't want to run any other test after this.
		}
		else {return 0;}
		string name;
		switch(type) //putting in the test to do i.e. time or sorting numbers.txt. case #s based off of website order
		{
			case 1: 
			name = "BubbleSort";
			test(BubbleSort<int>(ar, number), name, choose);
				break;
			case 2: 
			name = "SelectionSort";
			test(SelectionSort<int>(ar, number), name, choose);
				break;
			case 3: 
			name = "InsertionSort";
			test(InsertionSort<int>(ar, number), name, choose);
				break;
			case 4: 
			name = "HeapSort";
			test(HeapSort<int>(ar, number), name, choose);
				break;
			case 5: 
			name = "MergeSort";
			test(MergeSort<int>(ar, number), name, choose);
				break;
			case 6: 
			name = "QuickSortD";
			test(QuickSortD<int>(ar, number), name, choose);
				break;
			case 7: 
			name = "QuickSortR";
			test(QuickSortR<int>(ar, number), name, choose);
				break;
			case 8: 
			name = "RadixSort";
			test(RadixSort<int>(ar, number), name, choose);
				break;
			default: "Something went wrong";
		}
	}
	
	catch(exception& e) {cerr << e.what();}
	catch(...) {cerr << "Unknown error";} 
	return 0;
}
