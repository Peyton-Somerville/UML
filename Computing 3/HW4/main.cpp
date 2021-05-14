/*
	Author: Peyton Somerville
	Date: 10/22/19
	Assingment: HW4
	Lab Section: 801
*/

#include <iostream>

using namespace std;

class MyComplex
{
public:
	/* Constructors */
	MyComplex();
	MyComplex(double realNum);
	MyComplex(double realNum, double imaginaryNum);

	/* Accessor functions */
	double getRealNum() const;
	double getImaginaryNum() const;

	/* Mutator functions */
	void setRealNum(double realNum);
	void setImaginaryNum(double imaginaryNum);

	friend ostream& operator << (ostream& os, const MyComplex& mc);

private:
	double realNum;
	double imaginaryNum;
};

MyComplex::MyComplex()
{
	realNum = 0;
	imaginaryNum = 0;
}

MyComplex::MyComplex(double realNum)
{
	this->realNum = realNum;
	imaginaryNum = 0;
}

MyComplex::MyComplex(double realNum, double imaginaryNum)
{
	this->realNum = realNum;
	this->imaginaryNum = imaginaryNum;
}

double MyComplex::getRealNum() const
{
	return realNum;
}
double MyComplex::getImaginaryNum() const
{
	return imaginaryNum;
}

void MyComplex::setRealNum(double realNum)
{
	this->realNum = realNum;
}
void MyComplex::setImaginaryNum(double imaginaryNum)
{
	this->imaginaryNum = imaginaryNum;
}

ostream& operator << (ostream& os, const MyComplex& mc)
{
	if(mc.imaginaryNum < 0)
		os << mc.realNum << mc.imaginaryNum << "i";
	else
		os << mc.realNum << "+" << mc.imaginaryNum << "i";
	return os;
}

int main(int argc, char* argv[])
{
	MyComplex test1;
	MyComplex test2(1);
	MyComplex test3(1, 2);
	MyComplex test4;

	cout << "Using default constructor: " << test1 << endl;
	cout << "Using value constructor with one value (1): " << test2 << endl;
	cout << "Using value constructor with two values (1, 2): " << test3 << endl;

	test1.setRealNum(3);
	test1.setImaginaryNum(4);
	test2.setRealNum(-5);
	test2.setImaginaryNum(6);
	test3.setRealNum(0);
	test3.setImaginaryNum(-7);
	test4.setRealNum(8);
	test4.setImaginaryNum(0);

	cout << "\nTest1 -> After calling mutator functions setRealNum(3), setImaginaryNum(4): " << test1 << endl;
	cout << "Test2 -> After calling mutator functions setRealNum(-5), setImaginaryNum(6): " << test2 << endl;
	cout << "Test3 -> After calling mutator functions setRealNum(0), setImaginaryNum(-7): " << test3 << endl;
	cout << "Test4 -> After calling mutator functions setRealNum(8), setImaginaryNum(0): " << test4 << endl;

	cout << "\nAfter calling accessor function getRealNum for Test1: " << test1.getRealNum() << endl;
	cout << "After calling accessor function getImaginaryNum for Test1: " << test1.getImaginaryNum() << endl;
	cout << "\nAfter calling accessor function getRealNum for Test2: " << test2.getRealNum() << endl;
	cout << "After calling accessor function getImaginaryNum for Test2: " << test2.getImaginaryNum() << endl;
	cout << "\nAfter calling accessor function getRealNum for Test3: " << test3.getRealNum() << endl;
	cout << "After calling accessor function getImaginaryNum for Test3: " << test3.getImaginaryNum() << endl;
	cout << "\nAfter calling accessor function getRealNum for Test4: " << test4.getRealNum() << endl;
	cout << "After calling accessor function getImaginaryNum for Test4: " << test4.getImaginaryNum() << endl;

	return 0;
}
