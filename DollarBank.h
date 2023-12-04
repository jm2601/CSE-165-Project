#pragma once

#include <cmath>
#include "Bank.h"

// The support functions need to be redefined to support size
// The called functions have slightly different comments and output messages
class DollarBank : public Bank {
	Money bank[7];									// An array that stores the data for each dollar type
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

	~DollarBank() {

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
	virtual void deposit(double b, std::string& s) {
		// Use a buffer to convert to string
		char buffer[1024];
		s = "";
		// Do not deposit if the input is 0
		if (b == 0) {
			snprintf(buffer, sizeof(buffer), "Nothing to deposit.\n");
			s.append(buffer);
			return;
		}
		// Do not deposit if the input is too small
		if (b < 1) {
			snprintf(buffer, sizeof(buffer), "$%f is an invalid value.\n", b);
			s.append(buffer);
			return;
		}
		balance += b;
		snprintf(buffer, sizeof(buffer), "Deposited $%0.2f to the bank.\n", b);
		s.append(buffer);
		fillBank(b);
	}

	// The second deposit function
	// Syntax: deposit(value of dollar type, quantity to deposit)
	virtual void deposit(double v, int q, std::string& s) {
		// Use a buffer to convert to string
		char buffer[1024];
		s = "";
		double b = v * q;
		// Do not deposit if the input is 0
		if (v == 0 || q == 0) {
			snprintf(buffer, sizeof(buffer), "Nothing to deposit.\n");
			s.append(buffer);
			return;
		}
		// Do not deposit if the quantity is invalid
		if (q <= 0) {
			snprintf(buffer, sizeof(buffer), "$%d is an invalid quantity.\n", q);
			s.append(buffer);
			return;
		}
		// Verify that the v input is a valid value
		for (int i = 0; i < size; i++) {
			if (v == bank[i].value) {
				balance += b;
				snprintf(buffer, sizeof(buffer), "Deposited $%0.2f x %d to the bank.\n", v, q);
				s.append(buffer);
				// Repeat fillBank as many times as the quantity
				for (int i = 0; i < q; i++) {
					fillBank(v);
				}
				return;
			}
		}
		// If the value is not valid
		snprintf(buffer, sizeof(buffer), "$%f is an invalid dollar value.\n", v);
		s.append(buffer);
	}

	// Withdraw function
	// Nearly the same as deposit except negative
	virtual void withdraw(double b, std::string& s) {
		// Use a buffer to convert to string
		char buffer[1024];
		s = "";
		// Do not withdraw if the input is 0
		if (b == 0) {
			snprintf(buffer, sizeof(buffer), "Nothing to withdraw.\n");
			s.append(buffer);
			return;
		}
		// Do not withdraw if the input is too small
		if (b < 1) {
			snprintf(buffer, sizeof(buffer), "$%f is an invalid value.\n", b);
			s.append(buffer);
			return;
		}
		// Do not withdraw if the input exceeds balance
		if (b > balance) {
			snprintf(buffer, sizeof(buffer), "$%0.2f exceeds the current balance of $%0.2f.\n", b, balance);
			s.append(buffer);
			return;
		}
		balance -= b;
		snprintf(buffer, sizeof(buffer), "Withdrew $%0.2f from the bank.\n", b);
		s.append(buffer);
		emptyBank(b);
	}

	// Second withdraw function
	// Nearly the same as second deposit except negative
	virtual void withdraw(double v, int q, std::string& s) {
		// Use a buffer to convert to string
		char buffer[1024];
		s = "";
		double b = v * q;
		// Do not deposit if the input is 0
		if (v == 0 || q == 0) {
			snprintf(buffer, sizeof(buffer), "Nothing to withdraw.\n");
			s.append(buffer);
			return;
		}
		// Do not withdraw if the quantity is invalid
		if (q < 0) {
			snprintf(buffer, sizeof(buffer), "$%d is an invalid quantity.\n", q);
			s.append(buffer);
			return;
		}
		// Do not withdraw if the input is too small
		if (v < 1) {
			snprintf(buffer, sizeof(buffer), "$%f is an invalid dollar value.\n", v);
			s.append(buffer);
			return;
		}
		// Do not withdraw if the input exceeds balance
		if (b > balance) {
			snprintf(buffer, sizeof(buffer), "$%0.2f exceeds the current balance of $%0.2f.\n", b, balance);
			s.append(buffer);
			return;
		}
		// Verify that the v input is a valid value
		for (int i = 0; i < size; i++) {
			if (v == bank[i].value) {
				balance -= b;
				snprintf(buffer, sizeof(buffer), "Withdrew $%0.2f x %d from the bank.\n", v, q);
				s.append(buffer);
				// Repeat emptyBank as many times as the quantity
				for (int i = 0; i < q; i++) {
					emptyBank(v);
				}
				return;
			}
		}
		// If the value is not valid
		snprintf(buffer, sizeof(buffer), "$%f is an invalid dollar value.\n", v);
		s.append(buffer);
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

	// Prints all information of the bank (string version for Qt)
	virtual void print(std::string& s) {
		// Use a buffer to convert to string
		char buffer[1024];
		s = "";
		for (int i = 0; i < size; i++) {
			// Do not print dollar types that have quantity 0
			if (bank[i].quantity > 0) {
				snprintf(buffer, sizeof(buffer), "%s: %d ($%0.2f)\n", bank[i].name, bank[i].quantity, bank[i].total);
				s.append(buffer);
			}
		}
		// Print the total balance
		snprintf(buffer, sizeof(buffer), "Total balance: $%0.2f\n", balance);
		s.append(buffer);
	}
};