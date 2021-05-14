/*
  Copyright 2020 Peyton Somerville
*/

#include <math.h>
#include <random>
#include "StringSound.h"

#define SAMPLES_PER_SECOND 44100

// create a guitar string sound of the given frequency using a sampling rate of 44,100
StringSound::StringSound(double frequency){
	if (frequency < 1)
		throw std::invalid_argument("StringSound constructor: frequency "
			"must be greater than zero.");

	int ringBufferCap = ceil(SAMPLES_PER_SECOND / frequency);

	rb = new RingBuffer(ringBufferCap);

	ticCounter = 0;
}

// create a guitar string with size and initial values are given by the vector
StringSound::StringSound(std::vector<sf::Int16> init){
	if (init.size() < 1)
		throw std::invalid_argument("StringSound constructor: init.size() "
			"must be greater than zero.");

	rb = new RingBuffer(init.size());

	int i;
	for (i = 0; i < init.size(); i++) {
		rb->enqueue(init.at(i));
	}

	ticCounter = 0;
}

// pluck the guitar string by replacing the buffer with random values, representing white noise
void StringSound::pluck(){
	int i;
	int size = rb->size();
	if (rb->isEmpty() == false) {  // clear buffer if not empty
		for (i = 0; i < size; i++) {
			if (rb->isEmpty() == true)
				break;
			rb->dequeue();
		}
	}

	int j;

	// Seed with a real random value, if available
	std::random_device r;

	for (j = 0; j < rb->getCapacity(); j++) {
		// Choose a random mean between -32768 and 32767
		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(-32768, 32767);
		int randNum = uniform_dist(e1);

		rb->enqueue(randNum);
	}
}

// advance the simulation one time step
void StringSound::tic(){
	if (rb->isEmpty())
		throw std::runtime_error("tic: can't tic with an empty ring buffer.");

	int16_t num1 = rb->dequeue();
	int16_t num2 = rb->peek();
	int16_t newNum = 0.996 * ((num1 + num2) / 2.0);

	rb->enqueue(newNum);

	ticCounter++;
}

// return the current sample
sf::Int16 StringSound::sample(){
	if (rb->isEmpty())
		throw std::runtime_error("sample: can't return a sample from an empty ring buffer.");
	return (sf::Int16)rb->peek();
}

// return number of times tic was called so far
int StringSound::time(){
	return ticCounter;
}

ostream& operator<<(ostream& os, StringSound& ss)
{
	os << *(ss.rb);

	return os;
}