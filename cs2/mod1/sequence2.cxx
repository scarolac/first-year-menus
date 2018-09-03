// Section CSC161 - Computer Science II: C++
// File Name: sequence2.cxx
// Student: Chris Scarola
// Homework Number: 3
// Last Changed: 2/1/2017
/* CLASS IMPLEMENTED: sequence
   INVARIANT for sequence class:
   1. The number of items in a sequence is the member variable 'used'
   2. For an empty sequence, we do not care what is stored in data; for a non
   empty sequence, the items are stored in their sequence order from data[0] to data[used-1]
   and we do not care what is stored in the rest of data
   3. If there is a current item, then it lies in data[current_index]; if there is no current item,
   then current_index equals used
   4. If the sequence is full, make more room, using dynamic arrays
 */

#include "sequence2.h"
#include <algorithm>

namespace main_savitch_4
{
    const sequence::size_type sequence::DEFAULT_CAPACITY;

    //CONSTRUCTORS and DESTRUCTOR
    sequence::sequence(size_type initial_capacity)
        : data(new value_type[initial_capacity]),used(0),current_index(0),capacity(initial_capacity)
    {
        //intentionally blank
    }
    
    sequence::sequence(const sequence& source)
        : data(new value_type[source.capacity]),
          used(source.used),
          current_index(source.current_index),
          capacity(source.capacity)
    {
        //copy the data from source array into new object
        std::copy(source.data, source.data + used, data); 
    }

    sequence::~sequence()
    {
        delete [] data;
    }

    //MODIFICATION MEMBER FUNCTIONS
    void sequence::resize(size_type new_capacity)
    {
        if(new_capacity == capacity) return;         //no change needed
        if(new_capacity < used) new_capacity = used; //need at least 'used' amount of space

        value_type *larger_array = new value_type[new_capacity]; //create new array
        std::copy(data, data + used, larger_array);              //copy data into array
        delete [] data;                                          //delete old data
        data = larger_array;                                     //point to new data
        capacity = new_capacity;                                 //update capacity
    }
    
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
        if(size() == capacity) resize(2*capacity); //if capacity is reached, make more room
        if(size() < capacity)
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
        if(size() == capacity) resize(2*capacity); //if capacity is reached, make more room
        if(size() < capacity)
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

    void sequence::operator=(const sequence& source)
    {
        if(this == &source) return;  //handle self assignment
        
        if(capacity != source.capacity)       //if capacity of rvalue/source sequence differs
            {
                value_type *new_data = new value_type[source.capacity]; //create source sized temp array
                delete [] data;                             //delete old data
                data = new_data;                            //set new array to data
                capacity = source.capacity;                 //set capacity to same as source
            }

        used = source.used;                               //update number of items
        current_index = source.current_index;
        std::copy(source.data, source.data + used, data); //copy source data into new allocation
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
