#ifndef FIBLFSR_HPP
#define FIBLFSR_HPP
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class FibLFSR
{
public:
	FibLFSR(string seed);

	int step(void);

	int generate(int k);

	friend ostream& operator<< (ostream &os, FibLFSR &lfsr);

private:
	string bits;
};

#endif