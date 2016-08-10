// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw3pr4.cpp

#include "std_lib_facilities_4.h"

double my_sqrt_1(double n)
{
	double x = 1;
	int loop;
	for (loop = 0; loop<10; loop++){
		x = (x + (n /x) )/2;}
		return x;
}

double my_sqrt_2(double n)
{
	double result = 1;
	if(n>8.0/5){
		while(n>8.0/5){
			n=n/4;
			result=result*2;}
		return result*my_sqrt_1(n);}
	
	else if(n<2.0/5){
		while(n<2.0/5){
			n = n*4;
			result = result/2;}
		return result*my_sqrt_1(n);} 
	
	else {
		return my_sqrt_1(n);}
}

int main()
{
	cout << endl;
	for(auto k : {-100, -10, -1, 0, 1, 10, 100}){
	double n1 = M_PI * pow(10.0, k);
	double squareroot = sqrt(n1);
	double error = 100*((my_sqrt_2(n1)-squareroot)/squareroot);
	cout << setprecision(8) << setw(18) << left << n1 << setw(18) << left << my_sqrt_2(n1) << setw(18) << left << squareroot << setw(18) << left << error << endl;}
	cout << endl;
	return 0;
}