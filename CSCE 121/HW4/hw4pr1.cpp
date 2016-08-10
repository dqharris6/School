// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw4pr2.cpp

#include "std_lib_facilities_4.h"

int main()
{
try{
	cout << endl << "Quadratic Formula Calculator" << endl;
	
	double Avalue, Bvalue, Cvalue;			// declares inputs
	double discriminant, negativeBvalue;
	double x1, x2;							// declares outputs
	
	cout << "A = "; cin >> Avalue;			// prompting user for inputs
	cout << "B = "; cin >> Bvalue;
	cout << "C = "; cin >> Cvalue;
	
	discriminant = pow(Bvalue,2)-(4*Avalue*Cvalue);			// intermediate calculations
	negativeBvalue = -1*Bvalue;
	
	x1 = (negativeBvalue + sqrt(discriminant)) / (2*Avalue);	// final calculations
	x2 = (negativeBvalue - sqrt(discriminant)) / (2*Avalue);
	
	cout << endl << "x1 = " << x1 << endl << "x2 = " << x2 << endl;		// outputs roots
	
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