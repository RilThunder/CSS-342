#include "complex.h"

/*
 * This method will construct an imaginary number
*/
complex::complex(double real , double imagine )
{
	realNumber = real;
	imagineNumber = imagine;
}

/*
 * This method is not implemented
*/
complex::~complex()
{
}

/*
 * Return the real coefficient x of the imaginary number
*/
double complex::getReal() const
{
	return realNumber;
}

/*
 * Return the imaginary coefficient y of the imaginary number
*/
double complex::getImaginary() const
{
	return imagineNumber;
}

/*
 * Operator overloading + for 2 imaginary number
*/
complex complex::operator+(const complex & c) const
{
	complex newVar(realNumber, imagineNumber);
	newVar.imagineNumber = newVar.imagineNumber + c.getImaginary();
	newVar.realNumber = newVar.realNumber + c.getReal();
	return newVar;
}

/*
 * Operator overloading - for 2 imaginary number
*/
complex complex::operator-(const complex & c) const
{
	complex newVar(realNumber, imagineNumber);
	newVar.imagineNumber = newVar.imagineNumber - c.getImaginary();
	newVar.realNumber = newVar.realNumber - c.getReal();
	return newVar;
}

/*
 * Operator overloading * for 2 imagniary number
*/
complex complex::operator*(const complex & c) const
{
	complex newVar(realNumber, imagineNumber);
	double newReal = realNumber * c.getReal() + imagineNumber * c.getImaginary() * -1;  // i^2 = -1
	double newImaginary = realNumber * c.getImaginary() + imagineNumber * c.getReal();
	newVar.realNumber = newReal;
	newVar.imagineNumber = newImaginary;
	return newVar;
}

/*
 * Operator overloading / for 2 imaginary number
*/
complex complex::operator/(const complex & c) const
{
	if (c.getImaginary() == 0.0 && c.getReal() == 0) 
	{
		cout << "Error. Dision by zero " << endl; 
		return *this; // Do not change and return the original object
	}
	complex conjugate = c.conjugate();
	complex newVar (realNumber, imagineNumber);
	complex a = c * conjugate; // multiply the denominator
	double x = a.getReal(); // when multiply a complex with its conjugate, all the imaginary parts will be gone 
	newVar = newVar * conjugate;   // get the new numerator
	return complex(newVar.realNumber / x, newVar.imagineNumber / x); 
}

/*
 * This method will return a conjugate of a complex number
*/
complex complex::conjugate() const
{
	return complex(realNumber, -imagineNumber);
}

/*
 * Compare if both complex number are equal to each other
*/
bool complex::operator==(const complex & c) const
{
	return c.realNumber == realNumber && c.imagineNumber == imagineNumber;
}

/*
 * Compare if both complex number are different
*/
bool complex::operator!=(const complex & c) const
{
	return !operator==(c); // inverse of ==
}

/*
 * Overloading the += operator and change the left hand value
*/
complex & complex::operator+=(const complex & c)
{
	complex x = *this;
	*this = x + c; //utilized the + operator which was already defined
	return *this;
}

/*
 * Overloading the -= operator and change the left hand value
*/
complex & complex::operator-=(const complex & c)
{
	complex x = *this;
	*this = x - c;
	return *this;
}

/*
* Overloading the *= operator and change the left hand value
*/
complex & complex::operator*=(const complex & c)
{
	complex x = *this;
	*this = x * c;
	return *this;
}

/*
* Overloading the /= operator and change the left hand value
* This also handle the division by zero error
*/
complex & complex::operator/=(const complex & c)
{
	complex x = *this;
	*this = x / c;
	return *this;
}

/*
* Overloading the output stream to display the complex number
* This will handle special cases like displaying i instead of 1i
*/
ostream & operator<<(ostream & output, const complex & c)
{
	if (c.getImaginary() == 0 && c.getReal() == 0) 
	{
		output << "0" << endl;  // Special case where both coefficient is 0
		return output;
	}
	if (c.getReal() == 0.0)
	{
		if (c.getImaginary() == 1)  // Special case where we only want to display i instead of 1i and there is no real coefficient 
		{
			output << "i" << endl;
			return output;
		}
		if (c.getImaginary() == -1) {
			output << "-i" << endl;
			return output;
		}
		output << c.getImaginary() << "i" << endl;
		return output;
	}
	if (c.getImaginary() == 0)
	{
		output << c.getReal() << endl; // If there is no imaginary part, only display the real number
		return output;
	}
	if (c.getImaginary() < 0)
	{
		output << c.getReal() ;
		if (c.getImaginary() == -1.0)
		{
			output << "-i" << endl; // Special case where we want to display the -i instead of -1i but with real coefficient
			return output;
		}
		output << c.getImaginary() << "i" << endl;
		return output;
	}
	else
	{
		output << c.getReal() << "+";  // The same special case i instead of 1i but with real coefficient
		if (c.getImaginary() == 1)
		{
			output << "i" << endl;
			return output;
		}
		output << c.getImaginary() << "i" << endl;
		return output;
	}
	return output;
}

/*
* Overloading the input stream to prompt the user to enter and change a complex number
*/
istream & operator >> (istream & input, complex & c)
{
	double realCoef, imagineCoef;
	input >> realCoef;
	input >> imagineCoef;
	c.realNumber = realCoef; // Set the complex data to the user's input
	c.imagineNumber = imagineCoef;
	return input;
}

