// FILE: pqueue1.cxx
// First implementation of the priority queue, which stores items on a
// linked list. See pqueue1.h for complete specification.

#include <cassert>
#include <cstdlib>
#include <iostream>  
#include "pqueue1.h" 
using namespace std;

PriorityQueue::PriorityQueue( )
{
	many_nodes = 0;
	head_ptr = NULL;
}

PriorityQueue::PriorityQueue(const PriorityQueue& source)
{
	Node *source_cursor; 
	Node *my_cursor; 

	many_nodes = 0;
	head_ptr = NULL;
	if (source.many_nodes == 0)
		return;

	insert(source.head_ptr->data, source.head_ptr->priority);
	many_nodes = 1;

	my_cursor = head_ptr;
	source_cursor = source.head_ptr->link;
	while (source_cursor != NULL)
	{
		my_cursor->link = new Node;
		my_cursor = my_cursor->link;
		my_cursor->data = source_cursor->data;
		my_cursor->priority = source_cursor->priority;
		my_cursor->link = NULL;
		source_cursor = source_cursor->link;
	}
	many_nodes = source.many_nodes;
} 

PriorityQueue::~PriorityQueue( )
{
	Node *temp;

	while (head_ptr != NULL)
	{
		temp = head_ptr;
		head_ptr = head_ptr->link;
		delete temp;
	}
}

void PriorityQueue::operator =(const PriorityQueue& source)
{
	Node *source_cursor; 
	Node *my_cursor; 

	if (this == &source)
		return;

	while (many_nodes > 0)
		get_front( );

	if (source.many_nodes == 0)
		return;

	insert(source.head_ptr->data, source.head_ptr->priority);
	many_nodes = 1;

	my_cursor = head_ptr;
	source_cursor = source.head_ptr->link;
	while (source_cursor != NULL)
	{
		my_cursor->link = new Node;
		my_cursor = my_cursor->link;
		my_cursor->data = source_cursor->data;
		my_cursor->priority = source_cursor->priority;
		my_cursor->link = NULL;
		source_cursor = source_cursor->link;
	}
	many_nodes = source.many_nodes;
} 

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	Node *insert_ptr;
	Node *cursor; 

	insert_ptr = new Node;
	insert_ptr->data = entry;
	insert_ptr->priority = priority;

	if ((head_ptr == NULL) || (priority > head_ptr->priority))
	{   
		insert_ptr->link = head_ptr;
		head_ptr = insert_ptr;
	}
	else
	{   
		cursor = head_ptr;
		while ((cursor->link != NULL) && (cursor->link->priority >= priority))
			cursor = cursor->link;
		insert_ptr->link = cursor->link;
		cursor->link = insert_ptr;
	}
	many_nodes++;
}

PriorityQueue::Item PriorityQueue::get_front( )
{
	Item answer;
	Node *temp;

	assert(size( ) > 0);
	answer = head_ptr->data;
	temp = head_ptr;
	head_ptr = head_ptr->link;
	delete temp;
	many_nodes--;
	return answer;
} 
