#include "linklist.h"

// NOTE: The index use in this link list is 1,2,3,4,... instead of 0,1,2,3,..
// So if we insert at index 1, we will insert at top of list
// if we insert at index 2, we will move to the location after index 1, change the pointer of index 1.
// and make the new value point to the old index 2, make the new value index 2

// TO COMPILE, TYPE : g++ linklist.cpp Driver.cpp

/*
	* This is the constructor for the link list;
*/
linklist::linklist()
{
	head = NULL;
	size = 0;
	
}

/*
	* This is the copy constructor for the link list
*/
linklist::linklist(const linklist & copy)
{
	*this = copy;
}

/*
	* This is the destructor for the link list
*/
linklist::~linklist()
{
	clear();

}

/*
	*Check if the list is empty by checking the size
	* 1 mean that it is empty. 0 mean that it is not empty
*/
bool linklist::isEmpty() const
{
	return size == 0 ? true : false;
}

/*
*	How many elements are there in the list
*/
int linklist::listSize()
{
	return size;
}


/*
*	Clear the list by deleting each element
*/
void linklist::clear()
{
	Node *x = head;
	if (x == NULL)
	{
		return; // Check for the case if it is an empty list, if it is, do not do anything
	}
	if (x->nextNode == NULL) // Check for the case only 1 element
	{
		delete x;
		head = NULL;
		return;
	}
	while (x != NULL) // Now the list has more than 1 element, go through each element and delete
	{
		Node *nextNode = x;
		x = x->nextNode;
		
		delete nextNode;
	}
	size = 0;
	head = NULL;
	return;
}

/*
*	This will insert an integer to the end of the list
	@param x the integer to insert
	@return boolean value if insert was successful
*/
bool linklist::insertToEnd(int x)
{
	if (head == NULL )// Check the case the list was empty
	{
		Node* newNode = new Node();
		newNode->value = x;
		newNode->nextNode = NULL;
		head = newNode;
		size++;
		
		return true;
	}
	return insert(listSize()+1, x); // insert to consecutive index at the end

}

/*
	This function will insert an integer at a specific index 
	@param index The location to insert
	@param x the integer value to insert
	@return a boolean indicate if insert was success
*/
bool linklist::insert(int index, int x)
{
	if (index > (size)+1 || index <1) // Check for invalid location, out of bound or less than 1
	{
		cout << "Unable to insert at that index" << endl;
		return false;
	}
	Node* newNode = new Node();
	newNode->value = x;
	newNode->nextNode = NULL;
	if (index == 1) // Check if we want to insert at top of list 
	{
		newNode->nextNode = head;
		head = newNode;
		size++;
		return true;

	}
	Node* traverse = head; // Traverse through the list to the location we need to insert

	for (int i = 1; i < index-1 ; i++) // Stop before the location we want to insert
	{
		if (traverse->nextNode != NULL)
		{
			traverse = traverse->nextNode;
		}
	}
	newNode->nextNode = traverse->nextNode;
	traverse->nextNode = newNode;
	size++;
	return true;
}

/*
	This function remove all integer has value x from the list,if any
	@param x the interger value to remove
	@return a boolean if remove was successful
*/
bool linklist::remove(int x)
{
	Node* first = head;
	if (first == NULL) // Check for empty list
	{
		head = NULL;
		cout << "No value to remove" << endl;

		return false;
	}
	if (first->value == x)
	{
		head = first->nextNode;
		delete first; // Check for remove at top of list. Need to rearrange head pointer 
		size--;
	}
	first = head;
	while (first->nextNode != NULL) // Traverse through the list and remove all integer has value x
	{
		if (first->nextNode->value == x)
		{
			Node* x = first->nextNode;
			first->nextNode = first->nextNode->nextNode;
			delete x;
			size--;
		}
		first = first->nextNode;
	}
	
	return true;
}

/*
	*This function remove an integer at a specific index
	@param x the index of the integer that will be remove
	@return a boolean if remove was success
*/
bool linklist::removeAtIndex(int x)
{
	if (x > size || x < 1)
	{
		cout << "Invalid index" << endl;
		return false;
	}

	Node* first = head;
	if (x == 1) // Check for remove at top
	{
		head = first->nextNode;
		delete first;
		size--;
		return true;
	}
	
	int i = 1;
	while (i < x-1) // Traverse through the list
	{
		first = first->nextNode;
		i++;
	}
	Node *deleteNode = first->nextNode;
	first->nextNode = deleteNode->nextNode;
	size--;
	delete deleteNode;
}

/*
	*This function print out all the value of the list
*/
void linklist::print()
{
	Node* print = head; // Check for empty list
	if (print == NULL)
	{
		cout << "The list is empty" << endl;
		return;
	}
	
	while (print != NULL)
	{
		cout <<  print->value << endl;
		print = print->nextNode;
		
	}
	return;
}

/*
	*This function will reverse the list by going in an iterative way
	
*/
void linklist::ReverseIterative()
{
	Node *previous = NULL;
	Node *x = head;
	Node *next = x->nextNode;
	if (x == NULL || next == NULL)
	{
		return; // Check if the list is empty or only has 1 element;

	}
	while (x!= NULL)
	{

		next = x->nextNode; // Rearranging pointer 
		x->nextNode = previous;
		previous = x;
		x = next;
	}
	head = previous; // Now the head is at the used to be the last element of the list 
	
	return;

}

/*
	* This function reverse the list in a recursive way
*/
void linklist::ReverseRecursive()
{
	recur(&head);
}


/*
	* This overload the assignent operator for the copy constructor
*/
const linklist & linklist::operator=(const linklist & a)
{
	if (this != &a)
	{
		clear(); // Check for self assignement 
	}
	Node *theNode = a.head;
	while (theNode != NULL)
		{
			insertToEnd(theNode->value);
			theNode = theNode->nextNode;
		}

	return *this;


}

/*
	* Recursively reverse the list by going to the end of the list and reassign pointer at that location
	* This used double pointer to make sure that the parameter was at the exact memory location
*/
void linklist::recur(Node** x)
{
	Node *current = *x;
	if (current == NULL)
	{
		return; 
	}
	Node *k = current->nextNode;
	if (k == NULL)
	{
		head = current; // at the end of the list, assigning head pointer 
		return;
	}
	recur(&k);
	current->nextNode->nextNode = current; // Next pointer now point back to current pointer
	current->nextNode = NULL; // Current pointer now point to NULL
	*x = k;
}




