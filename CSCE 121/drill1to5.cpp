#include "std_lib_facilities_4.h"

int main()
{
	double value1, value2, smallervalue, largervalue, difference;
	while(true)
	{
		cin >> value1 >> value2;
		
		if(!cin)
		{
			cin.clear();
			char term;
			cin >> term;
			if(term == '|')
			break;
		}
		cout << value1 << " " << value2 << endl;
		
		if(value1==value2)
		{
			cout << "the numbers are equal";
		}
		else if(value1<value2)
		{
			cout << "the smaller value is: " << value1 << endl;
			cout << "the larger value is: " << value2;
			smallervalue = value1;
			largervalue = value2;
		}
		else if(value2<value1)
		{
			cout << "the smaller value is: " << value2 << endl;
			cout << "the larger value is: " << value1;	
			smallervalue = value2;
			largervalue = value1;
		}
		
		difference = largervalue-smallervalue;
		if(difference<=.01)
		{
			cout << endl << "the numbers are almost equal";
		}
		cout << endl << endl;
	}
	return 0;
}