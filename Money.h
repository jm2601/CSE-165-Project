#pragma once

#include <iostream>

class Money{
public:
	const char* name;	// The name of the dollar/coin
	char type;			// Should be either 'c' or 'd', representing coin or dollar
	double value;		// The money's worth
	int priority;		// Determines the priority when sorting
						// The higher the number, the higher priority
	int quantity;		// Stores how many of the dollar/coin there is in the bank
	double total;		// The worth of all dollars/coins of the same type

	Money() {

	}

	// Constructor given all variables mentioned above
	Money(const char* n, const char t, const double v, int p, int q) {
		name = n;
		type = t;
		value = v;
		priority = p;
		quantity = q;
		total = value * quantity;
	}

	// Updates the value of total
	void updateTotal() {
		total = value * quantity;
	}
};