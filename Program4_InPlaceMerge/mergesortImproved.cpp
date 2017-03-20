/*
*	CSS 342 Programming 4
*	mergesortImproved.cpp
*	Purpose: Improved merge sort algorithm by using bottom up approach and 1
*	additional array
*	Reference: https://www.akawebdesign.com/2012/04/13/javascript-mergesort-top-down-vs-bottom-up/
*	@author	Thuan Tran
*	@version 2.0 November 10th, 2016
*/



#include <vector> 
#include <math.h>
using namespace std;

/*
*	This method will be use to merge data from the original array into the
*	additional array. This will divide the original array for 2 sections
*	And start merging from left most and middle to the second Array
*	@param firstArray The original array
*	@param secondArray The additional array
*	@param low the lower limit of where we want to start mergin
*	@param mid the middle section 
*	@param limit when we reach this, we want to stop
*/
template <class Comparable>
void merge(vector<Comparable> &firstArray, vector<Comparable> &secondArray, int low, int mid, int right)
{
	// Divide into 2 sections, the leftmost and the middle one
	// Start iterating to the right from each sections
	int indexRight = mid + 1;
	int indexLeft = low;
	for (int x = low; x <= right;x++)
	{
		// When we reach this if, we have tested all the possibilites on the left
		// The remaining are on the right => Exhaust them
		if (indexLeft > mid)
		{
			secondArray[x] = firstArray[indexRight];
			//firstArray[indexRight] = secondArray[x];
			indexRight++;
			
		}
		// The same for this if. We have tested all on the right
		// Exhaust the left to the array;
		else if (indexRight > right)
		{
			secondArray[x] = firstArray[indexLeft];
			indexLeft++;
		}
		// Comparision at the beginning and middle of the array
		else if (firstArray[indexLeft] < firstArray[indexRight])
		{
			// The left part smaller => give to the second array
			secondArray[x] = firstArray[indexLeft];
			indexLeft++; // Move to the next element on the left
						 // Right stay the same
		}
		else
		{
			// Reverse for the right. Right get incremented, left the same
			secondArray[x] = firstArray[indexRight];
			indexRight++;
		}

	}
	// Merge back what is in the second Array to the first Array
	for (int reMerge = low; reMerge <= right; reMerge++)
	{
		firstArray[reMerge] = secondArray[reMerge];
	}
	
}

/*
*	This function is used as the official merge sort
*	For each iteration, the size of the merge sort component will be 2 time the previous
*	It will also calculate the width for each iteration as well
*	@param a the original vector we want to sort
*/
template <class Comparable>
void mergesortImproved(vector<Comparable> &a) 
{

	int size = a.size();
	vector<Comparable> b(size); 
	// Starting bottom up, each time the size will be two times the previous
	// From 1 to 2 to 4,.. etc
	for (int i = 1; i < size ; i = i*2)
	{

		// The width of each iteration 
	
		for (int j = 0; j < size-i ; j = j + 2 * i)
		{
			// This will compute the minimum
			// For the width of each iteration, there is a limit so that it will stop
			// size -1 is when we have reached the end of array
			// Most of the time, we usually use the limit which is j+2*i -1
			int limit = j + 2 * i - 1 < size - 1 ? j + 2 * i - 1 : size - 1;
			// j + i -1 is used to calculate the middle of the width
			merge(a, b, j, j + i - 1, limit);
		}
	}
}