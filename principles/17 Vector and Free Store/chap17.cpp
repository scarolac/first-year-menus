//#include <std_lib_facilities.h>
#include "links.h"
#include <vector>

void keep_open()
{
	std::cout << "Press a key to exit\n";
	std::cin.clear();
	char ch;
	std::cin >> ch;
}

class vector
{
	int sz;
	double* elem;
public:
	vector(int s)
		:sz(s),
		elem(new double[s])
	{
		for (int i = 0; i < s; ++i)
			elem[i] = 0;
	}
	~vector() { delete[] elem; }
	int size() const { return sz; }

	double get(int n) { return elem[n]; }
	void set(int n, double v) { elem[n] = v; }
};

/*	Notes

The new operator returns a pointer to the allocated memory.
A pointer value is the address of the first byte of the memory.
A pointer points to an object of a specified type.
A pointer docs not know how many elements it points to.
Delete removes the pointer from memory
	
	int var = 17;	//stores var at some location in memory

	int* ptr = &var;	//ptr holds the address of var

	char ch = 'c';
	char* pc = &ch;		//pointer to char

	int ii = 17;
	int* pi = &ii;		//pointer to int

	*pc //shows the contents of pc, which contains the address of ch, which is holding 'c'

	*pi //show contents of pi, which contains the address of ii, which is holding 17

	(type)* is a pointer of that type, so int* is a pointer to int

	*(type) (dereference operator) is the contents of that type, so *(int* variable) shows the contents of where the address points to

	&(object) is the address of that type, on the initializer side, returns the address of the object

	(type)& is the reference of that type, points to the object to allow usage without chaging the type that is referenced

*/

void size_test()
{
	std::cout << "the size of char is " << sizeof(char) << std::endl;
	std::cout << "the size of int is " << sizeof(int) << std::endl;
	std::cout << "the size of int* is " << sizeof(int*) << std::endl;
	std::cout << "the size of bool is " << sizeof(bool) << std::endl;
	std::cout << "the size of double is " << sizeof(double) << std::endl;
	std::cout << "the size of string is " << sizeof(std::string) << std::endl;
}

void vector_test()
{
	vector v(5);
	for (int i = 0; i < v.size(); ++i)
	{
		v.set(i, 1.1 * i + 1);
		std::cout << "v[" << i << "] == " << v.get(i) << '\n';
	}
}

/*
void link_test_fails()
{
	Link* norse_gods = new Link("Thor");
	norse_gods = new Link("Odin", norse_gods);
	norse_gods->succ->prev = norse_gods;		//this does not work correctly, sets norse_gods to norse_gods?
	norse_gods = new Link("Freia", norse_gods);
	norse_gods->succ->prev = norse_gods;
	print_all(norse_gods);
	std::cout << std::endl;
	delete norse_gods;
}

void link_test()
{
	Link* norse_gods = new Link("Thor");
	norse_gods = insert(norse_gods, new Link("Odin"));
	norse_gods = insert(norse_gods, new Link("Freia"));
	print_all(norse_gods);
	std::cout << std::endl;
	delete norse_gods;
}


void list_use()
{
	Link* norse_gods = new Link("Thor");
	norse_gods = insert(norse_gods, new Link("Odin"));
	norse_gods = insert(norse_gods, new Link("Zeus"));
	norse_gods = insert(norse_gods, new Link("Freia"));
	print_all(norse_gods);
	std::cout << '\n';

	Link* greek_gods = new Link("Hera");
	greek_gods = insert(greek_gods, new Link("Athena"));
	greek_gods = insert(greek_gods, new Link("Mars"));
	greek_gods = insert(greek_gods, new Link("Posiedon"));
	print_all(greek_gods);
	std::cout << '\n';

	//Correct Mars into Ares
	Link* p = find(greek_gods, "Mars");
	if (p) p->value = "Ares";
	std::cout << "\n** Update Mars -> Ares\n";
	print_all(greek_gods);
	std::cout << '\n';

	//Remove Zeus from norse gods and place into greek gods
	p = find(norse_gods, "Zeus");
	if (p)
	{
		if (p == norse_gods) norse_gods = p->succ;	//check norse_gods is not pointing at p already
		erase(p);
		greek_gods = insert(greek_gods, p);	//assign the pointer to greek_gods
	}
	std::cout << "\n** Remove Zeus from Norse gods -> place into greek gods\n";
	print_all(norse_gods);
	std::cout << '\n';
	print_all(greek_gods);
	std::cout << '\n';
}
*/

