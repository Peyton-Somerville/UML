#include "FibLFSR.hpp"
#include <string>
#include <iostream>

using namespace std;

FibLFSR::FibLFSR(string seed)
{
	bits = seed;
}

int FibLFSR::step(void)
{
	int newBit;
	if (bits.size() != 16)
	{
		cout << "There needs to be 16 bits.\n";
		newBit = -1;
	}
	else
	{
		newBit = ((bits[0] ^ bits[2]) ^ bits[3]) ^ bits[5]; //XOR on bits
		char strNewBit;
		int i;

		if (newBit == 1)
			strNewBit = '1';
		else
			strNewBit = '0';

		for (i = 0; i < 16; i++)  //shift bits to the left
		{
			if (i == 15)
			{
				bits[i] = strNewBit;
			}
			else
			{
				bits[i] = bits[i + 1];
			}
		}
	}

	return newBit;
}

int FibLFSR::generate(int k)
{
	int result = 0, bit = 0;
	int i;

	for (i = 0; i < k; i++)
	{
		bit = step();
		result = (result * 2) + bit;
	}

	return result;
}

ostream& operator<< (ostream &os, FibLFSR &lfsr)
{
	os << lfsr.bits;
	return os;
}
