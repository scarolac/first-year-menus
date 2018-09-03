#include "links.h"
/*
Link* Link::insert(Link* n)
{
	Link* p = this;					//pointer to this object
	if (n == 0) return p;			//test for 0's
	if (p == 0) return n;
	n->succ = p;					//p comes after n
	if (p->prev) p->prev->succ = n;	//if p has a predecessor, n comes after what used to be p's predecessor
	n->prev = p->prev;				//p's predecessor becomes n's predecessor
	p->prev = n;					//n becomes p's predecessor
	return n;
}

Link* Link::insert(Link* n)
{
	if (n == 0) return this;			//test for 0's
	if (this == 0) return n;
	n->succ = this;						//p comes after n
	if (this->prev) this->prev->succ = n;	//if p has a predecessor, n comes after what used to be p's predecessor
	n->prev = this->prev;				//p's predecessor becomes n's predecessor
	this->prev = n;						//n becomes p's predecessor
	return n;
}
*/
Link* Link::insert(Link* n)
{
	if (n == 0) return this;	//test for 0's
	if (this == 0) return n;
	n->succ = this;				//p comes after n
	if (prev) prev->succ = n;	//if p has a predecessor, n comes after what used to be p's predecessor
	n->prev = prev;				//p's predecessor becomes n's predecessor
	prev = n;					//n becomes p's predecessor
	return n;
}

Link* Link::add(Link* n)
{
	if (n == 0) return this;
	if (this == 0) return n;
	n->prev = this;
	if (succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

Link* Link::erase()		//remove *p (value that p points to) from list; return p's successor
{
	if (this == 0) return 0;
	if (succ) succ->prev = prev;	//if p has a successor, the successor's prev has to change to p's prev
	if (prev) prev->succ = succ;	//if p has a prev, the previous succ has to change to p's succ
	return succ;				//return the succ to the p (link) that is now erased
}

Link* Link::find(const std::string& s)
{
	Link* p = this;
	while (p)	//searches through pointers. stops when the first value is selected?
	{
		if (p->value == s) return p;
		p = p->succ;	//increments the search
	}
	return 0;	//not found
}

const Link* Link::find(const std::string& s) const
{
	const Link* p = this;
	while (p)	//searches through pointers. stops when the first value is selected?
	{
		if (p->value == s) return p;
		p = p->succ;	//increments the search
	}
	return 0;	//not found
}

Link* Link::advance(int n) const
{
	//move n positions in list, positive moves forward, negative moves backward
	Link* p = const_cast<Link*>(this);
	if (p == 0) return 0;	//if the list is empty

	if (0 < n)
	{
		while (n--)
		{
			if (p->succ == 0) return 0;	//if the list is only 1 item
			p = p->succ;	//move to the next item
		}
	}

	if (n < 0)
	{
		while (n++)
		{
			if (p->prev == 0) return 0;
			p = p->prev;	//move to the previous item
		}
	}
	return p;	//return the position
}

void print_all(Link* p)
{
	std::cout << "{";
	while (p)
	{
		std::cout << p->value;
		if (p = p->next()) std::cout << ", ";
	}
	std::cout << "}";
}