void this_pointer()
{
	Link* norse_gods = new Link("Thor");
	norse_gods = norse_gods->insert(new Link("Odin"));
	norse_gods = norse_gods->insert(new Link("Zeus"));
	norse_gods = norse_gods->insert(new Link("Freia"));
	print_all(norse_gods);
	std::cout << '\n';

	Link* greek_gods = new Link("Hera");
	greek_gods = greek_gods->insert(new Link("Athena"));
	greek_gods = greek_gods->insert(new Link("Mars"));
	greek_gods = greek_gods->insert(new Link("Poseidon"));
	print_all(greek_gods);
	std::cout << '\n';

	//Correct Mars into Ares
	Link* p = greek_gods->find("Mars");
	if (p) p->value = "Ares";
	std::cout << "\n** Update Mars -> Ares\n";
	print_all(greek_gods);
	std::cout << '\n';

	//Remove Zeus from norse gods and place into greek gods
	Link* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2 == norse_gods) norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->insert(p2);
	}
	std::cout << "\n** Remove Zeus from Norse gods -> place into greek gods\n";
	print_all(norse_gods);
	std::cout << '\n';
	print_all(greek_gods);
	std::cout << '\n';
}

//4
void print_array10(std::ostream& os, int* a)
{
	for (int i = 0; i < 10; ++i)
	{
		os << "a[" << i << "] == " << a[i] << std::endl;
	}
}

//7
void print_array(std::ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		os << "a[" << i << "] == " << a[i] << std::endl;
	}
}

//10
void print_vector(std::ostream& os, std::vector<int> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		os << "v[" << i << "] == " << v[i] << std::endl;
	}

}

void drill_one()
{
	//1, 2, 3
	std::cout << "Numbers 1, 2 and 3" << std::endl;
	int* ten_ints = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		ten_ints[i] = i + 1;
		std::cout << "ten_ints[" << i << "] == " << ten_ints[i] << std::endl;
	}
	delete[] ten_ints;

	//5
	std::cout << "\nNumber 5" << std::endl;
	int* number5 = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		number5[i] = 100 + i;
	}
	print_array10(std::cout, number5);
	delete[] number5;

	//6
	std::cout << "\n*** 6 ***" << std::endl;
	int* number6 = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		number6[i] = 100 + i;
	}
	print_array10(std::cout, number6);
	delete[] number6;

	//8
	std::cout << "\n*** 8 ***" << std::endl;
	int* twenty = new int[20];
	for (int i = 0; i < 20; ++i)
	{
		twenty[i] = 100 + i;
	}
	print_array(std::cout, twenty,20);
	delete[] twenty;
	
	//9, yes i deleted the arrays

	//10 vectors 
	std::cout << "\n*** 10 ***" << std::endl;
	std::vector<int> vec_ten;
	std::vector<int> vec_eleven;
	std::vector<int> vec_twenty;

	for (int i = 0; i < 10; ++i) vec_ten.push_back(100 + i);
	for (int i = 0; i < 11; ++i) vec_eleven.push_back(100 + i);
	for (int i = 0; i < 20; ++i) vec_twenty.push_back(100 + i);

	print_vector(std::cout, vec_ten);
	std::cout << "\n";
	print_vector(std::cout, vec_eleven);
	std::cout << "\n";
	print_vector(std::cout, vec_twenty);
}

void drill_two()
{
	//1-2
	std::cout << "*** 2 ***" << std::endl;
	int one = 7;
	int* p1 = &one;
	std::cout << "one = " << one << " p1 = " << p1 << std::endl;
	
	//3-4
	std::cout << "\n*** 4 ***" << std::endl;
	int* p2 = new int[7];
	for (int i = 0; i < 7; ++i)
	{
		if (i == 0) p2[i] = 1;
		else
			p2[i] = p2[i - 1] * 2;
	}

	std::cout << "p2 = " << p2 << std::endl;
	print_array(std::cout, p2, 7);

	//5-8
	std::cout << "\n*** 8 ***" << std::endl;
	int* p3 = p2;
	p2 = p1;
	p2 = p3;
	std::cout << "p1 = " << p1 << " p2 = " << p2 <<std::endl;

	//9
	p1 = 0;
	delete[] p2;
	p3 = 0;

	//10
	std::cout << "\n*** 10 ***" << std::endl;
	p1 = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		if (i == 0) p1[i] = 1;
		else
			p1[i] = p1[i - 1] * 2;
	}
	print_array10(std::cout, p1);

	//11
	p2 = new int[10];

	//12
	std::cout << "\n*** 12 ***" << std::endl;
	for (int i = 0; i < 10; ++i) p2[i] = p1[i];
	print_array10(std::cout, p2);

	//13
	std::cout << "\n*** 13 ***" << std::endl;
	std::vector<int> vp1(10);
	std::vector<int> vp2(10);

	for (int i = 0; i < vp1.size(); ++i)
	{
		if (i == 0) vp1[i] = 1;
		else
			vp1[i] = vp1[i - 1] * 2;
		vp2[i] = vp1[i];
	}
	print_vector(std::cout, vp1);
	std::cout << std::endl;
	print_vector(std::cout, vp2);
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