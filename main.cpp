#include <iostream>
#include <string>

#include "Money.h"
#include "Bank.h"

using namespace std;

int main( int argc, const char* argv[] )
{
	double input;
	char choice;

	//cout << "Would you like to create a bank with customizable priorities? Enter \"y\" for yes or \"n\" for no." << endl;
	//cin >> choice;
	//if (choice == 'y') {
		CustomizedBank myBank;
	//}

	myBank.buildMoney();

	// Testing modifyBalance
	cout << "Enter an input: ";
	cin >> input;
	myBank.modifyBalance(input);
	
	// Testing print
	myBank.print();

	// Testing modifyMoney (for CustomizedBank only)
	myBank.modifyMoney();

	return 0;
}