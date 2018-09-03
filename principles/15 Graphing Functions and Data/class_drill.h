#include <std_lib_facilities.h>

#ifndef CLASS_DRILL
#define CLASS_DRILL

struct Person
{
	Person() : fn(""), sn(""), a(0) {}
	Person(string n1, string n2, int a);

	string first_name() const { return fn; }
	string second_name() const { return sn; }

	int age() const { return a; }
private:
	string fn;
	string sn;
	int a;	
};

bool operator==(const Person& a, const Person& b);

bool operator!=(const Person& a, const Person& b);

istream& operator>>(istream& is, Person& p);

ostream& operator<<(ostream& os, const Person& p);


#endif // !CLASS_DRILL
