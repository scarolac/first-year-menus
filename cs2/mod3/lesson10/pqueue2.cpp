// Section CSC161 - Computer Science II: C++
// File Name: pqueue2.cpp
// Student: Chris Scarola
// Homework Number: 10
// Last Changed: 04/16/2017
// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.
 
#include <cassert>    // Provides assert function
#include <iostream>  // Provides cin, cout
#include <iomanip>   // Provides setw
#include <cmath>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue()
{
    many_items = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
    if(many_items != CAPACITY)
        {
            
            
            if(many_items == 0)
                {
                    heap[many_items].data = entry;
                    heap[many_items].priority = priority;
                    ++many_items;
                }
            else
                {
                    size_t i = many_items;
                    
                    heap[i].data = entry;
                    heap[i].priority = priority;
                    ++many_items;                    
                    
                    while(parent_priority(i) < priority)
                        {
                            swap_with_parent(i);
                            i = parent_index(i);
                        }                       
                    
                }                      
        }   
}

PriorityQueue::Item PriorityQueue::get_front( )
{   //remove root, replace with last item, filter it down

    if(many_items > 0)
        {         
            if(many_items == 1)
                {
                    --many_items;        //show size smaller
                    return heap[0].data; //get root data
                }
            else
                {
                    Item front = heap[0].data;    //store first item
                    heap[0] = heap[many_items-1]; //set last item into root slot
                    heap[many_items-1].data = 0;
                    heap[many_items-1].priority = 0;

                    size_t i = 0;
                    while(big_child_priority(i) > heap[i].priority)
                        {
                            swap_with_parent(big_child_index(i));
                            i = big_child_index(i);
                        }
                    
                    --many_items;
                    return front;
                    
                }
        }
    else return 0;
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
    if(i < many_items)
        return ((2*i)+1 > (many_items - 1));
    else return false;
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
    if(i > 0 && i < many_items) return (i-1)/2;
    else return 0;        
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
    if(i < many_items)
        return heap[parent_index(i)].priority;
    else return UINT32_MAX;
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
    if(!is_leaf(i))
        {
            //2i+1 left child, 2i+2 right child
            if(heap[(2*i)+1].priority > heap[(2*i)+2].priority)
                return (2*i)+1;
            else
                return (2*i)+2;

            return (2*i)+1;  //return if only 1 child
        }   
    else return UINT64_MAX;
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
    if(!is_leaf(i))
        return heap[big_child_index(i)].priority;
    else return 0;
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
    OneItemInfo temp = heap[parent_index(i)]; //store parent
    heap[parent_index(i)] = heap[i];          //set parent
    heap[i] = temp;                           //restore temp
}

void PriorityQueue::print_tree(const char message[ ], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses i=0, which prints the whole tree.
{
    if(many_items > 0)
        {
            if(i > many_items)
                {
                    cout << "out of range" << endl;
                    return;
                }
            else
                {
                    cout << message << endl;
                    size_t depth;

                    depth = (i+1)/2;
                    cout << setw(depth * 4);
                    
                    cout << heap[i].data << " (priority " << heap[i].priority << ")";
                    
                    if(2*i+1 < many_items) print_tree("", 2*i+1); //print the left children
                       
                    if(2*i+2 < many_items) print_tree("", 2*i+2); //print the right children
                       
                }          
                          
        }
    else
        cout << message << " no items" << endl;
}
