/*
  Copyright 2020 Peyton Somerville
*/

#include <algorithm>
#include "ED.hpp";

ED::ED(string s1, string s2) {
	str1 = s1 + '-';
	str2 = s2 + '-';
	
	rowSize = str1.size();
	colSize = str2.size();
	opt.resize(rowSize);

	int i;
	for (i = 0; i < rowSize; i++) {
		opt[i].resize(colSize);
	}

	int x, y;
	for (x = 0; x < opt.capacity(); x++) {
		for (y = 0; y < opt[x].capacity(); y++) {
			opt[x][y] = 0;	// fill whole matrix with 0s
		}
	}
}

int ED::penalty(char a, char b) {
	if (a == b)
		return 0;
	else
		return 1;
}

int ED::minimum(int a, int b, int c) {
	return std::min({ a, b, c });
}

int ED::OptDistance() {
	int x, y;
	
	int counter = 2;
	for (x = rowSize - 2; x >= 0; x--) {
		opt[x][colSize - 1] = counter;  // fill right column
		counter += 2;
	}
	counter = 2;
	for (y = colSize - 2; y >= 0; y--) {
		opt[rowSize - 1][y] = counter;  // fill bottom row
		counter += 2;
	}

	int num1, num2, num3;
	for (x = opt.size() - 2; x >= 0 ; x--) {
		for (y = opt[x].size() - 2; y >= 0; y--) {
			num1 = opt[x + 1][y + 1] + penalty(str1.at(x), str2.at(y));
			num2 = opt[x + 1][y] + 2;
			num3 = opt[x][y + 1] + 2;

			opt[x][y] = minimum(num1, num2, num3);
		}
	}

	return opt[0][0];
}

string ED::Alignment() {
	string output = "\0";
	int i = 0;
	int j = 0;
	while (i < rowSize - 1 || j < colSize - 1) {
		if (i == rowSize - 1)
			i--;
		if (j == colSize - 1)
			j--;
		if (opt[i][j] == opt[i + 1][j + 1] && str1.at(i) == str2.at(j)) {
			output += str1.at(i) + string("  ") + str2.at(j) + string("  0");
			i++;
			j++;
		}
		else if (opt[i][j] == opt[i + 1][j + 1] + 1) {
			output += str1.at(i) + string("  ") + str2.at(j) + string("  1");
			i++;
			j++;
		}
		else if (opt[i][j] == opt[i + 1][j] + 2) {
			output += str1.at(i) + string("  -  2");
			i++;
		}
		else if (opt[i][j] == opt[i][j + 1] + 2) {
			output += string("-  ") + str2.at(j) + string("  2");
			j++;
		}
		output += "\n";
	}

	return output;
}

void ED::printMatrix() {
	std::cout << "\t";
	int w, x, y;
	for (w = 0; w < str2.size(); w++) {
		std::cout << str2.at(w) << "\t";
	}
	std::cout << "\n";

	for (x = 0; x < opt.size(); x++) {
		std::cout << str1.at(x) << "\t";
		for (y = 0; y < opt[x].size(); y++) {
			std::cout << opt[x][y] << "\t";
		}
		std::cout << "\n\n";
	}
	std::cout << "\n";
}