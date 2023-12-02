#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "Bank.h"

class CoinBank : public Bank {
public:
	// Create an empty bank with only coin info
	Bank() {
		balance = 0;

		bank[0] = Money("Half Dollar", 0.50, 4, 0);			// Half dollar
		bank[1] = Money("Quarter", 0.25, 3, 0);				// Quarter
		bank[2] = Money("Dime", 0.10, 2, 0);				// Dime
		bank[3] = Money("Nickel", 0.05, 1, 0);				// Nickel
		bank[4] = Money("Penny", 0.01, 0, 0);				// Penny
	}

	// Fills the bank with coins based on the balance
	// This is called whenever a change to balance occurs
	void fillBank() {
		double tracker = 0;		// Keeps track of how many coins need to be added to the balance
		for (int i = 0; i < 5; i++) {
			// Repeatedly add a coin to balance until it can no longer fit, then move to the next type
			// round is used to prevent rounding errors
			while (bank[i].value <= (round((balance - tracker) * 100) / 100)) {
				tracker += bank[i].value;
				bank[i].quantity++;
				bank[i].updateTotal();
			}
		}
	}

	// This function allows the user to modify the priority of a selected coin given its value
	void modifyPriority() {
		int input;		// This is what the priority will be changed to
		double v;		// This is the value of the coin to be changed

		// This will go on forever until a correct input is detected
		while (0 == 0) {
			std::cout << "Enter the value of the coin you want to modify the priority for: ";
			std::cin >> v;

			// This loop finds the value that v corresponds to
			for (int i = 0; i < 5; i++) {
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
			// Do not print coin types that have quantity 0
			if (bank[i].quantity > 0) {
				std::cout << bank[i].name << ": " << bank[i].quantity << " ($" << bank[i].total <<
					")" << std::endl;
			}
		}
	}
};