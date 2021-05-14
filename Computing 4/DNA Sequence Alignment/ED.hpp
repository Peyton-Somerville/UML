/*
  Copyright 2020 Peyton Somerville
*/

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class ED {
public:

	ED(string s1, string s2);  // Constructor

	// Returns penalty for aligning chars a and b (will be 0 or 1)
	static int penalty(char a, char b);

	// Returns the minimum of the three agruments
	static int minimum(int a, int b, int c);

	int OptDistance();

	string Alignment();

	void printMatrix();

private:
	string str1;
	string str2;
	int rowSize;
	int colSize;

	vector<vector<int>> opt;
};