/*
  Copyright 2020 Peyton Somerville
*/

#ifndef _HOME_OSBOXES_DOCUMENTS_PS4B_STRINGSOUND_H_
#define _HOME_OSBOXES_DOCUMENTS_PS4B_STRINGSOUND_H_

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include "RingBuffer.h"

class StringSound{
public:
	// create a guitar string sound of the given frequency using a sampling rate of 44,100
	explicit StringSound(double frequency);

	// create a guitar string with size and initial values are given by the vector
	explicit StringSound(std::vector<sf::Int16> init);
				
	// pluck the guitar string by replacing the buffer with random values, representing white noise
	void pluck();

	// advance the simulation one time step
	void tic(); 

	// return the current sample
	sf::Int16 sample();

	// return number of times tic was called so far
	int time();

	friend ostream& operator<<(ostream& os, StringSound& ss);

private:
	RingBuffer* rb;
	int ticCounter;
};
#endif  // _HOME_OSBOXES_DOCUMENTS_PS4B_STRINGSOUND_H_#endif