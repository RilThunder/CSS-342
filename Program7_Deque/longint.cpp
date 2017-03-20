/*
	@author Thuan Tran
	Program 7: Implement a LongInt class 
	Dec 10,2016
*/


#include "longint.h"

/*
	This method overload the input stream
	@param in the input stream
	@param rhs the LongInt that will have new value
	@return the input stream
*/
istream & operator >> (istream & in, LongInt & rhs)
{
	rhs.digits.clear(); // Clean the LongInt before put new data into
	char read = '0';
	while (in.good() && ((read = in.get()) != '-') && (read < '0' || read >'9')) // must be from range 0-9
	{
		// Skip the blank space
	}
	if (read == '-') // Check for negative sign
	{
		rhs.negative = true;
		if (in.good())
		{
			read = in.get(); // Check for the next characer 
		}
	}
	while (read >= '0' && read <= '9')
	{
		rhs.digits.addBack(read - '0');
		// read a new charactor
		read = in.get(); // Check next available item
	}
	rhs.remove0s(); // Trim the number
	return in;
}

/*
	*This method overload the output operator and print out the LongInt
	@param out the output stream
	@param rhs the LongInt to print out
	@return the output stream
*/
ostream & operator<<(ostream & out, const LongInt & rhs)
{
	Deque<char> x = rhs.digits; // Creat a copy to print out
	if (rhs.negative) // Check for the sign
	{
		out << " - ";
	}
	if (x.isEmpty())
	{
		out << "0";
		return out;
	
	}
	while (x.size() > 0) // Iterate and print out
	{
		out << (int) (x.removeFront() );
	}
	return out;
}

/*
	This contructor will construct a new LongInt based on the given string
	@param str the string that has the number to be created
*/
LongInt::LongInt(const string str)
{
	digits.clear(); // Clean up first
	negative = false;
	bool oddThings = false; // This will be used to check if there are any odd things between number
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '-' && negative == false)
		{
			negative = true; // Check the sign of the string
			continue;
		}
		// We do not need to check the white space before number
		if (str[i] >= '0' && str[i] <= '9')
		{
			// At this point, we have started to go into the number
			oddThings = true;
			digits.addBack((char)str[i] - '0');
		}
		else
			// There are some strange characters inside
			if (oddThings == true)
			{
				break;
			}
	}
	remove0s();
}

/*
	*This is the copy constructor for the LongInt
	@param rhs the LongInt to be copy
*/
LongInt::LongInt(const LongInt & rhs)
{
	digits.clear(); // Clean up
	negative = false; 
	*this = rhs; // Utilize the = operator
	remove0s();
}

/*
	This is the default constructor for the LongInt
	Since Longint are read from input, to make a new one, need to make sure the deque is empty;
*/
LongInt::LongInt()
{
	digits.clear(); // Make the deque empty to hold new variable
	negative = false;
}

/*
	This is the destructor for the LongInt
	To destroy this, we just need to clear it and delete it
*/
LongInt::~LongInt()
{
	digits.clear();
}

