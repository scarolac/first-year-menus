#include <std_lib_facilities.h>
/*
namespace Chapter20
{
	//copy f2 into f1, with f1 ending at e1
	void copy(int* f1, int* e1, int* f2)
	{
		while (f1 != e1)
		{
			*f2 = *f1;
			++f1;
			++f2;
		}
	}

	//finds the high() using iterators so all types can be used istead of just double
	template <class Iterator> Iterator high(Iterator first, Iterator last)
	{
		//return an iterator to the element in [first:last) that has the highest value

		Iterator high = first;
		for (Iterator p = first; p != last; ++p)
		{
			if (*high < *p)
			{
				high = p;
				*high = *p;
			}
			return high;
		}
	}

	//Links and list
	template<class Elem> struct Link
	{
		Link* prev;
		Link* succ;
		Elem val;
	};
	/*
	template<class Elem> struct list
	{
	Link<Elem>* first;
	Link<Elem>* last;
	};
	

	//list class
	template<class Elem> class list
	{
	public:
		class Link;
		typedef unsigned long size_type;
		typedef Elem value_type;
		class iterator;		//member type: iterator
		class const_iterator;

		iterator begin();	//iterator to the first element
		const_iterator begin() const;
		iterator end();		//iterator to on beyond the last element
		const_iterator end() const;

		size_type size();

		iterator insert(iterator p, const Elem& v);	//insert v into list after p
		iterator erase(iterator p);					//remove p from list

		void push_back(const Elem& v);		//insert v at end
		void push_front(const Elem& v);		//insert v at front
		void pop_front();		//remove the first element
		void pop_back();		//remove the last element

		Elem& front();		//the first element
		Elem& back();		//the last element
	};
	/*
	template<class Elem> class list<Elem>::iterator
	{
		Link<Elem>* curr;	//current link
	public:
		iterator(Link* p) : curr(p) {}

		iterator& operator++() { curr = curr->succ; return *this; }	//forward
		iterator& operator--() { curr = curr->prev; return *this; }	//backward

		Elem& operator*() { return val; }	//get value (dereference)

		bool operator==(const iterator& b) const { return curr == b.curr; }
		bool operator!=(const iterator& b) const { return curr != b.curr; }
	};
	/*
	void f()
	{
	list<int> lst;
	int x;
	while (std::cin >> x) lst.push_front(x);

	list<int>::iterator p = high(lst.begin(), lst.end());
	if (p == lst.end())	//did we reach the end?
	std::cout << "The list is empty\n";
	else
	std::cout << "The highest value is " << *p << std::endl;
	}
	

	//Generalizing Vector
	template<class T> class vector
	{
	public:
		/*	typedef
		creates an alias for a type
		ex: iterator is another name for the pointer of T*
		size_type stores the size as an unsigned long

		can be used as:
		vector<int>::iterator p = find(v.begin(),v.end(),32);
		and
		for(vector<int>::size_type i = 0; i < v.size(); ++i) std::cout << v[i] << std::endl;
		
		
		typedef unsigned long size_type;
		typedef T value_type;
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin();
		const_iterator begin() const;

		size_type size();
	};
}

//Text Editor
typedef vector<char> Line;

struct Document
{
	Chapter20::list<Line> line;	//a Document is a list of lines, line[i] is the i'th line

	Document() { line.push_back(Line()); }
	//Line() calls the default constructor of vector, creating an empty vector of char's, due to the typedef above

//	Text_iterator begin() { return Text_iterator(line.begin(), (*line.begin()).begin()); }
	//Text_iterator end() { return Text_iterator(line.end(), (*line.end()).end()); }
};

istream& operator >> (istream& is, Document& d)
{
	char ch;
	while (is >> ch)
	{
		d.line.back().push_back(ch);	//add the character to the back
		if (ch == '\n')
			d.line.push_back(Line());	//add another line
	}
	return is;
}

class Text_iterator		//keep track of line and character position within a line, similar to (x,y) coords
{
	list<Line>::iterator ln;	//uses the iterator created for line
	Line::iterator pos;			//uses the iterator that std::vector contains
public:
	//start the iterator at line ll's character posistion pp:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln(ll), pos(pp) {}

	char& operator*() { return *pos; }	//returns reference to the value of the char located at pos
	Text_iterator& operator++();

	bool operator==(const Text_iterator& other) const { return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const { return !(*this == other); }
};

Text_iterator& Text_iterator::operator++()
{
	if (pos == (*ln).end())		//*ln shows the line that the iterator points at
	{
		++ln;
		pos = (*ln).begin();
	}
	++pos;
	return *this;				//return *this to update where the Text_iterator object is pointing to
}

void print(Document& d)
{
	//for (Text_iterator p = d.begin(); p != d.end(); ++p) cout << *p;
}

template<class Iter> Iter advance(Iter p, int n)
{
	if (n < 0)
		while (n < 0) { --p; ++n; }
	else if (n > 0)
		while (n > 0) { ++p; --n; }
	return p;
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.line.size() <= n) return;	//ignore out of range
	d.line.erase(advance(d.line.begin(), n));
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;
	char first_char = s[0];
	while (true)
	{
		Text_iterator p = find(first, last, first_char);	//finds first_char in the range of the document
	//	if (p == last || match(p, last, s)) return p;		//if it finds a match, or reaches the end, return the location
	}
}
*/