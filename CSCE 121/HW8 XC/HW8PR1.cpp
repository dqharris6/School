// Dalton Harris
// CSCE 121-509
// Due: December 11, 2014 (or whatever the due date is)
// hw8pr1.cpp (or whatever this file name is)

#include <regex>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string line;
regex pat("^(97(8|9))(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\-|\\s)?\\d{1}(\\s|\\-)?(\\d|X)$");
smatch matches;

int main(){
try
{

	while(true)
	{
		cout << "Input an ISBN-13 Book Number (or CTRL+C to exit): "; 
		getline(cin,line);
	
		if(regex_search(line,matches,pat))
			cout << matches[0] << " is a valid book number." << endl;
			
		else cout << "That is not a valid book number." << endl;
			
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