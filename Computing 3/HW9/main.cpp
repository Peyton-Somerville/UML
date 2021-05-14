/*
	Author: Peyton Somerville
	Date: 12/8/19
	Assingment: HW9
	Lab Section: 801

	Code changed from HW7/HW8:
	- Rational overloaded << operator: Added parenthesis to make output of fractions easier to see
	- Complex overloaded << operator: Changed to output only in basic form  
	- Complex overloaded * operator: Slightly changed the calculation for the real number part
	- Complex overloaded / operator: Changed calculation to handle rational numbers. I was not able to figure out how to have it handle
		both complex numbers with rational parts and ones with integer parts. Currently only works with rational parts.
*/

#include <iostream>
#include <string>

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
	if (rat.den == 1)
		os << rat.num;
	else
		os << "(" << rat.num << "/" << rat.den << ")";
	return os;
}

template <class T>
class MyComplex : public Rational
{
public:
	/* Constructors */
	MyComplex();
	MyComplex(T realNum);
	MyComplex(T realNum, T imaginaryNum);

	/* Accessor functions */
	T getRealNum() const;
	T getImaginaryNum() const;

	/* Mutator functions */
	void setRealNum(T realNum);
	void setImaginaryNum(T imaginaryNum);

	friend ostream& operator << <> (ostream& os, const MyComplex& mc);
	template <class U>
	friend istream& operator >> (istream& is, MyComplex<U>& mc);

	MyComplex operator + (const MyComplex& mc);
	MyComplex operator + (double op);
	template <class U>
	friend MyComplex<U> operator + (double op, const MyComplex<U>& mc);

	MyComplex operator - (const MyComplex& mc);
	MyComplex operator - (double op);
	template <class U>
	friend MyComplex<U> operator - (double op, const MyComplex<U>& mc);

	MyComplex operator * (const MyComplex& mc);
	MyComplex operator * (double op);
	template <class U>
	friend MyComplex<U> operator * (double op, const MyComplex<U>& mc);

	MyComplex operator / (T op);
	MyComplex operator / (MyComplex& mc);

	MyComplex conjugate();

private:
	T realNum;
	T imaginaryNum;
};

template <class T>
MyComplex<T>::MyComplex()
{
	realNum = 0;
	imaginaryNum = 0;
}
template <class T>
MyComplex<T>::MyComplex(T realNum)
{
	this->realNum = realNum;
	imaginaryNum = 0;
}
template <class T>
MyComplex<T>::MyComplex(T realNum, T imaginaryNum)
{
	this->realNum = realNum;
	this->imaginaryNum = imaginaryNum;
}

template <class T>
T MyComplex<T>::getRealNum() const
{
	return realNum;
}
template <class T>
T MyComplex<T>::getImaginaryNum() const
{
	return imaginaryNum;
}

template <class T>
void MyComplex<T>::setRealNum(T realNum)
{
	this->realNum = realNum;
}
template <class T>
void MyComplex<T>::setImaginaryNum(T imaginaryNum)
{
	this->imaginaryNum = imaginaryNum;
}

template <class T>
ostream& operator << <> (ostream& os, const MyComplex<T>& mc)
{
	os << mc.realNum << "+" << mc.imaginaryNum << "i";

	return os;
}
template <class T>
istream& operator >> (istream& is, MyComplex<T>& mc)
{
	string strInput;
	double rNum = 0, iNum = 0;
	string::size_type sz = 0;
	int i;

	cout << "Please enter input>> ";
	getline(cin, strInput);

	for (i = 0; i < strInput.size(); ++i)
	{
		if (strInput.at(i) == ' ' || strInput.at(i) == 'i')
			strInput.erase(strInput.begin() + i);
	}
	if (strInput.size() != 0)
	{
		rNum = stod(strInput, &sz);

		if (sz < strInput.size() - 1)
			iNum = stod(strInput.substr(sz));
	}

	mc.realNum = rNum;
	mc.imaginaryNum = iNum;

	return is;
}

template <class T>
MyComplex<T> MyComplex<T>::operator + (const MyComplex<T>& mc)
{
	MyComplex<T> result;
	result.realNum = realNum + mc.realNum;
	result.imaginaryNum = imaginaryNum + mc.imaginaryNum;

	return result;
}
template <class T>
MyComplex<T> MyComplex<T>::operator + (double op)
{
	MyComplex<T> result;
	result.realNum = realNum + op;
	result.imaginaryNum = imaginaryNum;

	return result;
}
template <class T>
MyComplex<T> operator + (double op, const MyComplex<T>& mc)
{
	MyComplex<T> result;
	result.realNum = mc.realNum + op;
	result.imaginaryNum = mc.imaginaryNum;

	return result;
}

template <class T>
MyComplex<T> MyComplex<T>::operator - (const MyComplex<T>& mc)
{
	MyComplex<T> result;
	result.realNum = realNum - mc.realNum;
	result.imaginaryNum = imaginaryNum - mc.imaginaryNum;

	return result;
}
template <class T>
MyComplex<T> MyComplex<T>::operator - (double op)
{
	MyComplex<T> result;
	result.realNum = realNum - op;
	result.imaginaryNum = imaginaryNum;

	return result;
}
template <class T>
MyComplex<T> operator - (double op, const MyComplex<T>& mc)
{
	MyComplex<T> result;
	result.realNum = op - mc.realNum;
	result.imaginaryNum = mc.imaginaryNum;

	return result;
}

