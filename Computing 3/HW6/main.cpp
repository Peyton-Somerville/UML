/*
	Author: Peyton Somerville
	Date: 11/5/19
	Assingment: HW6
	Lab Section: 801
*/

#include <iostream>
#include <string>

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
	friend istream& operator >> (istream& is, MyComplex& mc);

	MyComplex operator + (const MyComplex& mc);
	MyComplex operator + (double op);
	friend MyComplex operator + (double op, const MyComplex& mc);

	MyComplex operator - (const MyComplex& mc);
	MyComplex operator - (double op);
	friend MyComplex operator - (double op, const MyComplex& mc);

	MyComplex operator * (const MyComplex& mc);
	MyComplex operator * (double op);
	friend MyComplex operator * (double op, const MyComplex& mc);

	MyComplex operator / (double op);
	MyComplex operator / (MyComplex& mc);

	MyComplex conjugate();

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
	if (mc.realNum != 0 && mc.imaginaryNum != 0)
	{
		if (mc.imaginaryNum < 0)
			os << mc.realNum << mc.imaginaryNum << "i";
		else
			os << mc.realNum << "+" << mc.imaginaryNum << "i";
	}
	else
	{
		if (mc.realNum == 0 && mc.imaginaryNum != 0)
			os << mc.imaginaryNum << "i";
		if ((mc.imaginaryNum == 0 && mc.realNum != 0) || (mc.realNum == 0 && mc.imaginaryNum == 0))
			os << mc.realNum;
	}

	return os;
}
istream& operator >> (istream& is, MyComplex& mc)
{
	string strInput;
	double rNum = 0, iNum = 0;
	string::size_type sz = 0;
	int i;
	
	cout << "Please enter input>> ";
	getline(cin, strInput);
	
	for (i = 0; i < strInput.size(); ++i)
	{
		if (strInput.at(i) == ' ' || strInput.at(i) == '+' || strInput.at(i) == 'i' || strInput.at(i) == '-')
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

MyComplex MyComplex::operator + (const MyComplex& mc)
{
	MyComplex result;
	result.realNum = realNum + mc.realNum;
	result.imaginaryNum = imaginaryNum + mc.imaginaryNum;

	return result;
}
MyComplex MyComplex::operator + (double op)
{
	MyComplex result;
	result.realNum = realNum + op;
	result.imaginaryNum = imaginaryNum;

	return result;
}
MyComplex operator + (double op, const MyComplex& mc)
{
	MyComplex result;
	result.realNum = mc.realNum + op;
	result.imaginaryNum = mc.imaginaryNum;

	return result;
}

MyComplex MyComplex::operator - (const MyComplex& mc)
{
	MyComplex result;
	result.realNum = realNum - mc.realNum;
	result.imaginaryNum = imaginaryNum - mc.imaginaryNum;

	return result;
}
MyComplex MyComplex::operator - (double op)
{
	MyComplex result;
	result.realNum = realNum - op;
	result.imaginaryNum = imaginaryNum;

	return result;
}
MyComplex operator - (double op, const MyComplex& mc)
{
	MyComplex result;
	result.realNum = op - mc.realNum;
	result.imaginaryNum = mc.imaginaryNum;

	return result;
}

MyComplex MyComplex::operator * (const MyComplex& mc)
{
	MyComplex result;
	result.realNum = (realNum * mc.realNum) + -1 * (imaginaryNum * mc.imaginaryNum);
	result.imaginaryNum = (realNum * mc.imaginaryNum) + (imaginaryNum * mc.realNum);

	return result;
}
MyComplex MyComplex::operator * (double op)
{
	MyComplex result;
	result.realNum = realNum * op;
	result.imaginaryNum = imaginaryNum * op;

	return result;
}
MyComplex operator * (double op, const MyComplex& mc)
{
	MyComplex result;
	result.realNum = mc.realNum * op;
	result.imaginaryNum = mc.imaginaryNum * op;

	return result;
}

MyComplex MyComplex::operator / (double op)
{
	MyComplex result;
	result.realNum = realNum / op;
	result.imaginaryNum = imaginaryNum / op;

	return result;
}
MyComplex MyComplex::operator / (MyComplex& mc)
{
	MyComplex conj = mc.conjugate();
	MyComplex num(realNum, imaginaryNum);
	MyComplex den(mc.realNum, mc.imaginaryNum);
	MyComplex result;
	double dden;

	num = num * conj;
	den = den * conj;
	dden = den.getRealNum();	//converting den from MyComplex to double
	result = num / dden;

	return result;
}

MyComplex MyComplex::conjugate()
{
	MyComplex newNum;
	newNum.realNum = realNum;
	newNum.imaginaryNum = -imaginaryNum;

	return newNum;
}

int main(int argc, char* argv[])
{
	MyComplex test1;
	MyComplex test2(1);
	MyComplex test3(1, 2);
	MyComplex test4;

	cout << "Using >> operator with object then outputing with << operator:\n";
	cout << "Using no input:\n";
	cin >> test1;
	cout << test1 << endl;

	/*cout << "Using default constructor: " << test1 << endl;
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

	cout << "\nTest1 + Test2 = " << test1 + test2 << endl;
	cout << "Test2 + Test3 = " << test2 + test3 << endl;
	cout << "Test3 + Test4 = " << test3 + test4 << endl;
	cout << "Test1 + 3.0 = " << test1 + 3.0 << endl;
	cout << "3.0 + Test1 = " << 3.0 + test1 << endl;
	cout << "-2.0 + Test2 = " << -2.0 + test2 << endl;

	cout << "\nTest1 - Test2 = " << test1 - test2 << endl;
	cout << "Test2 - Test3 = " << test2 - test3 << endl;
	cout << "Test3 - Test4 = " << test3 - test4 << endl;
	cout << "Test3 - 5.0 = " << test3 - 5.0 << endl;
	cout << "5.0 - Test2 = " << 5.0 - test2 << endl;

	cout << "\nTest1 * Test2 = " << test1 * test2 << endl;
	cout << "Test2 * Test3 = " << test2 * test3 << endl;
	cout << "Test3 * Test4 = " << test3 * test4 << endl;
	cout << "Test4 * 10.0 = " << test4 * 10.0 << endl;
	cout << "5.0 * Test1 = " << 5.0 * test1 << endl;

	cout << "\nTest1 / 2.0 = " << test1 / 2.0 << endl;
	cout << "Test2 / 3.0 = " << test2 / 3.0 << endl;
	cout << "Test1 / Test2 = " << test1 / test2 << endl;
	cout << "Test2 / Test1 = " << test2 / test1 << endl;

	cout << "\nAfter calling test1.conjugate(): " << test1.conjugate() << endl;
	cout << "After calling test2.conjugate(): " << test2.conjugate() << endl;
	cout << "After calling test3.conjugate(): " << test3.conjugate() << endl;*/

	return 0;
}
