#include "std_lib_facilities_4.h"
// #include <iostream>
// #include <vector>
// using namespace std;

// void print_binary(int);
// int binary(int decimal_number)
// {
//
// }

// int main(void)
// {
// 	int input_number;
// 	
// 	cout << "Number to be converted to binary: ";
// 	cin >> input_number;
// 	
// 	if(input_number > 0)
// 	{
// 		binary_output = binary(input_number);
// 		cout << input_number << " converted to binary is " << binary_output;
// 	}
// 	
// 	return 0;
// }

void binary(int);

int main(void) {
    int number;
 
    cout << "Please enter a positive integer: ";
    cin >> number;
    if (number < 0)
        cout << "That is not a positive integer.\n";
    else {
        cout << number << " converted to binary is: ";
        binary(number);
        cout << endl;
    }
}
 
void binary(int number) {
    int remainder;
 
    if(number <= 1) {
        cout << number;
        return;
    }
 
 
    remainder = number%2;
    binary(number >> 1);
    cout << remainder;
}

