#include "std_lib_facilities_4.h"

int main()
{
	double value1, sumcounter;
	vector<double> totalcounter;
	string units;
	double largestvalue = -1*numeric_limits<double>::max();
	double smallestvalue = numeric_limits<double>::max();
	
	while(true)
	{
		cout << endl << "enter a value and unit, press '|' to terminate" << endl;
		cin >> value1 >> units;
		
		if(!cin){
			cin.clear();
			char term;
			cin >> term;
		if(term == '|')
			break;}
			
		cout << "the value you entered is " << value1 << " " << units << endl;
		
		if(units == "cm"){
			value1=value1/1000;}
		
		else if(units == "m"){
			value1=value1;}
		
		else if(units == "in"){
			value1=value1*2.54;
			value1=value1/1000;}
		
		else if(units == "ft"){
			value1=value1*30.48;
			value1=value1/1000;}
		
		else{
			cout << units << " is an illegal unit" << endl;
			break;}
		
		if(value1 < smallestvalue){
			smallestvalue = value1;
			cout << "this is the smallest value so far";}
			
		else if(value1 > largestvalue){
			largestvalue = value1;
			cout << "this is the largest value so far";}
			
		cout << endl;
		sumcounter = sumcounter+value1;
		totalcounter.push_back(value1);
	}
	sort(totalcounter.begin(),totalcounter.end());
	for(double v : totalcounter){
		cout << v << " m  ";}
		
	cout << endl << "total counter = " << sumcounter << " m";
		
	cout << endl;
	return 0;
}