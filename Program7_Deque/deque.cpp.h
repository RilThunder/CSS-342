/*
	@author Thuan Tran
	Purpose: Implement a Deque data structures
	Lab 7 for CSS 342
	Date: December 9th,2016
*/




/*
	This is the default constructor for the Deque
*/
template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
	front = NULL;
	back = NULL;

}

/*
	This is the copy constructor for the Deque
*/
template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
	front = NULL;
	back = NULL;
	*this = rhs;
}

/*
	This is the destructor for the Deque
*/
template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

/*
	This method will check if the deque is Empty or not
	@return a boolean value 1 if it is empty or 0 if it is not
*/
template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
	if (front == NULL)
	{
		return true;
  }
	return false;
}

/*
	This method will compute the size of the deque
	@return an integer which is the size of the Deque
*/
template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse queue
    ++i;

  return i;
}

/*
	This method will get the value at the Front of the Deque
	@return the item at the front 
*/
template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
	if (isEmpty())
	{
		throw "empty queue";
	}
  return front->item;
}

/*
	This method will get the value at the back of the Deque
	@return the item at the back
*/
template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
	if (isEmpty())
	{
		throw "empty queue";
	}
  return back->item;
}

/*
	This method will clear the deque by iterating through each element and clear

*/
template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}

/*
	This method will add item to the Front of the Deque
	@param obj the item to be add 
*/
template <class Object>
void Deque<Object>::addFront( const Object &obj ) {
  DequeNode *newNode = new DequeNode();  // create new Node to insert
  newNode->item = obj;
  newNode->next = front;
  newNode->prev = NULL;  
  if (front == NULL || back == NULL)
  {
	  back = newNode;
  }
  else
  {
	  front->prev = newNode;
  }
  front = newNode;
}

/*
	This method will add an objet to the back of the Deque
	@param obj the object to add
*/
template <class Object>
void Deque<Object>::addBack( const Object &obj ) { 
  DequeNode *newNode = new DequeNode();  // Create new Node to insert
  newNode->item = obj;
  newNode->next = NULL;
  newNode->prev = back;
  if (front == NULL || back == NULL) // Check for sepcial cases
  {
	  front = newNode;
  }
  else
  {
	  back->next = newNode; // Pointer rearrange
  }
  back = newNode;
}

/*
	This method will remove the item at the front of the Deque 
	@return the item at the Front 
*/
template <class Object>
Object Deque<Object>::removeFront( ) {  
	
  Object item = getFront();
  DequeNode *deleteNode = front;

  if (front == back) // only 1 element
  {
	
	  front = NULL;
		  back = NULL;
  }
  else {
    front = front->next; // Advance the front to the next item
    front->prev = NULL;
	
  }
  delete deleteNode;
                             // Deallocate the old Node
  return item;                     
}

/*
	This method will remove the item at the back of the Deque
	@return the item at the back
*/
template <class Object>
Object Deque<Object>::removeBack( ) {   
	
	Object item = getBack( );         

  DequeNode *deleteNode = back;                
  if (front == back)// only 1 element
  {

	  front = NULL;
		  back = NULL;
  }
  else {
    back = back->prev; // go back to the previous one
    back->next = NULL;
	
  }
  delete deleteNode;
           // Deallocate the old Node                
  return item;                      
}

/*
	This method overload the assignment operator
	@param rhs the Deque to deep copy
	@return a deep copy of the rhs Deque
*/
template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


