// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw3pr2.cpp

#include "std_lib_facilities_4.h"

double my_sqrt_1(double n)
{
	double x = 1;
	int loop;
	for (loop = 0; loop<10; loop++){
		x = (x + (n /x) )/2;}
		return x;
}

int main()
{
	try{
	cout << endl;
	for(auto k : {-100, -10, -1, 0, 1, 10, 100})
	{
	double n1 = M_PI * pow(10.0, k);
	double squareroot = sqrt(n1);
	double error = 100*((my_sqrt_1(n1)-squareroot)/squareroot);
	cout << setprecision(8) << setw(18) << left << n1 << setw(18) << left << my_sqrt_1(n1) << setw(18) << left << squareroot << setw(18) << left << error << endl;
	}
	
	cout << endl;
	return 0;}
	
	catch(exception&e){
	cerr << "error: " << e.what() << endl;
	keep_window_open();
	return 1;}
	
	catch(...){
	cerr << "unknown exception" << endl;
	keep_window_open();
	return 2;}	
}