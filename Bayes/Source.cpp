#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

bool A, B, C, D, E;
double aProb;
vector<double> bProb, cProb, dProb;
vector<vector<double>> eProb;

// returns a random number between 0 and 1
double rando() {
	return rand() / double(RAND_MAX);
}

// the five functions return the markov blanket of the respective node from checking their current states
// I use abs(!X - xProb[Y]) to get either X or !X depending on what it is currently
bool markovA() {
	double temp = rando();
	double bcd;
	bcd = aProb * abs(!B - bProb[1]) * cProb[1] * abs(!D - dProb[1]) + (1 - aProb) * abs(!B - bProb[0]) * cProb[0] * abs(!D - dProb[0]);
	return temp < aProb * abs(!B - bProb[1]) * cProb[1] * abs(!D - dProb[1]) / bcd;
}

bool markovB() {
	double temp = rando();
	return temp < bProb[A];
}

// C is always true since it is given
bool markovC() {
	return true;
}

bool markovD() {
	double temp = rando();
	double aced, dee, ace;

	dee = (dProb[1] * aProb + dProb[0] * (1 - aProb));

	aced = dProb[A] * abs(!A - aProb) / dee * cProb[A] * abs(!E - eProb[C][1]);

	ace = abs(!A - aProb) * cProb[A] * (abs(!E - eProb[C][1]) * dProb[A] + abs(!E - eProb[C][0]) * (1 - dProb[A]));

	return temp < (aced * dee / ace);
}

bool markovE() {
	double temp = rando();
	return temp < eProb[C][D];
}

int main() {
	// sets a random seed for the rng
	srand(time(NULL));

	// the given probabilities
	aProb = 0.6;
	bProb = { 0.1, 0.7 };
	cProb = { 0.2, 0.6 };
	dProb = { 0.8, 0.2 };
	eProb = { {0.3, 0.7}, {0.9, 0.1} };

	// sets the original states
	A = rando() < aProb;
	B = rando() < bProb[A];
	D = rando() < dProb[A];
	C = true;
	E = rando() < eProb[C][D];

	int total = 0;
	int iterations = 10000;
	for (int i = 1; i <= iterations; i++) {
		A = markovA();
		B = markovB();
		D = markovD();
		E = markovE();
		total += B;
		if (i % 1000 == 0) // prints out every 1000
			cout << total * 1.0 / i << endl;
	}
	system("PAUSE");
	return 0;
}