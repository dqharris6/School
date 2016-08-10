// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw2pr2.cpp

#include "std_lib_facilities_4.h"

int main()
{
	string amendment1 = "Amendment 1 states that Congress cannot enact a law that prohibits free speech, religion, press, or assembly.";
	string amendment2 = "Amendment 2 states that all citizens have the right to own and bear firearms.";
	string amendment3 = "Amendment 3 states that during times of peace, soldiers cannot take up residence in someone else's house without that owner's permission.";
	string amendment4 = "Amendment 4 states that a person, his house, and his belongings cannot be searched or taken, and he cannot be given a warrant without good reason.";
	string amendment5 = "Amendment 5 states that a person cannot be tried for a serious crime without a Grand Jury deciding there is enough evidence for a trial.";
	string amendment6 = "Amendment 6 states that a person should be given a speedy and public trial by a jury of his peers in the state and district where he committed the crime.";
	string amendment7 = "Amendment 7 states that a person has the right to a jury in a civil case where more than $20 is being disputed.";
	string amendment8 = "Amendment 8 states that excessive bails/fines cannot be ordered, and cruel and unusual punishments cannot be imposed.";
	string amendment9 = "Amendment 9 states that a person has rights beyond those listed in this Constitution.";
	string amendment10 = "Amendment 10 states that areas that aren't directly governed or prohibited by this Constitution may be made up by individual states.";
	
	vector <string> answers;
	answers.push_back(amendment1);
	answers.push_back(amendment2);
	answers.push_back(amendment3);
	answers.push_back(amendment4);
	answers.push_back(amendment5);
	answers.push_back(amendment6);
	answers.push_back(amendment7);
	answers.push_back(amendment8);
	answers.push_back(amendment9);
	answers.push_back(amendment10);
	
	double chosen_amendment;
	cout << "Which amendment would you like to learn about? ";
	cin >> chosen_amendment;
	
	if(chosen_amendment >= 0 && chosen_amendment <= 10)
	{
		cout << endl << answers[chosen_amendment-1] << endl << endl;
	}
	else
	{
		cout << "Invalid entry. Please input a number 1-10." << endl << endl;
	}
	
	
}