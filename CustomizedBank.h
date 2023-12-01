#pragma once

#include <iostream>
#include <string>
#include "Bank.h"

class CustomizedBank : public Bank{
public:
	// Create an empty bank
	CustomizedBank() {
		balance = 0;
	}

	// Fills out the bank array
	// This is with custom priorities
	// Money(const char* n, const char t, const double v, int p, int q)
	// n = name, t = type, v = value, p = priority, q = quantity
	void buildMoney() {
		int input;			// This is the priority that the user will input
		char choice;		// This is the choice of what dollar/coin the user wants to modify
							// 'y' = yes, 'n' = leave default
							// Can possibly add support for "yes" or "no" options that are not case sensitive

		// Build the default values first and the modify them if the user chooses to
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

		// Note that for now, only 'y' and 'n' should work
		// Entering anything that starts with y or n will cause an infinite loop
		std::cout << "Enter \"y\" to modify the priority. Enter \"n\" to skip." << std::endl;

		// COMMENT OUT FROM HERE...
		/*for (int i = 0; i < 12; i++) {
			while (choice != 'y' && choice != 'n') {
				std::cout << "Would you like to modify the priority of " << bank[i].name <<
					"? Its default priority is " << bank[i].priority << "." << std::endl;
				std::cin >> choice;

				if (choice == 'y') {
					std::cout << "\nEnter a new priority for " << bank[i].name << ": ";
					std::cin >> input;
					bank[i].priority = input;
					std::cout << "Priority for " << bank[i].name << " has been set to " << input << ".\n" << std::endl;
				}
				else if (choice == 'n') {
					std::cout << "Priority for " << bank[i].name << " will remain at " << bank[i].priority << ".\n" << std::endl;
				}
				else {
					std::cout << "Please enter either \"y\", \"yes\", \"n\", or \"no\".\n" << std::endl;
				}
			}
			// Override the value of choice so that the loop will continue
			choice = 'a';
		}*/
		// ... TO HERE to make testing easier
	}

	// This function allows the user to modify the priority of a selected dollar/coin given its value
	void modifyMoney() {
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
					// This will end the function once a correct input has been entered
					return;
				}
			}
			// If the value entered is invalid, the loop will repeat
			std::cout << "Invalid value.\n" << std::endl;
		}
	}
};