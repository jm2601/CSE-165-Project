#pragma once

#include <cmath>
#include "Bank.h"

class DollarBank : public Bank {
	Money bank[7];									// An array that stores the data for each coin type
	int size = (sizeof(bank) / sizeof(Money));		// Used for array calculations

public:
	// Create an empty bank with only dollar info
	DollarBank() {
		balance = 0;

		bank[0] = Money("$100 Dollar Bill", 100, 0);		// $100
		bank[1] = Money("$50 Dollar Bill", 50, 0);			// $50
		bank[2] = Money("$20 Dollar Bill", 20, 0);			// $20
		bank[3] = Money("$10 Dollar Bill", 10, 0);			// $10
		bank[4] = Money("$5 Dollar Bill", 5, 0);			// $5
		bank[5] = Money("$2 Dollar Bill", 2, 0);			// $2
		bank[6] = Money("$1 Dollar Bill", 1, 0);			// $1
	}

	// Sets the quantity of everything to 0
	void empty() {
		for (int i = 0; i < size; i++) {
			bank[i].quantity = 0;
		}
	}

	// Fills the bank with dollars based on the input
	// This is called whenever deposit is
	void fillBank(double b) {
		double tracker = 0;		// Keeps track of how many dollars need to be added to the balance
		for (int i = 0; i < size; i++) {
			// Repeatedly add a dollar to balance until it can no longer fit, then move to the next type
			// round is used to prevent rounding errors
			while (bank[i].value <= (round((b - tracker) * 100) / 100)) {
				tracker += bank[i].value;
				bank[i].quantity++;
				bank[i].updateTotal();
			}
		}
	}

	// Empties the bank with dollars based on the input
	// This is called whenever withdraw is
	void emptyBank(double b) {
		double tracker = 0;		// Keeps track of how many dollars need to be removed from the balance
		for (int i = 0; i < size; i++) {
			// Repeatedly remove a dollar to balance until it can no longer fit, then move to the next type
			// round is used to prevent rounding errors
			while (bank[i].value <= (round((b - tracker) * 100) / 100)) {
				tracker += bank[i].value;
				bank[i].quantity--;
				bank[i].updateTotal();
			}
		}

		// Fix for negative quantities: empty the bank and refill it based on the positive balance
		for (int i = 0; i < size; i++) {
			if (bank[i].quantity < 0) {
				double temp = balance;
				empty();
				fillBank(temp);
			}
		}
	}


	// Below this point are the functions that should actually be called
	// Deposit function
	// Adds the input to the balance
	void deposit(double b) {
		// Do not deposit if the input is too small
		if (b < 1) {
			std::cout << "$" << b << " is an invalid dollar value." << std::endl;
			return;
		}
		balance += b;
		std::cout << "Deposited $" << b << " to the bank." << std::endl;
		fillBank(b);
	}

	// The second deposit function
	// Syntax: deposit(value of dollar type, quantity to deposit)
	void deposit(double v, int q) {
		// Do not deposit if the input is too small
		if (v < 1) {
			std::cout << "$" << v << " is an invalid dollar value." << std::endl;
			return;
		}
		// Verify that the v input is a valid value
		for (int i = 0; i < size; i++) {
			if (v == bank[i].value) {
				double b = v * q;
				balance += b;
				std::cout << "Deposited $" << v << " x " << q << " to the bank." << std::endl;
				// Repeat fillBank as many times as the quantity
				for (int i = 0; i < q; i++) {
					fillBank(v);
				}
				return;
			}
		}
		// If the value is not valid
		std::cout << "$" << v << " is an invalid dollar value." << std::endl;
	}

	// Withdraw function
	// Nearly the same as deposit except negative
	void withdraw(double b) {
		// Do not withdraw if the input exceeds balance
		if (b > balance) {
			std::cout << "$" << b << " exceeds the current balance of $" << balance << "." << std::endl;
			return;
		}
		balance -= b;
		std::cout << "Withdrew $" << b << " from the bank." << std::endl;
		emptyBank(b);
	}

	// Second withdraw function
	// Nearly the same as second deposit except negative
	void withdraw(double v, int q) {
		double b = v * q;
		// Do not withdraw if the input exceeds balance
		if (b > balance) {
			std::cout << "$" << b << " exceeds the current balance of $" << balance << "." << std::endl;
			return;
		}
		// Verify that the v input is a valid value
		for (int i = 0; i < size; i++) {
			if (v == bank[i].value) {
				balance -= b;
				std::cout << "Withdrew $" << v << " x " << q << " from the bank." << std::endl;
				// Repeat emptyBank as many times as the quantity
				for (int i = 0; i < q; i++) {
					emptyBank(v);
				}
				return;
			}
		}
		// If the value is not valid
		std::cout << "$" << v << " is an invalid dollar value." << std::endl;
	}

	// Prints all information of the bank
	virtual void print() {
		std::cout << "\nBank contents:" << std::endl;
		for (int i = 0; i < size; i++) {
			// Do not print dollar types that have quantity 0
			if (bank[i].quantity > 0) {
				std::cout << bank[i].name << ": " << bank[i].quantity << " ($" << bank[i].total << ")" << std::endl;
			}
		}
		// Print the total balance
		std::cout << "Total balance: $" << balance << std::endl;
		std::cout << std::endl;
	}
};