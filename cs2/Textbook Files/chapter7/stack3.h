// FILE: stack3.h (part of the namespace main_savitch_7A)
// TEMPLATE CLASS PROVIDED: stack<Item>
//
// TEMPLATE PARAMETER, TYPEDEFS and MEMBER CONSTANTS for the stack<Item> class:
//   The template parameter, Item, is the data type of the items in the stack,
//   also defined as stack<Item>::value_type. It may be any of the C++ built-in
//   types (int, char, etc.), or a class with a default constructor, a copy
//   constructor, and an assignment operator. The definition
//   stack<Item>::size_type is the data type of any variable that keeps track of
//   how many items are in a stack. The static const CAPACITY is the
//   maximum capacity of a stack for this first stack implementation.
// NOTE:
//   Many compilers require the use of the new keyword typename before using
//   the expressions stack<Item>::value_type and stack<Item>::size_type.
//   Otherwise the compiler doesn't have enough information to realize that it
//   is the name of a data type.
//
// CONSTRUCTOR for the stack<Item> template class:
//   stack( )
//     Postcondition: The stack has been initialized as an empty stack.
//
// MODIFICATION MEMBER FUNCTIONS for the stack<Item> class:
//   void push(const Item& entry)
//     Precondition: size( ) < CAPACITY.
//     Postcondition: A new copy of entry has been pushed onto the stack.
//
//   Item pop( )
//     Precondition: size( ) > 0.
//     Postcondition: The top item of the stack has been removed.
//
//   Item& top( )
//     Precondition: size( ) > 0.
//     Postcondition: The return value is a reference to the top item
//     of the stack but the stack is unchanged.
//
// CONSTANT MEMBER FUNCTIONS for the stack<Item> class:
//   bool empty( ) const
//     Postcondition: Return value is true if the stack is empty.
//
//   size_type size( ) const
//     Postcondition: Return value is the total number of items in the stack.
//
//   const Item& top( ) const
//     Precondition: size( ) > 0.
//     Postcondition: The return value is a const reference to the top item
//     of the stack but the stack is unchanged.
//
//  VALUE SEMANTICS for the stack<Item> class:
//     Assignments and the copy constructor may be used with stack<Item> 
//     objects.

#ifndef MAIN_SAVITCH_STACK3_H
#define MAIN_SAVITCH_STACK3_H
#include <cstdlib> // Provides size_t

namespace main_savitch_7A
{
    template <class Item>
    class stack
    {
    public:
        // TYPEDEFS AND MEMBER CONSTANT -- See Appendix E if this fails to compile.
        typedef std::size_t size_type;
        typedef Item value_type;
        static const size_type CAPACITY = 30;
        // CONSTRUCTOR
        stack( ) { used = 0; }
        // MODIFICATION MEMBER FUNCTIONS
        void push(const Item& entry);
        void pop( );
        Item& top( );
        // CONSTANT MEMBER FUNCTIONS
        bool empty( ) const { return (used == 0); }
        size_type size( ) const { return used; }
        const Item& top( ) const;
    private:
        Item data[CAPACITY];        // Partially filled array 
        size_type used;             // How much of array is being used
    };
}

#include "stack3.template" // Include the implementation.
#endif

