/*
	@author Thuan Tran
	CSS 342 Program 5
	November 17th,2016
	Purpose: Implement a skip list find and remove methord
*/

/*
	This is the default constructor for skip list.
	It created a default skip list by creating 6 level of list with only left and right most Node
*/
template<class Object>
SList<Object>::SList()
{
	init();
}

/*
	This is the copy constructor of skip list
	It started by creating a default skip list like above
	Then use the overloaded = operator to create a copy
*/
template<class Object>
SList<Object>::SList(const SList &rhs)
{
	init();
	*this = rhs;                                   // then assign rhs to this.
}

/*
	This is the initialization method for the skip list
	It initialize the skip list by creating left and right dummy Node on 6 level total
*/
template<class Object>
void SList<Object>::init()
{
	for (int i = 0; i < LEVEL; i++)
	{   // for each level
        // create the left most dummy nodes;
		header[i] = new SListNode<Object>;
		header[i]->prev = NULL;
		header[i]->down = (i > 0) ? header[i - 1] : NULL;
		header[i]->up = NULL;
		if (i > 0) header[i - 1]->up = header[i];
		// create the right most dummy nodes;
		header[i]->next = new SListNode<Object>;
		header[i]->next->next = NULL;
		header[i]->next->prev = header[i];
		header[i]->next->down = (i > 0) ? header[i - 1]->next : NULL;
		header[i]->next->up = NULL;
		if (i > 0) header[i - 1]->next->up = header[i]->next;
	}

	// reset cost.
	cost = 0;
}

/*
	This is the destructor of the skip list
	It destroyed the skip list by clearing all elements first
	Then clear the left and right most dummy Node on each level
*/
template<class Object>
SList<Object>::~SList()
{
	clear();                                      // delete items starting 1st
	for (int i = 0; i < LEVEL; i++)
	{
		delete header[i]->next;                      // delete the right most dummy
		delete header[i];                            // delete the left most dummy
	}
}

/*
	This function check whether the skip list is empty
	By checking if there are any intermediate Node between the 2 dummy node
	@return a boolean value that is true if there is intermediate Node. False otherwise
*/
template<class Object>
bool SList<Object>::isEmpty() const
{
	// If it were empty, then header.next will be the right dummy node
	return (header[0]->next->next == NULL);
}

/*
	This function return the size of how many element are there in the skip list
	This do not include element on higher level. Only element of the lowest level
	@return an integer indicate the size of the skip list
*/
template<class Object>
int SList<Object>::size() const
{
	SListNode<Object> *p = header[0]->next; // at least the right most dummy
	int size = 0;

	for (; p->next != NULL; p = p->next, ++size);
	return size;
}

/*
	This function is used to clear the skip list by going through every Node at every level
	Except the 2 dummy node at each level
*/
template<class Object>
void SList<Object>::clear()
{
	for (int i = 0; i < LEVEL; i++)
	{        // for each level
		SListNode<Object> *p = header[i]->next;  // get the 1st item 
		while (p->next != NULL)
		{              // if this is not the left most
			SListNode<Object> *del = p;
			p = p->next;                           // get the next item
			delete del;                            // delete the current item
		}
		header[i]->next = p;                     // p now points to the left most 
	}                                          // let the right most point to it
}

/*
	This function is used to insert an element into the skip list
	This will insert at lower level and then use random to check 
	if it should insert at higher level or not
	@param obj the object that we want to insert 
*/
template<class Object>
void SList<Object>::insert(const Object &obj)
{
	// right points to the level-0 item before which a new object is inserted.
	SListNode<Object> *right = searchPointer(obj);
	SListNode<Object> *up = NULL;

	if (right->next != NULL && right->item == obj)
		// there is an identical object
		return;
  
	int x = rand() % 2;
	SListNode<Object> *newItem = new SListNode<Object>;
	newItem->item = obj; // Inserting the item in the lowest level 
	newItem->up = NULL; // No Node that is up and down so far
	newItem->down = NULL;
	newItem->next = right; // Insert before "right"
	newItem->prev = right->prev; // Change to point to the one before "right"
	right->prev->next = newItem; // Change so the one before "right" point to the new Item
	right->prev = newItem; // Change so that previous of "right" point to the newItem
	if (x != 1)
	{
		return; // Do not insert if random != 1;
	}
	up = newItem; // if it is not, start inserting item
	int count = 1; // Counter to make sure not to insert at top level 
	while (x == 1) // If we still getting 1, keep inserting
	{
		while (up->prev != NULL) // Check for leftmost case
		{
		
			up = up->prev;
			if (up->up != NULL) // Check for top level case 
			{
				up = up->up;
				up = up->next; 
				
				SListNode<Object> *insert = new SListNode<Object>;
				insert->item = obj;
				insert->next = up;   // Changing all the node around the new Node
				insert->up = NULL;   // Include the Node on right, on left and below;
				insert->prev = up->prev;
				
				insert->down = newItem;
				newItem->up = insert;
				up->prev->next = insert;
				up->prev = insert;
				count++; // As we insert item in 1 level, increment. Stop when 
				newItem = insert; // Save the current location to insert next time we go up
				break;
			}
		}
		if (count == 5) // 5 level maximum 
		{
			break; // Not to reach top level 
		}
		x = rand() % 2; // should we continue inserting ?
	}
	return;
}

