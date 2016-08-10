// Dalton Harris
// CSCE 121-509
// Due: September 14, 2014
// hw1pr2.cpp

#include "std_lib_facilities_4.h"

int main()
{
	double operand1, operand2, answer;
	string operation;
	
	cout << "\nInsert first operand: ";
	cin >> operand1;
	
	cout << "Insert second operand: ";
	cin >> operand2;
	
	cout << "Insert operation (plus, minus, mul, div or corresponding symbol): ";
	cin >> operation;
	
	if(operation == "+" || operation == "plus")
	{
		answer = operand1+operand2;
	}
	
	else if(operation == "-" || operation == "minus")
	{
		answer = operand1-operand2;
	}
	
	else if(operation == "*" || operation == "mul")
	{
		answer = operand1*operand2;
	}
	
	else if(operation == "/" || operation == "div")
	{
		answer = operand1/operand2;
	}
	
	else 
	{
		answer = 0;
		cout << "\nInvalid operation\n";
	}
	
	cout << "Your answer is " << answer << endl << endl;
}