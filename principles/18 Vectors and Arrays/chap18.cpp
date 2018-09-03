#include "vect.h"
#include <vector>


//	Some notes
/*
	For copying
	class variable(data) is the same as 
	class variable = data when they are the same type
	so 
	vector v2 = v1; or
	vector v2(v1);
	also
	int one = 7;
	int one(7);

	For assigning
	there needs to be an operator=(const vector& a) defined first of it will point instead of assign

	Destructors are needed when resources are acquired, they have to be put back
	if a derived class needs a destructor, the base class needs a virtual destructor
	A class that needs a destructor, also needs a copy constructor and a copy assignment 
	due to the nature of shallow copies
*/

struct X		//test class
{
	int val;

	void out(const std::string& s)
	{
		std::cerr << this << "->" << s << ": " << val << "\n";
	}

	X() { out("X()"); val = 0; }					//default constructor
	X(int v) { out("X(int)"); val = v; }
	X(const X& x) { out("X(X&)"); val = x.val; }	//copy constructor
	X& operator=(const X& a)						//copy assignment
		{ out("X::operator=()"); val = a.val; return *this; }
	~X() { out("~X()"); }							//destructor
};

//X glob(2);											//a global variable
X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

void try_this1()
{
	std::cout << '\n';

	X loc(4);			//Creates a loc as X int, sets val = 4
	std::cout << '\n';

	X loc2 = loc;		//Creates a loc2 as X by calling copy contructor with X&, set val to 4
	std::cout << '\n';

	loc = X(5);			//Creates an X int with a val of 5, uses copy assignment to assign to loc, destroys X int
	std::cout << '\n';

	loc2 = copy(loc);	//puts 5 into copy(), copy's arguments create a X& with val 5, 
	std::cout << '\n';	//copy returns an X& with val 5, detroys the first X&, 
						//assigns 5 to loc2, then destroys the final X&


	loc2 = copy2(loc);	//puts 5 into copy2(), copy2's arguments create an X&(1),
	std::cout << '\n';	//copy2's function creates an X&(2) sets that val to 5, returns the object creating X&(3),
						//during the return, X&(2) is destroyed, followed by X&(1) destroyed,
						//the copy assignment is called, set loc2 val to 5, destroy X&(3)

	X loc3(6);			//Creates loc 3 as X int, with val 6
	std::cout << '\n';

	X&r = ref_to(loc);	//Creates a reference to loc, does not create an X
	std::cout << '\n';

	delete make(7);			//Creates X int with val 7, creates copy, function X int is destroyed, 
							//returns a pointer to the copy, deletes the copy
	std::cout << '\n';

	delete make(8);			//same as make(7)
	std::cout << '\n';

	std::vector<X> v(4);	//creates 4 X() defaulted to val 0
	std::cout << '\n';

	XX loc4;				//creates derived class loc4, which contains 2 X() defaulted to val 0
	std::cout << '\n';

	X* p = new X(9);		//creates X int with val 9, creates pointer p to point to x int
	std::cout << '\n';

	delete p;				//deletes object pointer p points to, destroying X int
	std::cout << '\n';

	X* pp = new X[5];		//creates an array of 5 X() defaulted to val 0, creates pointer pp to point to it
	std::cout << '\n';

	delete[] pp;			//deletes array pointer p points to, which destroys X()
	std::cout << '\n';
	
}

void try_this2() 
{
	vector v(10);
	v.set(2, 4);
	int x = v[2];
	v[3] = x;
}

/*	Arrays
	Arrays need [] to define the size always.
	double ad[10];
	double* p = &ad[5]; //creates a pointer to the 6th element in the array
	p += 2; can be moved to element 2 to the right.
	*p = 7 can be used to change the element it points to
	p[2] = 6; changes the element 2 to the right of p position

	char ac[] = "Beorn";
	creates an array ac with 6 elements, the last being a 0 (zero terminated)
	this is a c-style string
*/