template <class T>
MyComplex<T> MyComplex<T>::operator * (const MyComplex<T>& mc)
{
	MyComplex<T> result;

	result.realNum = (realNum * mc.realNum) - (imaginaryNum * mc.imaginaryNum);
	result.imaginaryNum = (realNum * mc.imaginaryNum) + (imaginaryNum * mc.realNum);

	return result;
}
template <class T>
MyComplex<T> MyComplex<T>::operator * (double op)
{
	MyComplex<T> result;
	result.realNum = realNum * op;
	result.imaginaryNum = imaginaryNum * op;

	return result;
}
template <class T>
MyComplex<T> operator * (double op, const MyComplex<T>& mc)
{
	MyComplex<T> result;
	result.realNum = mc.realNum * op;
	result.imaginaryNum = mc.imaginaryNum * op;

	return result;
}

template <class T>
MyComplex<T> MyComplex<T>::operator / (T op)
{
	MyComplex<T> result;
	result.realNum = realNum / op;
	result.imaginaryNum = imaginaryNum / op;

	return result;
}
template <class T>
MyComplex<T> MyComplex<T>::operator / (MyComplex<T>& mc)
{
	MyComplex<T> result;
	Rational div(1, 1);

	div = (mc.realNum * mc.realNum) + (mc.imaginaryNum * mc.imaginaryNum);

	result.realNum = ((realNum * mc.realNum) + (imaginaryNum * mc.imaginaryNum)) / div;
	result.imaginaryNum = ((imaginaryNum * mc.realNum) - (realNum * mc.imaginaryNum)) / div;

	return result;
}

template <class T>
MyComplex<T> MyComplex<T>::conjugate()
{
	MyComplex<T> newNum;
	newNum.realNum = realNum;
	newNum.imaginaryNum = -imaginaryNum;

	return newNum;
}

int main(int argc, char* argv[])
{
	Rational rTest1(1, 2);
	Rational rTest2(1, 3);
	Rational rTest3(1, 4);
	Rational rTest4(1, 5);
	Rational rTest5(3, -7);
	Rational rTest6(-5, 9);

	MyComplex<Rational> test;
	MyComplex<Rational> test0(rTest1);
	MyComplex<Rational> test1(rTest1, rTest2);
	MyComplex<Rational> test2(rTest3, rTest4);
	MyComplex<Rational> test3(rTest5, rTest6);
	MyComplex<int> intTest1(2, 3);
	MyComplex<int> intTest2(4, 5);

	cout << "Using default constructor: " << test << endl;
	cout << "Using one value constructor: " << test0 << endl;
	cout << "Using two value constructor: " << test1 << endl << endl;

	cout << test1 << " + " << test2 << " = " << test1 + test2 << endl;
	cout << test1 << " + " << test3 << " = " << test1 + test3 << endl;
	cout << test2 << " + " << test3 << " = " << test2 + test3 << endl;
	cout << test1 << " + 3.0 = " << test1 + 3.0 << endl;
	cout << test3 << " + 3.0 = " << test3 + 3.0 << endl;
	cout << intTest1 << " + " << intTest2 << " = " << intTest1 + intTest2 << endl;
	cout << endl;
	cout << test1 << " - " << test2 << " = " << test1 - test2 << endl;
	cout << test1 << " - " << test3 << " = " << test1 - test3 << endl;
	cout << test2 << " - " << test3 << " = " << test2 - test3 << endl;
	cout << test1 << " - 3.0 = " << test1 - 3.0 << endl;
	cout << test3 << " - 3.0 = " << test3 - 3.0 << endl;
	cout << intTest1 << " - " << intTest2 << " = " << intTest1 - intTest2 << endl;
	cout << endl;
	cout << test1 << " * " << test2 << " = " << test1 * test2 << endl;
	cout << test1 << " * " << test3 << " = " << test1 * test3 << endl;
	cout << test2 << " * " << test3 << " = " << test2 * test3 << endl;
	cout << test1 << " * 3.0 = " << test1 * 3.0 << endl;
	cout << test3 << " * 3.0 = " << test3 * 3.0 << endl;
	cout << intTest1 << " * " << intTest2 << " = " << intTest1 * intTest2 << endl;
	cout << endl;
	cout << test1 << " / " << test2 << " = " << test1 / test2 << endl;
	cout << test1 << " / " << test3 << " = " << test1 / test3 << endl;
	cout << test2 << " / " << test3 << " = " << test2 / test3 << endl;
	cout << test1 << " / 3.0 = " << test1 / 3.0 << endl;
	cout << test3 << " / 3.0 = " << test3 / 3.0 << endl;
	//cout << intTest1 << " / " << intTest2 << " = " << intTest1 / intTest2 << endl;		//cant get this to work...

	return 0;
}
