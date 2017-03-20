/*
	* @author Thuan Tran
	* Programming Assignment 6: Implement a Linked List
	* Date: November 23th,2016
*/



#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
using namespace std;

struct Node
{
	Node* nextNode;
	int value;
};
class linklist
{
	

public:
	linklist();
	linklist(const linklist &copy);
	~linklist();

	
	bool isEmpty() const; // Check if the list is empty
	int  listSize(); // Check how many elements in the list
	void clear(); // Clear the list

	bool insertToEnd(int x); // append the value x to the end of list
	bool insert(int index, int x); // insert value x to the position index
	bool remove(int x); // remove from the list value x , if any
	bool removeAtIndex(int x); // remove value at index x

    void print(); // Print out the list

	void ReverseIterative(); // reverse the list in an iterative way
	void ReverseRecursive(); // reverse the list in a recursive way
	const linklist &operator=(const linklist &a);

private:
	void recur(Node **x); // private helper to reverse the list in recursive way
	Node* head;
	int size;

};
#endif
