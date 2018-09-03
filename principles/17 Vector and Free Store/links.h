#include <string>
#include <iostream>

/*	Links are used to build lists
	Links should have the following to build/modify a list:

	constructor
	insert: insert before and element
	add: insert after an element
	erase: remove an element
	find: find a link with a given value
	advance: get the nth successor

	These links build lists of strings
*/

struct Link
{
	std::string value;
	Link(const std::string& v, Link* p = 0, Link* s = 0)
		: value(v), prev(p), succ(s)
	{}
	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();
	Link* find(const std::string& s);
	const Link* find(const std::string& s) const;

	Link* advance(int n) const;

	Link* next() const { return succ; }
	Link* previous() const { return prev; }
private:
	Link* prev;
	Link* succ;

};

void print_all(Link* p);
