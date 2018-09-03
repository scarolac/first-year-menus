#include <iostream>
#include <string>

#ifndef VECT_GUARD
#define VECT_GUARD

template<class T, class A = std::allocator<T>> class vector
{
	A alloc;		//used to manage uninitialized type T's that are used
	/*	invariant
			for 0<=n<sz elem[n] is element n
			sz <= space
			if sz <space tere is space for (space - sz) doubles after elem[sz-1]
	*/

	int sz;			//number of elements
	T* elem;		//address of first element
	int space;		//number of elements plus "free space" for new elements

	void copy(const vector& arg);

public:
	vector() : sz(0),elem(0),space(0)	{}	//default construtor

	explicit vector(int s);		//explicit prevents vector v = 10 from creating a vector holding 10 doubles, forces vector v(10) to be used.
	
	vector(const vector&);				//copy constructor
	vector& operator=(const vector& a);	//copy assignment

	~vector() { delete[] elem; }		//destructor
		
	T& at(int n);				//checked access, can also modify
	const T& at(int n) const;	//cannot modify

	T& operator[](int n);					//unchecked access
	const T& operator[](int n) const;		//unchecked access
		
	int size() const { return sz; }
	int capacity() const { return space; }	//amount of space before reallocation is needed with reserve

	void resize(int newsize, T def = T());	//growth
	void push_back(const T& val);
	void reserve(int newalloc);
};

template<class T, class A> vector<T, A>::vector(int s) : sz(s), elem(new double[s])
{
	for (int i = 0; i < s; ++i)
		elem[i] = 0;
}

//copy, assign
template<class T, class A> void vector<T, A>::copy(const vector& arg)
{
	//copy elements [0:arg.sz-1]
	for (int i = 0; i < arg.sz; ++i) elem[i] = arg.elem[i];
}
template<class T, class A> vector<T, A>::vector(const vector& arg) : sz(arg.sz), elem(new double[arg.sz])
{
	copy(arg);
}
/*	Trickyness - copy assignment
When setting values of vectors = to each other: they will copy by default the members (shallow copy, copies what pointers point to)
this operation tells it to make a new spot of the elements
then to delete the old representation of the previously incorrectly pointed to section
then point to the new area that was created
and set the new size
returning the reference to the object since *this returns the reference
(deep copy, copies what the values are that the pointers are pointing to)
*/
template<class T, class A> vector<T, A>& vector<T, A>::operator=(const vector& a)
{
	//make this vector a copy of a
	if (this == &a) return *this;	//self assignment, no change

	if (a.sz <= space)	//enough space, no need to allocate
	{
		for (int i = 0; i < a.sz; ++i) elem[i] = a.elem[i];	//copy elements
		sz = a.sz;
		return *this;
	}

	double* p = new double[a.sz];	//allocate new space
	copy(a);			//copy elements
	delete[] elem;		//deallocate old space
	space = sz = a.sz;	//set new size
	elem = p;			//set new elements
	return *this;		//return a self reference 
}

//ranged access, when bounds are unknown
struct out_of_range {};
template<class T, class A> T& vector<T, A>::at(int n)
{
	if (n < 0 || sz < n) throw out_of_range();
	return elem[n];
}
template<class T, class A> const T& vector<T, A>::at(int n) const
{
	if (n < 0 || sz < n) throw out_of_range();
	return elem[n];
}

//access and setting, when bounds are known
template<class T, class A> T& vector<T, A>::operator[](int n) 
{ 
	return elem[n]; 
}
template<class T, class A> const T& vector<T, A>::operator[](int n) const 
{ 
	return elem[n]; 
}

//allocate space, handle uninitialized
template<class T, class A>void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;		//never decrease allocation
	auto_ptr<T> p (alloc.allocate(newalloc));	//allocate new space based on size of T objects
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);	//copy current element pointers into new space
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);			//destroy old objects
	alloc.deallocate(elem,space);		//deallocate old space
	elem = p.release();					//set new elem to p	that holds the old elements, making them current elements
	space = newalloc;					//grow the space
}

template<class T, class A> void vector<T, A>::push_back(const T& val)
{
	//increase vector size by one, initialize new element with d
	if (space == 0) reserve(8);					//start with space for 8 elements
	else if (sz == space) reserve(2 * space);	//get more space
	alloc.construct(&elem[sz],val);				//add val at the end
	++sz;										//increase the size
}

template<class T, class A> void vector<T, A>::resize(int newsize, T def = T())
{
	//make the vector have newsize elements, initialize each element with default value 0.0
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i],def);	//construct default T objects at the elem[i] address
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);			//destroy excess objects
	sz = newsize;			//set new sz, if newsize is smaller, it will chop off the rest 
}
#endif // !VECT_GUARD

