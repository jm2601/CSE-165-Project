#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "Bank.h"

class DollarBank : public Bank {
public:
	// Create an empty bank with only dollar info
	Bank() {
		balance = 0;

		bank[0] = Money("$100 Dollar Bill", 100, 11, 0);		// $100
		bank[1] = Money("$50 Dollar Bill", 50, 10, 0);			// $50
		bank[2] = Money("$20 Dollar Bill", 20, 9, 0);			// $20
		bank[3] = Money("$10 Dollar Bill", 10, 8, 0);			// $10
		bank[4] = Money("$5 Dollar Bill", 5, 7, 0);				// $5
		bank[5] = Money("$2 Dollar Bill", 2, 6, 0);				// $2
		bank[6] = Money("$1 Dollar Bill", 1, 5, 0);				// $1
	}

	// Fills the bank with dollars based on the balance
	// This is called whenever a change to balance occurs
	void fillBank() {
		double tracker = 0;		// Keeps track of how many dollars need to be added to the balance
		for (int i = 0; i < 7; i++) {
			// Repeatedly add a dollar to balance until it can no longer fit, then move to the next type
			while (bank[i].value <= balance - tracker) {
				tracker += bank[i].value;
				bank[i].quantity++;
				bank[i].updateTotal();
			}
		}
	}

	// Deposit function
	// Adds an amount to the balance, but does not allow values less than 1
	void deposit(double b) {
		// Do not attempt to add the value if it is less than 1
		if (b < 1) {
			std::cout << "Invalid value. Input must be at least $1." << std::endl;
			return;
		}
		balance += b;
		fillBank();
	}

	// Withdraw function
	// Same as deposit except negative
	void withdraw(double b) {
		// Do not attempt to subtract the value if it is less than 1
		if (b < 1) {
			std::cout << "Invalid value. Input must be at least $1." << std::endl;
			return;
		}
		balance -= b;
		fillBank();
	}

	// This function allows the user to modify the priority of a selected dollar given its value
	void modifyPriority() {
		int input;		// This is what the priority will be changed to
		double v;		// This is the value of the dollar to be changed

		// This will go on forever until a correct input is detected
		while (0 == 0) {
			std::cout << "Enter the value of the dollar you want to modify the priority for: ";
			std::cin >> v;

			// This loop finds the value that v corresponds to
			for (int i = 0; i < 7; i++) {
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
	void print() {
		// Print the balance
		std::cout << "Balance: $" << balance << std::endl;
		for (int i = 0; i < 5; i++) {
			// Do not print dollar types that have quantity 0
			if (bank[i].quantity > 0) {
				std::cout << bank[i].name << ": " << bank[i].quantity << " ($" << bank[i].total <<
					")" << std::endl;
			}
		}
	}
};