//String palindromes
bool is_palindrome(const std::string& s)
{
	int first = 0;
	int last = s.length() - 1;
	while (first < last)
	{
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

void string_palindrome_test()
{
	std::cout << "Input a string to test for a palindrome, x to quit:\n";
	std::string s;
	while (std::getline(std::cin, s))
	{
		if (s == "x") break;
		std::cout << s << " is";
		if (!is_palindrome(s)) std::cout << " not";
		std::cout << " a palindrome\n";
	}
}

//char array palindromes
bool is_palindrome(const char s[], size_t n)
{
	//s points to the first char of an array of char's
	int first = 0;
	int last = n - 1;
	while (first < last)
	{
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

std::istream& read_word(std::istream& is, char* buffer, int max)
{
	//read at most max-1 characters from is into buffer
	is.width(max);	//read at most max-1 characters in the next >>
	is >> buffer;	//read whitespace-terminated word, add zero after the last character read into p

	return is;
}

void array_palindrome()
{
	std::cout << "Input a string to test for a palindrome:\n";
	const int max = 128;
	char s[max];
	while (read_word(std::cin, s, max))
	{
		std::cout << s << " is"; 
		if(!is_palindrome(s,strlen(s))) std::cout << " not";
		std::cout << " a palindrome\n";
	}
}

//pointer palindrome
bool is_palindrome(const char* first, const char* last)
{
	//first points to the first letter, last to the last letter
	while (first < last)
	{
		if (*first != *last) return false;	//compare the value that first and last consists of
		return is_palindrome(++first, --last);	//palindrome is a palindrome if the first and last characters are the same
									//and if you remove the first and last characters, the substring you get is a palindrome
	}
	return true;
}

void pointer_palindrome()
{
	std::cout << "Input a string to test for a palindrome:\n";
	const int max = 128;
	char s[max];
	while (read_word(std::cin, s, max))
	{
		std::cout << s << " is";
		if (!is_palindrome(&s[0], &s[strlen(s) - 1])) std::cout << " not";	//put the address of the first and last elements
		std::cout << " a palindrome\n";
	}
}

const int ga_count = 10;
int ga[ga_count] = { 1,2,4,8,16,32,64,128,256,512 };

void print_array(const int a[], int n)
{
	for (int i = 0; i < n; ++i) std::cout << "a[" << i << "] = " << a[i] << std::endl;
	std::cout << std::endl;
}

void f(int a[], int n)
{
	const int la_count = 10;
	int la[la_count];	//a

	for (int i = 0; i < la_count; ++i) la[i] = ga[i];	//b

	print_array(la, la_count);	//c

	int* p = new int[n];	//d

	for (int i = 0; i < n; ++i) p[i] = a[i];	//e

	print_array(p, n);	//f

	delete[] p;		//g

}

void drill_one()
{
	f(ga, ga_count);	//4a

	const int aa_count = 10;
	int aa[aa_count] = { 1 };

	for (int i = 1; i < aa_count; ++i) aa[i] = aa[i - 1] * (i + 1);	//4b

	f(aa, aa_count);	//4c
}

std::vector<int> gv;
void init_gv()
{
	for (int i = 0; i < 10; ++i)
	{
		if (i == 0) gv.push_back(1);
		else
			gv.push_back(gv[i - 1] * 2);
	}
}

void print_vec(const std::vector<int>& v)
{
	for(int i =0;i<v.size();++i) std::cout << "v[" << i << "] = " << v[i] << std::endl;
	std::cout << std::endl;
}

void f(std::vector<int> v)
{
	std::vector<int> lv(v.size());	//a

	lv = gv;	//b
	
	print_vec(lv);	//c

	std::vector<int> lv2 = v; //d           or lv2(v)

	print_vec(lv2);

}

void drill_two()
{
	init_gv();	//1

	f(gv);	//4a

	std::vector<int> vv;
	vv.push_back(1);
	for (int i = 1; i < 10; ++i) vv.push_back(vv[i - 1] * (i + 1)); //4b

	f(vv);
}

void keep_open()
{
	std::cout << "Press a key to exit\n";
	std::cin.clear();
	char ch;
	std::cin >> ch;
}
int main()
{
	try
	{
		drill_two();

		keep_open();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		keep_open();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Error unknown" << std::endl;
		keep_open();
		return 2;
	}
}