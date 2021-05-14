/*
	Author: Peyton Somerville
	Date: 10/8/19
	Assignment: HW3
	Lab section: 801
*/

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

string triangle(int a, int b, int c);
string overloaded_triangle(double a, double b, double c);
void bubble_sort(int arr[], int size);
void d_bubble_sort(double arr[], int size);

int main(int argc, char* argv[])
{
	int sides[3];
	double dSides[3];
	string output;

	if (argc == 1)
	{
		cerr << "No command line arguments.\n";
		cerr << "Enter side 1 of the triangle >> ";
		cin >> sides[0];
		if (sides[0] <= 0)
		{
			cerr << "Invalid length.\n";
			exit(1);
		}

		cerr << "Enter side 2 of the triangle >> ";
		cin >> sides[1];
		if (sides[1] <= 0)
		{
			cerr << "Invalid length.\n";
			exit(1);
		}

		cerr << "Enter side 3 of the triangle >> ";
		cin >> sides[2];
		if (sides[2] <= 0)
		{
			cerr << "Invalid length.\n";
			exit(1);
		}

		if (sides[0] > sides[1] || sides[0] > sides[2] || sides[1] > sides[2])	//out of order
		{
			bubble_sort(sides, 3);
		}

		output = triangle(sides[0], sides[1], sides[2]);
	}
	else if (string(argv[1]) == "-i")
	{
		if (argc == 3 || argc == 4 || argc > 5)
		{
			cerr << "Invalid number of arguments.\n";
			exit(1);
		}
		else
		{
			sides[0] = stoi(argv[2]);
			sides[1] = stoi(argv[3]);
			sides[2] = stoi(argv[4]);
		}

		if (sides[0] > sides[1] || sides[0] > sides[2] || sides[1] > sides[2])	//out of order
		{
			bubble_sort(sides, 3);
		}

		output = triangle(sides[0], sides[1], sides[2]);
	}
	else if (string(argv[1]) == "-d")
	{
		if (argc == 3 || argc == 4 || argc > 5)
		{
			cerr << "Invalid number of arguments.\n";
			exit(1);
		}
		else
		{
			dSides[0] = atof(argv[2]);
			dSides[1] = atof(argv[3]);
			dSides[2] = atof(argv[4]);
		}

		if (dSides[0] > dSides[1] || dSides[0] > dSides[2] || dSides[1] > dSides[2])	//out of order
		{
			d_bubble_sort(dSides, 3);
		}

		output = overloaded_triangle(dSides[0], dSides[1], dSides[2]);
	}
	else
	{
		if (argc == 2 || argc == 3 || argc > 4)
		{
			cerr << "Invalid number of arguments.\n";
			exit(1);
		}
		else
		{
			sides[0] = stoi(argv[1]);
			sides[1] = stoi(argv[2]);
			sides[2] = stoi(argv[3]);
		}

		if (sides[0] > sides[1] || sides[0] > sides[2] || sides[1] > sides[2])	//out of order
		{
			bubble_sort(sides, 3);
		}

		output = triangle(sides[0], sides[1], sides[2]);
	}

	cout << output;

	return 0;
}

string triangle(int a, int b, int c)
{
	string result;
	if (a + b <= c)
	{
		result = to_string(a) + ' ' + to_string(b) + ' ' + to_string(c) + " Not a triangle\n";
	}
	else
	{
		if (a == b && a == c)
		{
			result = to_string(a) + ' ' + to_string(b) + ' ' + to_string(c) + " Equilateral triangle\n";
		}
		else if ((a == b) || (a == c) || (b == c))
		{
			result = to_string(a) + ' ' + to_string(b) + ' ' + to_string(c) + " Isosceles triangle\n";
		}
		else if (a != b && a != c)
		{
			if ((a * a) + (b * b) == (c * c))
			{
				result = to_string(a) + ' ' + to_string(b) + ' ' + to_string(c) + " Right Scalene triangle\n";
			}
			else
			{
				result = to_string(a) + ' ' + to_string(b) + ' ' + to_string(c) + " Scalene triangle\n";
			}
		}
	}

	return result;
}

string overloaded_triangle(double a, double b, double c)
{
	const double EPSILON = 0.001;
	string result;
	string aString, bString, cString;
	stringstream stream;

	stream << fixed << setprecision(5) << a;	//converts from double to string with 5 decimals
	aString = stream.str();
	stream.str(string());	//clears stringstream

	stream << fixed << setprecision(5) << b;
	bString = stream.str();
	stream.str(string());

	stream << fixed << setprecision(5) << c;
	cString = stream.str();
	stream.str(string());

	if (fabs((a + b) - c) < EPSILON || a + b < c)
	{
		result = aString + ' ' + bString + ' ' + cString + " Not a triangle\n";
	}
	else
	{
		if ((fabs(a - b) < EPSILON) && (fabs(a - c) < EPSILON))
		{
			result = aString + ' ' + bString + ' ' + cString + " Equilateral triangle\n";
		}
		else if ((fabs(a - b) < EPSILON) || (fabs(a - c) < EPSILON) || (fabs(b - c) < EPSILON))
		{
			result = aString + ' ' + bString + ' ' + cString + " Isosceles triangle\n";
		}
		else if ((fabs(a - b) >= EPSILON) && (fabs(a - c) >= EPSILON))
		{
			if (fabs(((a * a) + (b * b)) - (c * c)) < EPSILON)
			{
				result = aString + ' ' + bString + ' ' + cString + " Right Scalene triangle\n";
			}
			else
			{
				result = aString + ' ' + bString + ' ' + cString + " Scalene triangle\n";
			}
		}
	}

	return result;
}

void bubble_sort(int arr[], int size)
{
	int i, j;
	int temp;
	bool swapped;

	for (i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void d_bubble_sort(double arr[], int size)
{
	int i, j;
	double temp;
	bool swapped;

	for (i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}
