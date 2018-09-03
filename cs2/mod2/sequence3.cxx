// Section CSC161 - Computer Science II: C++
// File Name: sequence3.cxx
// Student: Chris Scarola
// Homework Number: 4
// Last Changed: 2/19/2017
/* CLASS IMPLEMENTED: sequence
   INVARIANT for sequence class:
   1. Some of your member variables are pointers. In fact, for your sequence
   class, four member variables are pointers.
   2. Member functions allocate and release memory as needed. Don't forget
   to write documentation indicating which member functions allocate
   dynamic memory so that experienced programmers can deal with failures.
   3. You must override the automatic copy constructor and the automatic
   assignment operator. Otherwise two different sequences end up with
   pointers to the same linked list. Some hints on these implementations are
   given in the following "value semantics" section.
   4. The class requires a destructor, which is responsible for returning all
   dynamic memory to the heap.
*/

#include "sequence3.h"
#include <algorithm>

namespace main_savitch_5
{
    //CONSTRUCTORS and DESTRUCTOR
    sequence::sequence()
        : head_ptr(NULL), tail_ptr(NULL), cursor(NULL), precursor(NULL), many_nodes(0)
    {
        //intentionally blank
    }

    //COPY CONSTRUCTOR
    sequence::sequence(const sequence& source)
    {
        //reset cursor and precursor, head and tail is reset during list_copy
        cursor = NULL;
        precursor = NULL;
        
        //set the new size
        many_nodes = source.many_nodes;

        //precursor points somewhere, many_nodes > 1
        if(source.precursor != NULL)
            {
                //save cursor data from source
                value_type _precursor = source.precursor->data();

                //copy source over
                list_copy(source.head_ptr, head_ptr, tail_ptr);

                //find the node the data is located in to set cursor/precursor
                precursor = list_search(head_ptr, _precursor);
                
                //if cursor was not beyond tail
                if(source.cursor != NULL) cursor = precursor->link();
            }

        //cursor point to head_ptr, no precursor
        if(source.cursor != NULL && source.precursor == NULL)
            {
                list_copy(source.head_ptr, head_ptr, tail_ptr); //copy over
                tail_ptr = list_locate(head_ptr,many_nodes);    //put tail at the end
                cursor = head_ptr;                              //set cursor back to head
            }

        //no cursor or precursor, source empty
        if(source.cursor == NULL && source.precursor == NULL)
            list_copy(source.head_ptr, head_ptr, tail_ptr); //should not do much

    }

