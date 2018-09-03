#include <std_lib_facilities.h>

class B1
{
public:
	virtual void pvf() = 0;

	virtual void vf();

	void f();
};

class D1 : public B1
{
public:
	virtual void pvf();

	void vf();

	void f();
};

class D2 : public D1
{
public:
	void pvf();
};

class B2
{
public:
	virtual void pvf() = 0;
};

class D21 : public B2
{
public:
	string s;

	void pvf();
};

class D22 : public B2
{
public:
	int i;

	void pvf();
};