/*
	Peyton Somerville
	COMP. 4290
	2/7/21
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::max;
using std::vector;

int score(char c1, char c2);
int find_max(int n1, int n2, int n3);

int main()
{
	string s1 = "ATG";
	string s2 = "GGAAT";
	int g = -5;

	char c1, c2;
	int i, j;
	int s;

	vector<vector<int>> a;

	string str1 = '-' + s1;
	string str2 = '-' + s2;
	int x = str1.size(), y = str2.size();

	//set size of matrix based on strings
	a.resize(x);
	for (i = 0; i < x; i++) {
		a[i].resize(y);
	}

	//fill in first row and column based on gap penalty
	for (i = 1; i < x; i++) {
		a[i][0] = a[i - 1][0] + g;
	}
	for (j = 1; j < y; j++) {
		a[0][j] = a[0][j - 1] + g;
	}

	//fill in the rest with 0s
	for (i = 1; i < a.capacity(); i++) {
		for (j = 1; j < a[i].capacity(); j++) {
			a[i][j] = 0;
		}
	}


	//compute matrix values using described algorithm
	for (i = 1; i < x; i++) {
		c1 = str1.at(i);
		for (j = 1; j < y; j++) {
			c2 = str2.at(j);
			s = score(c1, c2);
			a[i][j] = find_max(a[i - 1][j - 1] + s, a[i - 1][j] + g, a[i][j - 1] + g);
		}
	}


	//display matrix
	cout << "\t";
	for (i = 0; i < str2.size(); i++) {
		cout << str2.at(i) << "\t";
	}
	cout << endl;

	for (i = 0; i < x; i++) {
		cout << str1.at(i) << "\t";
		for (j = 0; j < y; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "\n\n";
	}
	cout << endl;


	return 0;
}

int score(char c1, char c2)
{
	if (c1 == c2)
		return 20;
	else if (((c1 == 'T' && c2 == 'C') || (c1 == 'C' && c2 == 'T')) || ((c1 == 'A' && c2 == 'G') || (c1 == 'G' && c2 == 'A')))
		return 10;
	else
		return 5;
}

int find_max(int n1, int n2, int n3)
{
	return max(n1, max(n2, n3));
}
