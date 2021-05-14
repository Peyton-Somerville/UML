/*
	Author: Peyton Somerville
	Date: 12/4/19
	Assingment: HW8
	Lab Section: 801
*/

#include <iostream>

using namespace std;

class Rational
{
public:
	Rational();
	Rational(long numerator);
	Rational(long numerator, long denominator);

	int gcd(long n, long d);

	Rational operator + (const  Rational& rat);
	Rational operator - (const  Rational& rat);
	Rational operator * (const  Rational& rat);
	Rational operator / (const  Rational& rat);

	friend ostream& operator << (ostream& os, const Rational& rat);

private:
	long num;
	long den;
};

Rational::Rational()
{
	num = 0;
	den = 1;
}
Rational::Rational(long numerator)
{
	num = numerator;
	den = 1;
}
Rational::Rational(long numerator, long denominator)
{
	int div;

	try
	{
		if (denominator == 0)
			throw denominator;
	}
	catch (long x)
	{
		cerr << "Exception caught: cannot have 0 as the denominator.\n";
	}

	num = numerator;
	den = denominator;

	div = gcd(num, den);
	num /= div;
	den /= div;
	
	if (den < 0)
	{
		num = -num;
		den = -den;
	}
}

int Rational::gcd(long n, long d)
{
	if (n == 0)
		return d;
	if (d == 0)
		return n;

	gcd(d, n % d);
}

Rational Rational::operator + (const  Rational& rat)
{
	Rational result;
	int div;

	long newnum1 = num * rat.den;		//setting common denominator
	long newden = den * rat.den;
	long newnum2 = rat.num * den;

	result.num = newnum1 + newnum2;
	result.den = newden;

	div = gcd(result.num, result.den);
	result.num /= div;
	result.den /= div;

	if (result.den < 0)
	{
		result.num = -result.num;
		result.den = -result.den;
	}
	return result;
}
Rational Rational::operator - (const  Rational& rat)
{
	Rational result;
	int div;

	long newnum1 = num * rat.den;		//setting common denominator
	long newden = den * rat.den;
	long newnum2 = rat.num * den;

	result.num = newnum1 - newnum2;
	result.den = newden;

	div = gcd(result.num, result.den);
	result.num /= div;
	result.den /= div;

	if (result.den < 0)
	{
		result.num = -result.num;
		result.den = -result.den;
	}
	return result;
}
Rational Rational::operator * (const  Rational& rat)
{
	Rational result;
	int div;

	result.num = num * rat.num;
	result.den = den * rat.den;

	div = gcd(result.num, result.den);
	result.num /= div;
	result.den /= div;

	if (result.den < 0)
	{
		result.num = -result.num;
		result.den = -result.den;
	}
	return result;
}
Rational Rational::operator / (const  Rational& rat)
{
	Rational result;
	int div;

	long newnum = rat.den;		//flipping second fraction
	long newden = rat.num;

	result.num = num * newnum;
	result.den = den * newden;

	div = gcd(result.num, result.den);
	result.num /= div;
	result.den /= div;

	if (result.den < 0)
	{
		result.num = -result.num;
		result.den = -result.den;
	}
	return result;
}

ostream& operator << (ostream& os, const Rational& rat)
{
	if(rat.den == 1)
		os << rat.num;
	else
		os << rat.num << "/" << rat.den;
	return os;
}

int main(int argc, char* argv[])
{
	Rational test1;
	Rational test2(1);
	Rational test3(1, 2);
	Rational test4(5, 30);
	Rational test5(15, -95);
	Rational test6(-12, -66);

	cout << "Test1 -> Using default constructor: " << test1 << endl;
	cout << "Test2 -> Using one value constructor (1): " << test2 << endl;
	cout << "Test3 -> Using two value constructor (1, 2): " << test3 << endl;

	cout << "Test4 -> Using values (5, 30): " << test4 << endl;
	cout << "Test5 -> Using values (15, -95): " << test5 << endl;
	cout << "Test6 -> Using values (-12, -66): " << test6 << endl;

	cout << "\nTest3 + Test4 = " << test3 + test4 << endl;
	cout << "Test4 + Test5 = " << test4 + test5 << endl;
	cout << "Test5 + Test6 = " << test5 + test6 << endl;

	cout << "\nTest3 - Test4 = " << test3 - test4 << endl;
	cout << "Test4 - Test5 = " << test4 - test5 << endl;
	cout << "Test5 - Test6 = " << test5 - test6 << endl;

	cout << "\nTest3 * Test4 = " << test3 * test4 << endl;
	cout << "Test4 * Test5 = " << test4 * test5 << endl;
	cout << "Test5 * Test6 = " << test5 * test6 << endl;

	cout << "\nTest3 / Test4 = " << test3 / test4 << endl;
	cout << "Test4 / Test5 = " << test4 / test5 << endl;
	cout << "Test5 / Test6 = " << test5 / test6 << endl;

	cout << "\nTest7 -> Using values (1, 0): ";
	Rational test7(1, 0);

	cout << "\nGCD of Test4: " << test4.gcd(5, 30) << endl;
	cout << "GCD of Test5: " << test5.gcd(15, -95) << endl;
	cout << "GCD of Test6: " << test6.gcd(-12, -66) << endl;

	return 0;
}
