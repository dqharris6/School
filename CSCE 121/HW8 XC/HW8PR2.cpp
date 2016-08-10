// Dalton Harris
// CSCE 121-509
// Due: December 11, 2014 (or whatever the due date is)
// hw8pr2.cpp (or whatever this file name is)

#include <regex>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string line;
regex pat2{R"(?!(078-?05-?1120|123-?45-?6789|(\d)\2{2}-?\2{2}-?\2{4}))((?!(000|666|9))\d{3}-?(?!00)\d{2}-?(?!0000)\d{4})"};
smatch matches;

int main(){
try
{
	while(true)
	{
		cout << "Input a Social Security Number (or CTRL+C to exit): "; 
		getline(cin,line);
	
		if(regex_search(line,matches,pat2))
			cout << matches[0] << " is a valid social security number." << endl;
			
		else cout << "That is not a valid social security number." << endl;
			
		cout << endl;
	}
	return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;}
catch (...) {
	cerr << "Some exception\n";
	return 2;}
}