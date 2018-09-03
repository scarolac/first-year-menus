// Section CSC161 - Computer Science II: C++
// File Name: queue3.h
// Student: Chris Scarola
// Homework Number: 7
// Last Changed: 3/12/2017
/* CLASS PROVIDED: queue

   CONSTRUCTOR:
   queue( )
       Postcondition: The queue has been initialized as an empty queue.

   MODIFICATION MEMBER FUNCTIONS:
   void pop( )
       Precondition: size( ) > 0.
       Postcondition: The front item of the queue has been removed.

   void push(const Item& entry)
       Postcondition: A new copy of entry has been inserted at the rear of the
       queue.

   CONSTANT MEMBER FUNCTIONS:
   bool empty( ) const
       Postcondition: The return value is true if the queue is empty.

   Item front( ) const
       Precondition: size( ) > 0
       Postcondition: The return value is a copy of the item at
       the front of the queue (and the queue is unaltered).

   size_type size( ) const
       Postcondition: The return value is the total number of items in the queue.

   PRIVATE FUNCTIONS:
   void clear_list(main_savitch_6B::node<Item>*& rear_ptr)
       Precondition: rear_ptr points at last item of queue
       Postcondition: clears the list, using pop() until rear_ptr is equal to NULL
       
   void copy_list(main_savitch_6B::node<Item>* source_ptr, main_savitch_6B::node<Item>*& rear_ptr)
       Precondition: rear_ptr is the last item of the queue
       Postcondition: copies a source rear_ptr until it reaches the starting value into a new lists rear_ptr
        source is unaltered

   VALUE SEMANTICS:
     Assignments and the copy constructor may be used with the class provided.

 */

#ifndef QUEUE3_H
#define QUEUE3_H
#include <cstdlib> //provides std::size_t
#include "node2.h" //node template class

template <class Item> class queue
{
public:
    //Typedefs
    typedef std::size_t size_type;
    typedef Item value_type;

    //Constructors + Destructor
    queue();
    queue(const queue<Item>& source);
    ~queue();

    //Modification member functions
    void pop();
    void push(const Item& entry);
    void operator =(const queue<Item>& source);

    //Constant member functions
    bool empty() const { return (count == 0); }
    Item front() const;
    size_type size() const { return count; }
    
private:
    main_savitch_6B::node<Item> *rear_ptr;
    size_type count;

    //private functions
    void clear_list(main_savitch_6B::node<Item>*& rear_ptr);
    void copy_list(main_savitch_6B::node<Item>* source_ptr, main_savitch_6B::node<Item>*& rear_ptr); 
};

//Include the implementation
#include "queue3.template"

#endif