    sequence::~sequence()
    {
        if(head_ptr != NULL) list_clear(head_ptr); //delete each node, leaves head_ptr null
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    //MODIFICATION MEMBER FUNCTIONS
    //Assignment Operator
    void sequence::operator=(const sequence& source)
    {
        //handle self assignment
        if(this == &source) return;  

        //clear any data to get ready for copy
        list_clear(head_ptr);

        //reset cursor/precursor, head/tail ptr is set in list_copy
        cursor = NULL;
        precursor = NULL;

        //set the new size
        many_nodes = source.many_nodes;

        //precursor points somewhere, many_nodes > 1
        if(source.precursor != NULL)
            {
                //save cursor data from source
                value_type _precursor = source.precursor->data();

                //copy source over
                list_copy(source.head_ptr, head_ptr, tail_ptr);

                //find the node the data is located in to set cursor/precursor
                precursor = list_search(head_ptr, _precursor);
                
                //if cursor was not beyond tail
                if(source.cursor != NULL) cursor = precursor->link();
            }

        //cursor point to head_ptr, no precursor
        if(source.cursor != NULL && source.precursor == NULL)
            {
                list_copy(source.head_ptr, head_ptr, tail_ptr); //copy over
                tail_ptr = list_locate(head_ptr,many_nodes);    //put tail at the end
                cursor = head_ptr;                              //set cursor back to head
            }

        //no cursor or precursor, source empty
        if(source.cursor == NULL && source.precursor == NULL)
            list_copy(source.head_ptr, head_ptr, tail_ptr);     //should not do much

    }
    
    void sequence::start()
    {
        if(head_ptr != NULL) cursor = head_ptr;
        precursor = NULL;
    }

    void sequence::advance()
    {
        if(cursor == NULL) return;       //if empty or beyond tail_ptr
        if(cursor != tail_ptr)
            {
                precursor = cursor;       //set precursor to before cursor
                cursor = cursor->link();  //don't advance beyond tail_ptr
            }
        else
            {
                cursor = NULL;
                precursor = tail_ptr;
            }
    }

    void sequence::insert(const value_type& entry)
    //before cursor
    {
        //cursor at head or not pointing
        if(cursor == NULL || cursor == head_ptr)
            {
                if(head_ptr == NULL)
                    {
                        list_head_insert(head_ptr, entry); //insert item - set head_ptr
                        tail_ptr = head_ptr;               //set tail to head
                        cursor = head_ptr;                 //set cursor to head
                    }
                else
                    {
                        cursor = new node(entry, head_ptr); //cursor point to new node, which points to head 
                        head_ptr = cursor; //move head_ptr back to cursor to point at the inserted item 
                        precursor = NULL;  //cursor back to head_ptr, precursor must be NULL
                    }
            }
        //cursor pointing somewhere in middle
        if(precursor != NULL && precursor != tail_ptr)
            {
                value_type _precursor = precursor->data();     //store location of precursor
                list_insert(precursor, entry);                 //add item - moves precursor to item
                precursor = list_search(head_ptr, _precursor); //move precursor back before item
                cursor = precursor->link();                    //put cursor on item added
            }
        
        ++many_nodes;
    }

    void sequence::attach(const value_type& entry)
    //after cursor
    {
        //Non empty list
        if(cursor != NULL)
            {
                precursor = cursor;          //move precursor up one
                list_insert(cursor, entry);  //add item, cursor links to new node, but not pointing at

                //move the tail_ptr if cursor was at the end and added an item
                if(tail_ptr->link() != NULL) tail_ptr = tail_ptr->link();
                
                cursor = cursor->link();     //set the cursor on the new item                 
            }
        else
            {
                //Cursor beyond tail
                if(precursor == tail_ptr && tail_ptr != NULL)
                    {
                        tail_ptr = new node(entry);	//point to a new node, link still NULL
                        precursor->set_link(tail_ptr);  //precursor was on tail so move its link
                        precursor = tail_ptr;           //put precursor back on tail
                    }
                //Empty list
                if(head_ptr == NULL)
                    {
                        list_head_insert(head_ptr, entry); //insert data
                        tail_ptr = head_ptr;               //set tail to head
                        cursor = head_ptr;                 //set cursor to head
                    }
            }
		
        ++many_nodes;        //increment size of list
    }

    void sequence::remove_current()
    {
        if(is_item())
            {
                node* remove_ptr;
                bool item_removed = false;

                //normal removal
                if (cursor != head_ptr && cursor != tail_ptr)
                    {
                        cursor = cursor->link();     //move cursor to item after removed
                        list_remove(precursor);      //remove the item, precursor moves up
                        item_removed = true;
                    }

                //pointing at head, but not tail
                if (item_removed == false && precursor == NULL && cursor != tail_ptr)
                    {
                        remove_ptr = cursor;         //temp ptr to cursor
                        head_ptr = head_ptr->link(); //move head_ptr to next item
                        cursor = cursor->link();     //move cursor to next item
                        
                        delete remove_ptr;           //delete the item
                        item_removed = true;
                    }

                //pointing at tail, or head and tail
                if(item_removed == false && cursor == tail_ptr)
                    {
                        remove_ptr = tail_ptr;
                        
                        if(cursor == head_ptr)       //remove last item, reset linked sequence
                            {
                                head_ptr = NULL;
                                tail_ptr = NULL;
                                cursor = NULL;
                                precursor = NULL;                                
                            }
                        else
                            {
                                precursor->set_link(NULL);
                                tail_ptr = precursor;   //move tail_ptr back one
                                cursor = NULL;          //cursor points after tail or null
                            }                        

                        delete remove_ptr;     //delete the last node
                        item_removed = true;
                    }
                
                --many_nodes;
            }
    }

    //CONSTANT MEMBER FUNCTIONS    
    sequence::value_type sequence::current() const
    {
        if(is_item()) return cursor->data();
    }
}