/*
	This method will overload the addition operator
	This will add 2 LongInt together and return a new LongInt
	@param rhs the second LongInt to add with the current LongInt
	@return a new LongInt that is the result of the addition
*/
LongInt LongInt::operator+(const LongInt & rhs) const
{
	if (negative == false && rhs.negative == true)
	{
		LongInt temporary = rhs;
		temporary.negative = false;
		return *this - temporary; // Cases when we can utilize the - operator
	}
	if (negative == true && rhs.negative == false)
	{
		LongInt temporary = *this;
		temporary.negative = false;
		return rhs - temporary;
	}
	// The only cases left are + + and - - in which we perform normal addition
	int size = rhs.digits.size() < digits.size() ? rhs.digits.size() : digits.size(); // Compare the size of 2 LongInt 
	LongInt answer;
	Deque<char> firstCopy = digits; // Get the queue of 2 LongInt to perform addition
	Deque<char> secondCopy = rhs.digits;
	int carry = 0;
	while (size != 0) // Go through the smaller queue
	{
		int x = (int)firstCopy.removeBack();
		int y = (int)secondCopy.removeBack();
		int result = x + y + carry; 
		carry = result / 10;
		answer.digits.addFront((char)(result % 10));
		size--;
	}
	int resultSecond = 0;
	while (firstCopy.size() > 0) // Check if we still have more elements
	{   // We still need to the latest carry integer
		resultSecond = (int)firstCopy.removeBack() + carry;
		answer.digits.addFront((char)(resultSecond % 10)); // Exhaust the remaining of 2 deque to make sure no elements are behind
		carry = resultSecond / 10;
	}
	while (secondCopy.size() > 0)
	{
		resultSecond = (int)secondCopy.removeBack() + carry;
		answer.digits.addFront((char)(resultSecond % 10));
		carry = resultSecond / 10;
	}
	if (negative == false && rhs.negative == false)
	{
		answer.negative = false;
		if (carry != 0)
		{
			answer.digits.addFront((char)carry); // Add the remaning carry
		}
		answer.remove0s();
	}
	if (negative == true && rhs.negative == true)
	{
		// This is the case where -(lhs+rhs). We only need to put the negative infront
		answer.negative = true;
		if (carry != 0)
		{
			answer.digits.addFront((char)carry);
		}
		answer.remove0s();
	}
	return answer;
}

/*
	This method will perform subtraction of 2 LongInt
	@param rhs the LongInt to be subtract
	@return a new LongInt that is the result of the subtraction
*/
LongInt LongInt::operator-(const LongInt & rhs) const
{
	
	LongInt answer;
	if (*this == rhs) // Special case when the result is equal to 0;
	{
		answer.negative = false;
		answer.digits.addBack(0);
		return answer;
	}
	if (rhs.negative == true && negative == false)
	{
		LongInt temporary = rhs;
		temporary.negative = false; // a - - b = a+ b
		answer = *this + temporary;
		answer.negative = false; // Utilize the + operator
		return answer;
	}
	if (rhs.negative == false && negative == true)
	{
		LongInt temporary = rhs;  // -a - b = -(a+b)
		temporary.negative = false;
		LongInt temporarySecond = *this;
		temporarySecond.negative = false;
		answer = temporarySecond + temporary;
		answer.negative = true;
		return answer;
	}

	Deque<char> firstCopy;
	Deque<char> secondCopy;

	if (negative == true && rhs.negative == true)
	{
		if (*this >= rhs)
		{
			// Check for multiple cases and compare between 2 LongInt to determine the sign first
		
			answer.negative = false;
			firstCopy = rhs.digits;
			secondCopy = digits;
		}
		else
		{
			answer.negative = true ;
			firstCopy = digits;
			secondCopy = rhs.digits;
		}
	}
	if (negative == false && rhs.negative == false)
	{
		if (*this < rhs)
		{
			answer.negative = true;
			firstCopy = rhs.digits;
			secondCopy = digits;

		}
		else
		{
			answer.negative = false;
			firstCopy = digits;
			secondCopy = rhs.digits;
		}
	}
	int size = firstCopy.size() > secondCopy.size() ? firstCopy.size() : secondCopy.size();
	int carry = 0;
	int result = 0;
	while (size != 0) // Go through all the number 
	{
		int x = firstCopy.size() > 0 ? (int)firstCopy.removeBack() : 0;
		int y = secondCopy.size() > 0 ? (int)secondCopy.removeBack() : 0;
		if ((x - y - carry )>= 0)
		{
			 
			result = x -y- carry; // This will still in positive range
			carry = 0;

		}
		else
		{
			result = x + 10 - y - carry; // We will get negative integer so add 10 to make up 
			carry = 1;
		}
		answer.digits.addFront((char) abs(result));
		size--;

	}
	answer.remove0s();
	return answer;
	
}


/*
	* This method overloaded the assgienment operator for the LongInt
*/
const LongInt & LongInt::operator=(const LongInt & rhs)
{

	negative = rhs.negative;
	digits = rhs.digits; // Already overloaded the = operator in Deque class

	return *this;
}

