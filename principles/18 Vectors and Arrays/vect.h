#include <iostream>
#include <string>

#ifndef VECT_GUARD
#define VECT_GUARD

class vector
{
	int sz;
	double* elem;

	void copy(const vector& arg);

public:
	explicit vector(int s);		//explicit prevents vector v = 10 from creating a vector holding 10 doubles, forces vector v(10) to be used.

	~vector() { delete[] elem; }

	int size() const { return sz; }

	double get(int n) { return elem[n]; }
	double& operator[](int n);		//returns a reference, if v[i] = x, x will assign over that reference updating the value
	double operator[](int i) const;	//used for const vectors to return a value and not modify

	void set(int n, double v) { elem[n] = v; }

	vector(const vector&);

	vector& operator=(const vector& a);
};

#endif // !VECT_GUARD

