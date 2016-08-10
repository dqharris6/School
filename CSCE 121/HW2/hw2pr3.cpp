// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw2pr3.cpp

#include "std_lib_facilities_4.h"

// #include <iostream>
// using namespace std;

int main()
{
	double dollars_input, ten_percent_value, left_over_value;
	
	while(true)
	{
	cout << "\nInput in dollars? ";
	cin >> dollars_input;
	
	ten_percent_value = dollars_input*.1;
	left_over_value = dollars_input-(2*ten_percent_value);
	
	if(dollars_input > 0)
		{
		cout << setprecision(2) << fixed << "You should give away $" << ten_percent_value << ", save $" << ten_percent_value;
		cout << setprecision(2) << fixed << " and live on $" << left_over_value << ".";
		cout << "\nPress CTRL+C to exit.";
		cout << endl;
		}
	else
	{
		cout << "Not a valid input. Please enter a number." << endl << endl;
		break;
	}
	}
	
}