#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string string1, string2, string3, string4, string5, concatenated_string;

ifstream input_stream("text.txt");
ofstream output_stream("text.txt", ofstream::app);
	
string concatenate(string s1, string s2, string s3, string s4, string s5)
{
	string concatenated = s1+","+s2+","+s3+","+s4+","+s5;
	return concatenated;
}

int main()
{
	input_stream >> string1 >> string2 >> string3 >> string4 >> string5;
	concatenated_string = concatenate(string1,string2,string3,string4,string5);
	output_stream << endl << concatenated_string;
	
	return 0;
}