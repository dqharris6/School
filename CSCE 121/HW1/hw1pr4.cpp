// Dalton Harris
// CSCE 121-509
// Due: September 14, 2014
// hw1pr4.cpp

#include "std_lib_facilities_4.h"

int main()
{
	int x = 1;
	for (int loop = 1; loop <=11; loop++)
	{
	double y = sqrt(x);
	cout << "square root of " << x << " = " << y << endl;
	x = x*10;
	}
	
	cout << "This program contains some strange values because 1410065408 \nis the maximum value that an integer can be stored into." << endl;
}