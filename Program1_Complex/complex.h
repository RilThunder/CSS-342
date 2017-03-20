/*
 *	CSS 342 Programming 1
 *	complex.cpp
 *	Purpose: Represent a complex number in the form x + yi
 *	where x is a real number and y is the coefficient of imaginary number
 *	@author	Thuan Tran
 *	@version 2.0 October 14th, 2016
*/

#ifndef complex_H
#define complex_H
#include <iostream>
using namespace std;

class complex
{
	public:
 /*
  *	Construct a complex number using the given parameter
  * The default behavior is to give the real and imaginary coefficient a value of 0 
  * @param real The real coefficient
  * @param imahinary The rel coefficient of the imaginary number
 */
	complex(double real=0, double imaginary=0);
	
 /* 
  * Destroy the complex number
  * This method is not implemented
 */
	~complex();
	
 /*
  *  This method will return the coefficient x 
  * @return Return the x coefficient in x + yi
 */
	double getReal() const;

 /*
  * This method will return the imaginary coefficient y
  * @return Return the y coefficient in x + yi
 */ 
	double getImaginary() const;

 /*
  * Overloaded the + operator to allow addition of complex number
  * This will not change the value of the complex number in parameter
  * @param c The complex number that we want to do addition
  * @return a complex number that is the result of the method
 */
	complex operator+(const complex &c) const;   
	
 /*
  * Overloaded the - operator to allow subtraction of complex number
  * This will not change the value of the complex number in parameter
  * @param c The complex number that we want to do subtraction
  * @return a complex number that is the result of the method
 */
	complex operator-(const complex &c) const;
	
 /*
  * Overloaded the + operator to allow multiplication of complex number
  * This will not change the value of the complex number in parameter
  * @param c The complex number that we want to do multiplication
  * @return a complex number that is the result of the method
 */
	complex operator*(const complex &c) const;
	
 /*
  * Overloaded the / operator to allow division of complex number
  * This will not change the value of the complex number in parameter
  * Print out error when dividing to 0
  * @param c The complex number that we want to do division
  * @return a complex number that is the result of the method
 */
	complex operator/(const complex &c) const;

 /*
  * This method will return the conjugate of a complex number
  * The conjugate of a x + yi complex will be x - yi
  * @return a complex that is the conjugate of the complex calling the method
 */
	complex conjugate() const;

 /* 
  *	Overloaded the == operator to allow comparision between 2 complex numbers
  *	This will compare both coefficient of the first complex number to both coefficient of the complex number in the parameter
  *	@param c The address of the complex number being compared to
  *	@return TRUE if they are the same and FALSE if they are different
 */
	bool operator==(const complex &c) const;    // is object == parameter ?  

 /*
  *	Overloaded the != operator to test if both objects are different
  *	This will compare both coefficient of the first complex number to both coefficient of the complex number in the parameter
  *	@param c the complex number being compared to
  *	@return TRUE if they are different and FALSE if they are equal to each other
 */
	bool operator!=(const complex &c) const;      // is object != parameter?

 /*
  * Overloard the += operator to allow both addition and assignment at the same time
  * This method will perform addition first and then assign that value to the current object
  * @param c the address of the complex number that is used for addition
  * @return the address of the new complex number
 */
	complex& operator+=(const complex &c);       // current object += parameter
    
 /*
  *	Overloard the += operator to allow both addition and assignment at the same time
  * This method will perform addition first and then assign that value to the current object
  * @param c the address of the complex number that is used for addition
  * @return the address of the new complex number
 */
	complex& operator-=(const complex &c);       // current object -= parameter
	
 /*
  *	Overloard the += operator to allow both addition and assignment at the same time
  * This method will perform addition first and then assign that value to the current object
  * @param c the address of the complex number that is used for addition
  * @return the address of the new complex number
 */
	complex& operator*=(const complex &c);       // current object *= parameter
	
 /*
  *	Overloard the += operator to allow both addition and assignment at the same time
  * This method will perform addition first and then assign that value to the current object
  * @param c the address of the complex number that is used for addition
  * @return the address of the new complex number
 */
	complex& operator/=(const complex &c);       // current object /= parameter
	
 /*
  *	Overload the output stream << to allow displaying the complex number
  *	This will print out the complex number in the form x + yi
  *	This method will also handle special representation like print out 0 when x and y =0
  *	Or print out i instead of 1i
  *	@param output the output stream
  *	@param c the address of the complex that we want to print
  *	@return the output stream and print out the complex number
 */
		friend ostream& operator<<(ostream &output, const complex &c) ;

 /*
  *	Overload the input to allow the user to enter the coefficient for a complex number
  *	This will prompt the ser 2 times to enter the input. First time will be for x, second time will be for y
  * @param input the input stream
  * @param c the address of the complex that we will change based on the input
  *	@return the input stream and this will change the c parameter to user's input
 */
	friend istream& operator >> (istream &input, complex &c) ;

	
private:
	double realNumber; // The x coefficient in x + yi
	double imagineNumber; // The y coefficient in x + yi
};
#endif


