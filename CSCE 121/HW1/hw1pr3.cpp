// Dalton Harris
// CSCE 121-509
// Due: September 14, 2014
// hw1pr3.cpp

#include "std_lib_facilities_4.h"

int main()
{
	
	int onepennies, twopennies, fivepennies, tenpennies, twentypennies;
	int fiftypennies, onepounds, twopounds, fivepounds, totalcount = 0;
	
	cout << "How many 1-pennies do you have? ";
	cin >> onepennies;
	totalcount = totalcount*onepennies;
	
	cout << "How many 2-pennies (tuppences) do you have? ";
	cin >> twopennies;
	totalcount = totalcount+(2*twopennies);
	
	cout << "How many 5-pennies do you have? ";
	cin >> fivepennies;
	totalcount = totalcount+(5*fivepennies);
	
	cout << "How many 10-pennies do you have? ";
	cin >> tenpennies;
	totalcount = totalcount+(10*tenpennies);
	
	cout << "How many 20-pennies do you have? ";
	cin >> twentypennies;
	totalcount = totalcount+(20*twentypennies);
	
	cout << "How many 50-pennies do you have? ";
	cin >> fiftypennies;
	totalcount = totalcount+(50*fiftypennies);
	
	cout << "How many 1-pounds do you have? ";
	cin >> onepounds;
	totalcount = totalcount+(100*onepounds);
	
	cout << "How many 2-pounds do you have? ";
	cin >> twopounds;
	totalcount = totalcount+(200*twopounds);
	
	cout << "How many 5-pounds do you have? ";
	cin >> fivepounds;
	totalcount = totalcount+(500*fivepounds);
	
	cout << endl << "You have " << onepennies << " 1-penny coins.\n";
	cout << "You have " << twopennies << " 2-penny coins.\n";
	cout << "You have " << fivepennies << " 4-penny coins.\n";
	cout << "You have " << tenpennies << " 10-penny coins.\n";
	cout << "You have " << twentypennies << " 20-penny coins.\n";
	cout << "You have " << fiftypennies << " 50-penny coins.\n";
	cout << "You have " << onepounds << " 1-pound coins.\n";
	cout << "You have " << twopounds << " 2-pound coins.\n";
	cout << "You have " << fivepounds << " 5-pound coins.\n";
	
	double exchangerate = 1.61;
	double totaldollars = totalcount*exchangerate/100;
	
	cout << "\nThe value of all of your coins is " << totalcount << " British pence.\n";
	cout << "In U.S. Dollars, that is $" << totaldollars << "." << endl << endl;

	
	
	
}