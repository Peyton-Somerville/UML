/*
  Copyright 2020 Peyton Somerville
*/

#ifndef _HOME_OSBOXES_DOCUMENTS_PS4B_RINGBUFFER_H_
#define _HOME_OSBOXES_DOCUMENTS_PS4B_RINGBUFFER_H_
#include <stdint.h>
#include <iostream>
#include <vector>

using std::ostream;

class RingBuffer {
public:
	// create an empty ring buffer, with given max capacity
	explicit RingBuffer(int capacity);

	int getCapacity();

	int size();  // return number of items currently in the buffer

	bool isEmpty();  // is the buffer empty (size equals zero)?
	bool isFull();  // is the buffer full (size equals capacity)?

	void enqueue(int16_t x);  // add item x to the end
	int16_t dequeue();  // delete and return item from the front

	int16_t peek();  // return (but do not delete) item from the front

	// return (but do not delete) item from the location
	int16_t peekAt(int location);

	friend ostream& operator<<(ostream& os, RingBuffer& rb);

	void printBuffer();

private:
	std::vector<int16_t> buffer;
};

#endif  // _HOME_OSBOXES_DOCUMENTS_PS4B_RINGBUFFER_H_#endif