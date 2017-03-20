#include "linklist.h"
#include <stdlib.h> 



int main()
{
	linklist a;
	// Insert 20 integer to the list;
	for (int i = 1; i <= 20; i++)
	{
		int x = rand() % 20 + 1;
		a.insert(i, x);
	}
	cout << "Result of inserting 20 integers" << endl;
	a.print(); // Test if successfully print out and insert
	cout << endl;
	cout << " Now removing all number 2 in the list, if exist" << endl;
	a.remove(2); 
	a.print(); 
	cout << endl;
	cout << " Now removing the first number in the list" << endl;
	a.removeAtIndex(1); // Remove the first
	a.print();
	cout << endl;
	cout << " Now insert 3 to the end of the list" << endl;
	a.insertToEnd(3);
	
	a.print();
	cout << endl;
	// How many element in the list
	cout << "Now print out how many number in the list ";
	cout << a.listSize();
	cout << endl;
	// Check if the list is empty while it still has elements: Expect true
	cout << "Now print out to check if the list is empty ";
	cout << a.isEmpty();
	cout << endl;

	// Recursively reverse the list;
	cout << "Now reverse the list recursively" << endl;
	a.ReverseRecursive();
	a.print();
	cout << endl;
	cout << " Now reverse the list iterative" << endl;
	a.ReverseIterative();
	a.print();
	cout << endl;

	cout << "Create a copy of the link list and print out content" << endl;
	linklist copy = a; 
	copy.print();

	copy.removeAtIndex(3);
	cout << "Print out copy link list and original list after remove 3rd element in copy list" << endl;
	copy.print();
	cout << "copy list now has " << copy.listSize() << " elements " << endl;
	cout << endl;

	a.print();
	cout << "original list now has " << a.listSize() << " elements " << endl;
	cout << "Check to clear the copy list" << endl;

	copy.clear();
	copy.print();
	return 0; 
}