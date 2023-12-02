#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "Money.h"

class Bank {
protected:
	double balance;		// Total amount of money
	Money bank[12];		// An array that stores the data for each dollar/coin type
	// Array is ordered from highest priority to least

public:
	// Create an empty bank with the dollar/coin info filled out
	Bank() {
		balance = 0;

		// Dollars
		bank[0] = Money("$100 Dollar Bill", 100, 11, 0);		// $100
		bank[1] = Money("$50 Dollar Bill", 50, 10, 0);			// $50
		bank[2] = Money("$20 Dollar Bill", 20, 9, 0);			// $20
		bank[3] = Money("$10 Dollar Bill", 10, 8, 0);			// $10
		bank[4] = Money("$5 Dollar Bill", 5, 7, 0);				// $5
		bank[5] = Money("$2 Dollar Bill", 2, 6, 0);				// $2
		bank[6] = Money("$1 Dollar Bill", 1, 5, 0);				// $1

		// Coins
		bank[7] = Money("Half Dollar", 0.50, 4, 0);			// Half dollar
		bank[8] = Money("Quarter", 0.25, 3, 0);				// Quarter
		bank[9] = Money("Dime", 0.10, 2, 0);				// Dime
		bank[10] = Money("Nickel", 0.05, 1, 0);				// Nickel
		bank[11] = Money("Penny", 0.01, 0, 0);				// Penny
	}

	// This sorts the bank and is called whenever a priority is modified
	// bank should be ordered with the highest priority at index 0 and lowest at 11
	void sortBank() {
		// insertion sort or something simple, empty for now since it's already sorted
	}

	// Fills the bank with dollars/coins based on the balance
	// This is called whenever a change to balance occurs
	virtual void fillBank() {
		double tracker = 0;		// Keeps track of how many dollars/coins need to be added to the balance
		for (int i = 0; i < 12; i++) {
			// Repeatedly add a dollar/coin to balance until it can no longer fit, then move to the next type
			// round is used to prevent rounding errors
			while (bank[i].value <= (round((balance - tracker) * 100) / 100)) {
				tracker += bank[i].value;
				bank[i].quantity++;
				bank[i].updateTotal();
			}
		}
	}

	// Deposit function
	// Adds an amount to the balance
	virtual void deposit(double b) {
		balance += b;
		fillBank();
	}

	// Withdraw function
	// Same as deposit except negative
	virtual void withdraw(double b) {
		balance -= b;
		fillBank();
	}

	// This function allows the user to modify the priority of a selected dollar/coin given its value
	virtual void modifyPriority() {
		int input;		// This is what the priority will be changed to
		double v;		// This is the value of the dollar/coin to be changed

		// This will go on forever until a correct input is detected
		while (0 == 0) {
			std::cout << "Enter the value of the dollar/coin you want to modify the priority for: ";
			std::cin >> v;

			// This loop finds the value that v corresponds to
			for (int i = 0; i < 12; i++) {
				if (v == bank[i].value) {
					std::cout << "Enter priority you want to set for " << bank[i].name << ": ";
					std::cin >> input;
					bank[i].priority = input;
					std::cout << "Priority of " << bank[i].name << " has been set to " << input << "." << std::endl;
					// Sort the priorities after the change has been made
					sortBank();
					// This will end the function once a correct input has been entered
					return;
				}
			}
			// If the value entered is invalid, the loop will repeat
			std::cout << "Invalid value.\n" << std::endl;
		}
	}

	// Prints all information of the bank
	virtual void print() {
		// Print the balance
		std::cout << "Balance: $" << balance << std::endl;
		for (int i = 0; i < 12; i++) {
			// Do not print dollar/coin types that have quantity 0
			if (bank[i].quantity > 0) {
				std::cout << bank[i].name << ": " << bank[i].quantity << " ($" << bank[i].total <<
					")" << std::endl;
			}
		}
	}
};