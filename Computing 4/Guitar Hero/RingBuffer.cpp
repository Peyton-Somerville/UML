/*
  Copyright 2020 Peyton Somerville
*/

#include <bits/stdc++.h>
#include "RingBuffer.h"
// Google wants it this way:
// #include "/home/osboxes/Documents/ps4b/RingBuffer.h"
// But then it would not work on every machine.

RingBuffer::RingBuffer(int capacity) {
	if (capacity < 1)
		throw std::invalid_argument("RingBuffer constructor: capacity "
			"must be greater than zero.");

	buffer.reserve(capacity);
}

int RingBuffer::getCapacity()
{
	return buffer.capacity();
}

int RingBuffer::size() {
	return buffer.size();
}

bool RingBuffer::isEmpty() {
	if (buffer.empty() == true)
		return true;
	return false;
}
bool RingBuffer::isFull() {
	if (buffer.size() == buffer.capacity())
		return true;
	return false;
}

void RingBuffer::enqueue(int16_t x) {
	if (isFull())
		throw std::runtime_error("enqueue: can't enqueue to a full ring buffer.");

	buffer.push_back(x);
}
int16_t RingBuffer::dequeue() {
	if (isEmpty())
		throw std::runtime_error("dequeue: can't dequeue from"
			"an empty ring buffer.");

	int16_t item;
	item = buffer.at(0);
	buffer.erase(buffer.begin());

	return item;
}

int16_t RingBuffer::peek() {
	if (isEmpty())
		throw std::runtime_error("peek: can't peek into an empty ring buffer.");

	return buffer.front();
}

int16_t RingBuffer::peekAt(int location) {
	if (isEmpty())
		throw std::runtime_error("peekAt: can't peek into an empty ring buffer.");

	return buffer.at(location);
}

ostream& operator<<(ostream& os, RingBuffer& rb) {
	if (rb.isEmpty())
		throw std::runtime_error("operator<<: can't print an empty ring buffer.");

	int i;
	for (i = 0; i < rb.size(); i++) {
		os << rb.peekAt(i) << "\n";
	}

	return os;
}

void RingBuffer::printBuffer() {
	if (isEmpty())
		throw std::runtime_error("operator<<: can't print an empty ring buffer.");

	// lambda expression to print vector
	std::for_each(buffer.begin(), buffer.end(), [](int i) {
		std::cout << i << "  ";
	});

	std::cout << "\n";
}