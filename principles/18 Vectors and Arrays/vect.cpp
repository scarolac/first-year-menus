#include "vect.h"

vector::vector(int s) : sz(s), elem(new double[s])
{
	for (int i = 0; i < s; ++i)
		elem[i] = 0;
}

void vector::copy(const vector& arg)
{
	//copy elements [0:arg.sz-1]
	for (int i = 0; i < arg.sz; ++i) elem[i] = arg.elem[i];
}

double& vector::operator[](int n) { return elem[n]; }

double vector::operator[](int i) const { return elem[i]; }

vector::vector(const vector& arg) : sz(arg.sz), elem(new double[arg.sz]) 
{
	copy(arg);
}

/*	Trickyness
	When setting values of vectors = to each other: they will copy by default the members (shallow copy, copies what pointers point to)
	this operation tells it to make a new spot of the elements
	then to delete the old representation of the previously incorrectly pointed to section
	then point to the new area that was created
	and set the new size
	returning the value of the object since *type returns the value and type* creates a pointer
	(deep copy, copies what the values are that the pointers are pointing to)
*/
vector& vector::operator=(const vector& a)
{
	//make this vector a copy of a
	double* p = new double[a.sz];	//allocate new space
	copy(a);			//copy elements
	delete[] elem;		//deallocate old space
	elem = p;			//reset elem
	sz = a.sz;
	return *this;		//return a self reference 
}