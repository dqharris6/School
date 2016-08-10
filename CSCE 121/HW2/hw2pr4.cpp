// Dalton Harris
// CSCE 121-509
// Due: September 21, 2014
// hw2pr4.cpp

#include "std_lib_facilities_4.h"

int main()
{
	vector <int> denominations = {1,2,5,10,20,25,50,100,200,500};
	vector <int> coin_amounts;
	vector <int> totals;
	
	int coin_amounts_input, edited_counter, edited_counter2, counter, counter2;
	double aggregate_cost, exchange_rate = 1.61, total_dollars, output_this_value;
	
	for(counter = 0; counter < 10; counter++)
	{
		if(counter <= 6)
		{
			cout << "How many " << denominations[counter] << "-pennies do you have? ";
			cin >> coin_amounts_input;
			if(!cin)
			{
				cout << "Invalid entry. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				counter--;
			}
			else
			{
			coin_amounts.push_back(coin_amounts_input);
			}
		}
		else
		{
			edited_counter = denominations[counter]/100;
			cout << "How many " << edited_counter << "-pounds do you have? ";
			cin >> coin_amounts_input;
			coin_amounts.push_back(coin_amounts_input);
		}
	}
	
	cout << endl;
	
	for(counter2 = 0; counter2 <= 9; counter2++)
	{
		totals.push_back(denominations[counter2]*coin_amounts[counter2]);
		aggregate_cost = aggregate_cost + (denominations[counter2]*coin_amounts[counter2]);
		
		if(counter2 <=6)
		{
			cout << "You have " << coin_amounts[counter2] << " " << denominations[counter2] << "-penny coins." << endl;
		}
		else
		{
			edited_counter2 = denominations[counter2]/100;
			cout << "You have " << coin_amounts[counter2] << " " << edited_counter2 << "-pound coins." << endl;
		}
	}
	
	cout << endl << "The value of all your coins is " << aggregate_cost << " pence." << endl;
	total_dollars = exchange_rate*aggregate_cost;
	output_this_value = total_dollars/100;
	cout << setprecision(2) << fixed << "In US dollars, that is $" << output_this_value << "." << endl;
	
}