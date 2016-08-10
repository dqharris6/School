// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw4pr2.cpp

#include "std_lib_facilities_4.h"

bool yes()
{
	string inputstring;
	cin >> inputstring;
	char firstletter = inputstring[0];
	if(firstletter == 'y' || firstletter == 'Y'){return true;}
	else{return false;}
}
int main()
{
try{
	cout << "Are you thinking of an animal? (Yes or No) ";
	bool question1 = yes();
	cout << "Are you thinking of an actor? (Yes or No) ";
	bool question2 = yes();
	cout << "Are you thinking of something that likes the water? (Yes or No) ";
	bool question3 = yes();
	
	if(question1 && !question2 && !question3){
		cout << endl << "You must be thinking of a dog.";}
		
	else if(question1 && question2 && !question3){
		cout << endl << "You must be thinking of Clifford the Big Red Dog.";}
		
	else if(question1 && question2 && question3){
	cout << endl << "You must be thinking of Shamu.";}
	
	else if(!question1 && question2 && question3){
		cout << endl << "You must be thinking of David Hasslehoff.";}	

	else if(!question1 && question2 && !question3){
		cout << endl << "You must be thinking of Tom Cruise in Top Gun.";}

	else if(!question1 && !question2 && question3){
		cout << endl << "You must be thinking of a carrot.";}
		
	else if(question1 && !question2 && question3){
		cout << endl << "You must be thinking of a fish.";}	
		
	else if(!question1 && !question2 && !question3){
		cout << endl << "You must be thinking of fresh, new pair of Jordans.";}		
		
	cout << endl;	
	return 0;
	}		
catch(exception&e){
	cerr << "error: " << e.what() << endl;
	keep_window_open();
	return 1;}
	
catch(...){
	cerr << "unknown exception" << endl;
	keep_window_open();
	return 2;}	
}

