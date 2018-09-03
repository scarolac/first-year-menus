#include "class_drill.h"

Person::Person(string n1, string n2, int a)
	:fn(n1),sn(n2),a(a)
{


	if (a < 0 || 150 < a) error("age out of range [0:150]");
	
	//check bad characters
	const string bad_chars = ";:\"'[]*&^%$#@!";
	for (unsigned int i = 0; i < fn.size(); ++i)
	{
		for (unsigned int j = 0; j < bad_chars.size(); ++j)
		{
			if (fn[i] == bad_chars[j]) error("Illegal character: ", string(1,bad_chars[j]));
		}
		if (!isalpha(fn[i])) error("invalid first name");
	}
	for (unsigned int i = 0; i < sn.size(); ++i)
	{
		for (unsigned int j = 0; j < bad_chars.size(); ++j)
		{
			if (sn[i] == bad_chars[j]) error("Illegal character: ", string(1, bad_chars[j]));
		}
		if (!isalpha(sn[i])) error("invalid second name");
	}

}

bool operator==(const Person& a, const Person& b)
{
	return a.age() == b.age()
		&& a.first_name() == b.first_name()
		&& a.second_name() == b.second_name();
}

bool operator!=(const Person& a, const Person& b)
{
	return !(a == b);
}

istream& operator>>(istream& is, Person& p)
{
	string f_name;
	string s_name;
	int age;
	
	is >> f_name >> s_name >> age;
	if (!is) return is;

	p = Person(f_name, s_name, age);

	return is;
}

ostream& operator<<(ostream& os, const Person& p)
{
	return os << p.first_name() << ' ' << p.second_name()
		<< " is " << p.age() << " years old.";
}