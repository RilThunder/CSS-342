/*
*	CSS 342 Program 3
*	Tran_cannibals.cpp 
*	Purpose: Solve the missionaries problem and print out the result
*
*	@author	Thuan Tran
*	@version 2.0 October 27, 2016
*/


/*
	IMPORTANT : To compile on linux type : ":  g++ -std=c++11 -o Tran_cannibals Tran_cannibals.cpp"

*/


#include<iostream>
#include <string>
#include <set>
#include <stack>
using namespace std;


/*
	This function will be used to find the path to solve the missionaries problem
	We are assuming that there are 3 missionaries and 3 cannibals on the left side of the river
	We want to bring all of them to the right side without getting eaten
	It will try every possiblities there are and will stop if it can not find the solution

	@param missLeft the number of missionaries on the left side of the river
	@param cannLeft the number of cannibals on the the side of the river
	@param status a boolean value indicate if we are on the left or right side of river. True for Left, False for right
	@param missRight the number of missionaries on the right side of the river
	@param cannRight the number of cannibals on the the right side of the river
	@param database a set of string that contains all the locations that we have visited
	@param result a stack of string that will be used to save the correct path

	@return bool Indicate if we are able to find a path or not

*/
bool cross(int missLeft, int cannLeft, bool status, int missRight, int cannRight,  set<string> & database, stack<string> &result )
	{
	string a = status ? "1" : "0"; // Transform the status to a string
	// This will be to make sure that we have visited every location and each of them is unique
	string visitedPlace = to_string(missLeft) + to_string(cannLeft)+ a  + to_string(missRight) + to_string(cannRight);
	
	// Base case 
	if (database.find(visitedPlace) == database.end())
	{
		database.insert(visitedPlace); // save the location
	}
	else
	{
		return false; // we have visited this already, backtrack
	}
	
	if (missLeft == 0 && cannLeft == 0  && missRight ==3 && cannRight ==3) 
	{
		return true;
	}
	if (missLeft < 0 || cannLeft < 0 || missRight <0 || cannRight <0)
	{
		return false; // out of bound
	}
	if ((missLeft > 0) && (missLeft < cannLeft))
	{
		return false; // missionaries get eaten
	}
	if ((missRight >0) && (missRight < cannRight)) 
	{
		return false;
	}
	
	// Recursive case
	if (status == true) // check if we are on the left side 
	{
		// Move from left to right so we will decrease people on the left and increase people on the right
		if (cross(missLeft - 2, cannLeft, !status,missRight+2,cannRight, database, result)) 
		{
			result.push("Bring 2 missionaries to the right"); // save the result if we reach the base case
			return true;
		}

		if (cross(missLeft, cannLeft - 2, !status, missRight, cannRight+2, database, result)) 
		{
			result.push("Bring 2 cannibals to the right");
			return true;
		}
		if (cross(missLeft - 1, cannLeft - 1, !status, missRight+1, cannRight+1, database, result)) 
		{
			result.push("Bring 1 missionaries and 1 cannibals to the right");
			return true;
		}
		if (cross(missLeft - 1, cannLeft, !status, missRight+1, cannRight, database, result)) 
		{
			result.push("Bring 1 missionaries to the right");
			return true;
		}
		if (cross(missLeft, cannLeft - 1, !status, missRight, cannRight+1, database, result)) 
		{
			result.push("Bring 1 cannibals to the right");
			return true;
		}
	}
	
	if (status == false) // check if we are at the right side
	{
		// Move people from right to left so people on the left get increased and people on the right get decreased
		if (cross(missLeft+2, cannLeft, !status, missRight-2, cannRight, database, result)) 
		{
			result.push("Bring 2 missionaries back to the left");
			return true;
		}
		if (cross(missLeft, cannLeft +2, !status, missRight, cannRight-2, database, result)) 
		{
			result.push("Bring 2 cannibals back to the left");
			return true;
		}
		if (cross(missLeft + 1, cannLeft + 1, !status, missRight-1, cannRight-1, database, result)) 
		{
			result.push("Bring 1 missionaries and 1 cannibals back to the  left");
			return true;
		}
		if (cross(missLeft +1, cannLeft, !status,missRight-1, cannRight, database, result)) 
		{
			result.push("Bring 1 missionaries back to the  left");
			return true;
		}
		if (cross(missLeft, cannLeft +1, !status, missRight, cannRight-1, database, result)) 
		{
			result.push("Bring 1 cannibals back to the  left");
			return true;
		}
	}
	return false; // If we reach here, that mean there are no possible path
}

/*
	This function will be used to print out the solution
*/
int main()
{
    set <string> visited;
	int x = 3; // missionaries on the Left
	int y = 3;  // cannibals on the left
	int xx = 0;// missionaries on the right
	int yy = 0; // cannibals on the right
	stack<string> path; // since we pass by reference, all the result will be in the stack when we are done
	cross(x, y, true, xx,yy,visited,path); // we are at the left side of the river so passed in true
	while (!path.empty()) //Iterate through the stack and print out the result
	{
		cout << "" << path.top();
		path.pop();
		cout << endl;
	}
	return 0;
}