/*
	This method will compare if the current LongInt is less than the compared LongInt
	This will check the sign first and return the result. If the sign is the same, It will then interate to check the whole deque
	@param rhs the LongInt that we need to compare to
	@return a boolean variable indicating if this is less than the parameter
*/
bool LongInt::operator<(const LongInt & rhs) const
{
	bool result = true;
	if (negative == true && rhs.negative == false)
	{
		// negative lhs is less than positive rhs
		return result;
	}
	if (negative == false && rhs.negative == true)
	{
		// positive lhs is greater than negative rhs
		return !result;
	}
	int firstSize = digits.size();
	int secondSize = rhs.digits.size();
	if (firstSize < secondSize) 
	{
		if (negative == true && rhs.negative == true)
		{
			return !result; // for negative number, the smaller in lenght it is, the bigge it is
		}
		else
		{
			return result; // At this point, the only sign left is negative  = faslse && rhs.negative = false;
		}
	}
	if (firstSize > secondSize)
	{
		if (negative == true && rhs.negative == true)
		{
			return !result; // Same like above
		}
		else
		{
			return !result; // At this point, the only sign left is negative  = faslse && rhs.negative = false;
		}
	}
	if (firstSize == secondSize)
	{
		Deque<char> a = digits;
		Deque<char>b = rhs.digits;
		while (firstSize > 0)
		{
			int x = (int)a.removeFront() ; // Now iterate and check from the front
			int y =  (int) b.removeFront() ;
			if ((x - y) != 0)
			{
				if (negative == true && rhs.negative == true)
				{
					// Negative number, smaller means bigger
					return x < y ? !result : result;
				}
				else
				{
					return x < y ? result : !result; 
				}
			}
		}
	}
}

/*
	*This method overloaded the <= operator
	@param rhs the LongInt to compare to
	@return a boolean value indicate if the LongInt is <= to the other LongInt
*/
bool LongInt::operator<=(const LongInt & rhs) const
{
	if (*this < rhs)
	{
		return true;
	}
	if (*this == rhs)
	{
		return true;
	}
	return false;
}

/*
	*This method will overload the > operator
	@param rhs the LongInt to compare to
	@return a boolean value if the LongInt is less than rhs
*/
bool LongInt::operator>(const LongInt & rhs) const
{
	return  !(*this <= rhs);
}

/*
	This method will overload the >= operator
	@param rhs the LongInt to compare to
	@return a boolean value if the LongInt is  >= to the rhs
*/
bool LongInt::operator>=(const LongInt & rhs) const
{
	return !(*this < rhs);
}

/*
	This method will overload the == operator
	@param rhs The LongInt to compare to
	@return a boolean value if the LongInt is == to the rhs
*/
bool LongInt::operator==(const LongInt & rhs) const
{
	if (negative != rhs.negative)
	{
		return false; // Check the sign first
	}
	if (digits.size() != rhs.digits.size())
	{
		return false; // Check the size second
	}
	Deque<char> thisCompare = digits;
	Deque<char> theCompare = rhs.digits;
	while (theCompare.size() > 0) // Now iterate through both LongInt and compare each element
	{
		int theResult = (int) thisCompare.removeFront()  - (int) theCompare.removeFront() ;
		if (theResult != 0)
		{
			return false;
		}
	}
	return true;
}

/*
	This method will overload the != operator
	@param rhs the LongInt to compare to
	@return a boolean value if the LongInt is different from the rhs
*/
bool LongInt::operator!=(const LongInt & rhs) const
{
	return !(*this == rhs);
}

/*
	This private helper method will remove all the 0 that appear infront of the LongInt
*/
void LongInt::remove0s()
{      
	


	while (digits.getFront() == 0) // While the front is still 0, remove it and iterate to the next one
	{
		digits.removeFront();

	}
	if (digits.isEmpty())
	{
		digits.addBack(0);
		negative = false;
	}
	return;

}
