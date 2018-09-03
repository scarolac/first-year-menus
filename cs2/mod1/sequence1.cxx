// Section CSC161 - Computer Science II: C++
// File Name: sequence1.cxx
// Student: Chris Scarola
// Homework Number: 2
// Last Changed: 1/26/2017
/* CLASS IMPLEMENTED: sequence
   INVARIANT for sequence class:
   1. The number of items in a sequence is the member variable 'used'
   2. For an empty sequence, we do not care what is stored in data; for a non
   empty sequence, the items are stored in their sequence order from data[0] to data[used-1]
   and we do not care what is stored in the rest of data
   3. If there is a current item, then it lies in data[current_index]; if there is no current item,
   then current_index equals used
 */

#include "sequence1.h"

namespace main_savitch_3
{
    const sequence::size_type sequence::CAPACITY;

    //CONSTRUCTOR
    sequence::sequence() : used(0),current_index(0)
    {}

    //MODIFICATION MEMBER FUNCTIONS
    void sequence::start()
    {
        current_index = 0;
    }

    void sequence::advance()
    {
        if(current_index < used) ++current_index;  //don't advance pass used
    }

    void sequence::insert(const value_type& entry)
    //before current_item
    {
        if(size() < CAPACITY)
            {
                if(!is_item()) current_index = 0;
                for(size_type i = used; i > current_index; --i)
                    data[i] = data[i-1];     //move everything right by one
                data[current_index] = entry; //set the entry before other items
                ++used;                      
            }
    }

    void sequence::attach(const value_type& entry)
    //after current_item
    {
        if(size() < CAPACITY)
            {              
                if(!is_item()) //handle current_index at used and at 0
                    {
                        data[current_index] = entry; //add data to either end of list, or as first entry
                        if(current_index > 0) ++current_index; //if non empty list, increment current_index
                        ++used;                                //always increment used if data added
                        return;
                    }
                
                for(size_type i = used; i > current_index + 1; --i) //move data but 1 item less than insert
                    data[i] = data[i-1];    
                data[current_index + 1] = entry; //put data in slot after current_index
                ++current_index;                 //increment index to stay with item added
                ++used;                          //always increment used if data added
            }
    }

    void sequence::remove_current()
    {
        if(is_item())
            {
                for(size_type i = current_index + 1; i < used; ++i)
                    data[i-1] = data[i];
                --used;
            }
    }

    //CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const
    {
        return used;
    }

    bool sequence::is_item() const
    {
        if(current_index >= used) return false;

        return true;
    }

    sequence::value_type sequence::current() const
    {
        if(is_item()) return data[current_index];
    }
}
