#pragma once

#include <iostream>
#include <string>
#include "Money.h"

class Bank{
protected:
	double balance;		// Total amount of money
	Money bank[12];		// An array that stores the data for each dollar/coin type
						// Array is ordered from highest priority to least

public:
	// Create an empty bank
	Bank() {
		balance = 0;
	}

	// Constructor given a bank value (not used as of now)
	Bank(double b) {
		balance = b;
	}

	// Fills out the bank array
	// This is with default priorities, can be overwritten if the user chooses custom priorities
	// Money(const char* n, const char t, const double v, int p, int q)
	// n = name, t = type, v = value, p = priority, q = quantity
	virtual void buildMoney() {
		// Dollars
		bank[0] = Money("$100 Dollar Bill", 'd', 100, 11, 0);		// $100
		bank[1] = Money("$50 Dollar Bill", 'd', 50, 10, 0);			// $50
		bank[2] = Money("$20 Dollar Bill", 'd', 20, 9, 0);			// $20
		bank[3] = Money("$10 Dollar Bill", 'd', 10, 8, 0);			// $10
		bank[4] = Money("$5 Dollar Bill", 'd', 5, 7, 0);			// $5
		bank[5] = Money("$2 Dollar Bill", 'd', 2, 6, 0);			// $2
		bank[6] = Money("$1 Dollar Bill", 'd', 1, 5, 0);			// $1

		// Coins
		bank[7] = Money("Half Dollar", 'c', 0.50, 4, 0);		// Half dollar
		bank[8] = Money("Quarter", 'c', 0.25, 3, 0);			// Quarter
		bank[9] = Money("Dime", 'c', 0.10, 2, 0);				// Dime
		bank[10] = Money("Nickel", 'c', 0.05, 1, 0);			// Nickel
		bank[11] = Money("Penny", 'c', 0.01, 0, 0);				// Penny
	}

	// This automatically sorts the bank whenever it is being filled
	// bank should be ordered with the highest priority at index 0 and lowest at 11
	void sortBank() {
		// insertion sort or something simple, empty for now since it's already sorted
	}

	// Fills the bank with money based on the balance
	// This is called whenever a change to balance occurs
	void fillBank() {
		sortBank();
		double tracker = 0;		// Keeps track of how many dollars/coins need to be added to the balance
		for (int i = 0; i < 12; i++) {
			// Repeatedly add a money type to balance until it can no longer fit, then move to the next
			while (bank[i].value <= balance - tracker) {
				tracker += bank[i].value;
				bank[i].quantity++;
				bank[i].updateTotal();
			}
		}
	}

	// Adds an amount to the balance
	void modifyBalance(double b) {
		balance += b;
		fillBank();
	}

	// Withdraw function


	// Prints all information of the bank
	void print() {
		std::cout << "Balance: $" << balance << std::endl;
		for (int i = 0; i < 12; i++) {
			// Do not print dollar/coin types that have 0
			if (bank[i].quantity > 0) {
				std::cout << bank[i].name << ": " << bank[i].quantity << " ($" << bank[i].total <<
				")" << std::endl;
			}
		}
	}
};