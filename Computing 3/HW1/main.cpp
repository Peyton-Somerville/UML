/*
	Author: Peyton Somerville
	Date: 9/8/19
	Assignment: HW1
	Lab section: 801
*/

#include <iostream>
#include <string>

using namespace std;

void triangle(int a, int b, int c);

int main(int argc, char* argv[])
{
	int a, b, c;
	int sides[3];
	int temp;
	int user_wishes_to_continue = 1;

	do
	{
		if (argc == 1)
		{
			cout << "No command line arguments.\n";
			cout << "Enter side 1 of the triangle >> ";
			cin >> sides[0];
			if (sides[0] <= 0)
			{
				cerr << "Invalid length.\n";
				exit(1);
			}

			cout << "Enter side 2 of the triangle >> ";
			cin >> sides[1];
			if (sides[1] <= 0)
			{
				cerr << "Invalid length.\n";
				exit(1);
			}

			cout << "Enter side 3 of the triangle >> ";
			cin >> sides[2];
			if (sides[2] <= 0)
			{
				cerr << "Invalid length.\n";
				exit(1);
			}
		}
		else if (argc == 2 || argc == 3 || argc > 4)
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

		if (sides[0] > sides[1] || sides[0] > sides[2] || sides[1] > sides[2])
		{
			for (int i = 0; i < 2; i++)		//bubble sort if numbers are out of order
			{
				for (int j = 0; j < 2 - i; j++)
				{
					if (sides[j] > sides[j + 1])
					{
						temp = sides[j];
						sides[j] = sides[j + 1];
						sides[j + 1] = temp;
					}
				}
			}
		}

		a = sides[0];
		b = sides[1];
		c = sides[2];

		triangle(a, b, c);

		cout << "\nSelect one of the following:\n";
		cout << "0: Exit the program\n";
		cout << "1: Test another triangle\n>> ";
		cin >> user_wishes_to_continue;
	} while (user_wishes_to_continue == 1);

	return 0;
}

void triangle(int a, int b, int c)
{
	if (a + b <= c)
	{
		cout << a << " " << b << " " << c << " Not a triangle\n";
	}
	else
	{
		if (a == b && a == c)
		{
			cout << a << " " << b << " " << c << " Equilateral triangle\n";
		}
		else if ((a == b) || (a == c) || (b == c))
		{
			cout << a << " " << b << " " << c << " Isosceles triangle\n";
		}
		else if (a != b && a != c)
		{
			if ((a * a) + (b * b) == (c * c))
			{
				cout << a << " " << b << " " << c << " Right Scalene triangle\n";
			}
			else
			{
				cout << a << " " << b << " " << c << " Scalene triangle\n";
			}
		}
	}

}
