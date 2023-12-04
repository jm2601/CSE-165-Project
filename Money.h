#pragma once

class Money{
public:
	const char* name;	// The name of the dollar/coin
	double value;		// The dollar/coin's individual value
	int quantity;		// Stores how many of the dollar/coin there is in the bank
	double total;		// The value of all dollars/coins of the same type

	Money() {

	}

	~Money() {

	}

	// Constructor given all variables mentioned above
	Money(const char* n, const double v, int q) {
		name = n;
		value = v;
		quantity = q;
		total = value * quantity;
	}

	// Updates the value of total
	void updateTotal() {
		total = value * quantity;
	}
};