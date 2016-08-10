// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw2pr1.cpp

#include "std_lib_facilities_4.h"

int main()
{
	int amendment_number;
	
	cout << "Which amendment would you like to learn about? ";
	cin >> amendment_number;
	
	if(amendment_number == 1)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "Congress cannot enact a law that prohibits free speech, religion, press, or assembly.";
		cout << endl;
	}
	
	else if(amendment_number == 2)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "all citizens have the right to own and bear firearms.";
		cout << endl;
	}	
	
	else if(amendment_number == 3)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "during times of peace, soldiers cannot take up residence in someone else's house without that owner's permission.";
		cout << endl;
	}
	
	else if(amendment_number == 4)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "a person, his house, and his belongings cannot be searched or taken, and he cannot be given a warrant without good reason.";
		cout << endl;
	}	
	
	else if(amendment_number == 5)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "a person cannot be tried for a serious crime without a Grand Jury deciding there is enough evidence for a trial.";
		cout << endl;
	}	
	
	else if(amendment_number == 6)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "a person should be given a speedy and public trial by a jury of his peers in the state and district where he committed the crime.";
		cout << endl;
	}
	
	else if(amendment_number == 7)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "a person has the right to a jury in a civil case where more than $20 is being disputed.";
		cout << endl;
	}	
	
	else if(amendment_number == 8)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "excessive bails/fines cannot be ordered, and cruel and unusual punishments cannot be imposed.";
		cout << endl;
	}
	
	else if(amendment_number == 9)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "a person has rights beyond those listed in this Constitution.";
		cout << endl;
	}		
	
	else if(amendment_number == 10)
	{
		cout << endl;
		cout << "Amendment " << amendment_number << " states that ";
		cout << "areas that aren't directly governed or prohibited by this Constitution may be made up by individual states.";
		cout << endl;
	}	
	
	else
	{
		cout << endl;
		cout << "That is not a valid input. Please input a number between 0 and 10.";
		cout << endl;
	}				
}