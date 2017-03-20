/*
*	CSS 342 Programming 2
*	euclid.cpp
*	Purpose: Print out Greatest Common Divisor and Run time
*	
*	@author	Thuan Tran
*	@version 2.0 October 23rd, 2016
*/


#include <iostream>
#include <sys/time.h> 

using namespace std;


/* This function will be used to measure the run time of main()
   Unit is ms ( microsecond)
   This can be compiled in Linux
*/
int gettimeofday(struct timeval *tv, struct timezone *tz);


/* This function will calculate the greates common devisor of 2 numbers
   This function will also have a counter variable to count the number of modulus opearations
   @param A The function number
   @param B The second number
   @param x The counter variable that will be use to calculate the number of modulus operations
   @return the greates common devisior of A and B

*/
int gcd(int A, int B, int &x)
{
	if (A < B)
	{
		return gcd(B, A, x); // switch position to calculate
	}
	int remainder = A % B;
	x = x + 1; 
	if (remainder == 0)
	{
		return B;
	}

	return gcd(B, remainder, x);
}
	
/* This function will prompt the user to enter a number 
   The function will output the greatest common divisor and the maximum number of modulus operator

*/

int main()
{
	cout << "Please enter an integer: "; 
	int x;
	cin >> x;
	int greatestA = 0; // This will be used to save the number that has the most modulus operation in iteration
	int greatestB = 0;
	int counter = 1;
	int result; // Result of the gcd() that has the most modulus operation at outer iteration
	int k; // Result of the gcd() that has the most modulus opearation at inner iteration
	struct timeval startTime;
	struct timeval endTime;
	double elapsed = 0;
	for (int i = 8; i <= x; i++) 
	{	

		gettimeofday(&startTime, NULL);

		for (int j = 1; j <= i; j++)
		{
			
				int insideCounter = 0; // temporary variable for the counter
				k = gcd(j, i, insideCounter); // 
				if (insideCounter > counter) // save the counter variable if this gcd is greater than previous
				{
					counter = insideCounter;
					greatestA = j; 
					greatestB = i;
					result = k;
				}
			
		}
		gettimeofday(&endTime, NULL);
		elapsed = endTime.tv_usec - startTime.tv_usec; // Calculate the time
		cout << "At i = " << i << ";" << " gcd" << "(" << greatestA << "," << greatestB << ") = ";
		cout << result << " took " << counter << " modoulus operator" << " and it tooks ";
		cout << elapsed << "ms" << endl;
		
	}
	


}