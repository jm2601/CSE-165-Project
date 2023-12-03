#include <iostream>

#include "Bank.h"
//#include "CoinBank.h"
//#include "DollarBank.h"

using namespace std;

int main(int argc, const char* argv[])
{
	double input;
	char choice;
	Bank* myBank;

	myBank = new Bank;

	myBank->deposit(100);
	myBank->print();

	myBank->deposit(49, 2);
	myBank->deposit(50, 2);
	myBank->print();

	myBank->withdraw(999);
	myBank->withdraw(50);
	myBank->print();

	myBank->withdraw(45, 3);
	myBank->withdraw(99, 3);
	myBank->withdraw(50, 3);
	myBank->print();

	return 0;
}