/*
 This method is used to check if we can find the object in the skip list
 @param obj the obj we want to find
 @return a boolean value indicate successful found or not
*/
template<class Object>
bool SList<Object>::find(const Object &obj)
{
	// p oints to the level-0 item close to a given object
	SListNode<Object> *p = searchPointer(obj);

	return (p->next != NULL && p->item == obj);     // true if obj was found
}

/*
	This method is used to find the location of an object in the skip list
	@param obj the object we want to find
	@return a pointer to the location after that
*/
template<class Object>
SListNode<Object> *SList<Object>::searchPointer(const Object &obj)
{
	SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
	while (p->down != NULL)  // While we have not reach beyond the lowest level 
	{
		p = p->down;
		cost++;

		if (p->prev == NULL)						
		{											 // at the left most item
			if (p->next->next == NULL)              // no intermediate items
				continue;
			else
			{                                    // some intermadiate items
				if (p->next->item <= obj)
				{                               // if 1st item <= obj
					p = p->next;                          // shift right to item 1
					cost++;
				}
			}
		}

		while (p->next->next != NULL && p->next->item <= obj)
		{
			// shift right through intermediate items as far as the item value <= obj
			p = p->next;
			cost++;
		}
	}

	// now reached the bottom. shift right once if the current item < obj
	if (p->prev == NULL || p->item < obj)
	{ // Special case when there are only 2 dummy Node or we need to shift right
		// Or we are near at the right most Node but still no match
		p = p->next;
		cost++;
	}
	return p; // return the pointer to an item >= a given object.
}

/*
	This method is used to remove an object from the skip list
	@param obj the obj to remove 
*/
template<class Object>
void SList<Object>::remove(const Object &obj)
{
	// p points to the level-0 item to delete
	SListNode<Object> *p = searchPointer(obj);

	// validate if p is not the left most or right most and exactly contains the
	// item to delete
	if (p->prev == NULL || p->next == NULL || p->item != obj)
		return;
	// At this point, we know that it is not the left most or right most Node 
	if (p->up == NULL) // Check if it only has 1 level
	{
		//	  SListNode<Object> *k = p->prev;
		p->prev->next = p->next;

		//  k->next = p->next;
		p->next->prev = p->prev;
		//p->next->prev = k;
		delete p; // Deallocate memory
		return;
	}
	SListNode<Object> *deleteNode = p;
	while (p != NULL) // going through each level to delete
	{
		p->prev->next = p->next; // Reconfigure the adjacent Node 
		p->next->prev = p->prev;
		p = p->up; // Go up
		delete deleteNode; 
		deleteNode = p;
	}

}

/*
	This overloaded the assignment operator to use in copy constructor
	@param rhs the skip list we want to copy to
	@return a refernce to the new skip list we created
*/
template<class Object>
const SList<Object> &SList<Object>::operator=(const SList &rhs)
{
	if (this != &rhs)
	{ // avoid self-assignment
		clear();           // deallocate old items

		int index;
		SListNode<Object> *rnode;
		for (index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
			rnode = rnode->next, ++index)
			insert(rnode->item);

		cost = rhs.cost;
	}
	return *this;
}

/*
	This method is used to get the Cost of the entire List. Cost to traverse,input
	@return an integer that represent the cost
*/
template<class Object>
int SList<Object>::getCost() const
{
	return cost;
}

/*
	This method is used to print out the skip list
*/
template<class Object>
void SList<Object>::show() const
{
	cout << "contents:" << endl;
	for (SListNode<Object> *col = header[0]; col != NULL; col = col->next)
	{
		SListNode<Object> *row = col;
		for (int level = 0; row != NULL && level < LEVEL; level++)
		{
			if (row->prev == NULL)
				cout << "-inf\t";
			else if (row->next == NULL)
				cout << "+inf\t";
			else
				cout << row->item << "\t";
			row = row->up;
		}
		cout << endl;
	}
}

