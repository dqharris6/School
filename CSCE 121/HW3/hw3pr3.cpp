// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw3pr3.cpp

#include "std_lib_facilities_4.h"

int main()
{
	try{
	string input;
	int aggiecounter = 0;

	cout << "Enter your string: ";
	while(true){
		cin >> input;
		if(input == "aggie" || input == "aggies" || input == "Aggie" || input == "Aggies"){
			aggiecounter++;
			cout << "Aggie counter is " << aggiecounter << endl;}
			   }
	return 0;
	   }
	
	catch(exception&e){
	cerr << "error: " << e.what() << endl;
	keep_window_open();
	return 1;}
	
	catch(...){
	cerr << "unknown exception" << endl;
	keep_window_open();
	return 2;}	
}