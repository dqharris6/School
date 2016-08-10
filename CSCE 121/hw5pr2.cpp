#include "std_lib_facilities_4.h"

int main()
{
	// All needed declarations.
	ifstream myfilein, myfilein2;
	ofstream myfileout;
	string inputfile1, inputfile2, readstring, outputfile;
	int linenumber = 0, vector1size, vector2size;
	vector<string> stringvector1;
	vector<string> stringvector2;
	
	// Prompt user for input files.
	cout << "Input File 1: ";
	cin >> inputfile1;
	cout << "Input File 2: ";
	cin >> inputfile2;
	cout << "Output File: ";
	cin >> outputfile;
		
	// New file streams for file 1 and file 2.
	myfilein.open(inputfile1);
	myfilein2.open(inputfile2);
	myfileout.open(outputfile);
	
	// While file 1 is open, read each entry by line and push back string into a vector.
	if(myfilein.is_open())
	{
		cout << endl << "File 1:" << endl;
		while(!myfilein.eof())
		{
			getline(myfilein, readstring);
			//myfilein >> readstring;
			stringvector1.push_back(readstring);
			cout << stringvector1[linenumber] << endl;
			linenumber++;
		}
	}
	// If file 1 doesn't open, throw an error.
	else
	{
		cout << "Error opening file." << endl;
	}
	
	cout << endl;
	
	// Done with file 1, reset the line number integer.
	linenumber = 0;
	
	// While file 2 is open, read each entry by line and push back string into a vector.
	if(myfilein2.is_open())
	{
		cout << "File 2:" << endl;
		while(!myfilein2.eof())
		{
			getline(myfilein2, readstring);
			//myfilein2 >> readstring;
			stringvector2.push_back(readstring);
			cout << stringvector2[linenumber] << endl;
			linenumber++;
		}
	}
	
	// If file 2 doesn't open, throw an error.
	else
	{
		cout << "Error opening file." << endl;
	}
	
	cout << endl;
	
	// Set these variables to the size of their respective vectors.
	vector1size = stringvector1.size();
	vector2size = stringvector2.size();
	
	// If 2 vectors are the same size, carry on.
	if(vector1size == vector2size)
	{
			
		for(int loop = 0; loop < vector1size; loop++)
		{
			if(stringvector1[loop] == stringvector2[loop])
			{
				myfileout << loop+1 << " : SAME" << endl;
			}
			else
			{
				myfileout << loop+1 << " : DIFF" << endl;
			}
		}
	}
	
	// If vector 1 has more elements, push back zeroes in vector 2 until they are equivalent.
	else if(vector1size > vector2size)
	{
		int difference = vector1size-vector2size;
		for(int loop1 = 0; loop1 < difference; loop1++)
		{
			stringvector2.push_back("0");
		}
			
		for(int loop = 0; loop < vector1size; loop++)
		{
			if(stringvector1[loop] == stringvector2[loop])
			{
				myfileout << loop+1 << " : SAME" << endl;
			}
			else
			{
				myfileout << loop+1 << " : DIFF" << endl;
			}
		}
	}
	
	// If vector 2 has more elements, push back zeroes in vector 1 until they are equivalent.
	else if(vector2size > vector1size)
	{
		int difference = vector2size-vector1size;
		for(int loop2 = 0; loop2 < difference; loop2++)
		{
			stringvector1.push_back("0");
		}
			
		for(int loop = 0; loop < vector2size; loop++)
		{
			if(stringvector1[loop] == stringvector2[loop])
			{
				myfileout << loop+1 << " : SAME" << endl;
			}
			else
			{
				myfileout << loop+1 << " : DIFF" << endl;
			}
		}
	}	
	
	return 0;
}