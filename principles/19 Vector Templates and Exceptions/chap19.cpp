#include <iostream>
#include <vector>
#include "vect.h"

template<class T> struct S
{
	S() : val(T())	{}
	S(T v) : val(v)	{}

	T& get();
	const T& get() const;
	void set(const T& v);

	T& operator=(const T& v);
	
private:
	T val;
};

template<class T> T& S<T>::get() { return val; }
template<class T> const T& S<T>::get() const { return val; }
template<class T> void S<T>::set(const T& v) { val = v; }

template<class T> T& S<T>::operator=(const T& v) 
{ 
	val = v;
	return val; 
}

template<class T> std::istream& operator >> (std::istream& is, S<T>& ss)
{
	T v;
	std::cin >> v;
	if (!is) return is;

	ss = v;
	return is;
}

template<class T> void read_val(T& v)
{
	std::cin >> v;
}

template<class T> std::ostream& operator<<(std::ostream& os, std::vector<T>& vt)
{
	os << "{ ";
	for (int i = 0; i < vt.size(); ++i)
	{
		os << vt[i];
		if (i < vt.size() - 1) os << ",";
		os << ' ';
	}
	os << "}";
	return os;
}

template<class T> std::istream& operator>>(std::istream& is, std::vector<T>& vt)
{
	char ch1;
	char ch2;
	T temp;
	std::vector<T> vtemp;
	is >> ch1;
	if (!is) return is;

	if (ch1 != '{')
	{
		is.clear(std::ios_base::failbit);
		return is;
	}

	while (std::cin >> temp >> ch2 && ch2 == ',')
	{
		vtemp.push_back(temp);
	}

	if (ch2 != '}')
	{
		is.clear(std::ios_base::failbit);
		return is;
	}

	vtemp.push_back(temp); //read the last temp since the while will fail after reading ch2

	vt = vtemp;	//copy at the end in case is fails
}

void drill()
{
	S<int> in;
	in.set(1);
	S<char> ch = 'b';
	S<double> dou = 3.3;
	S<std::string> str = "test";

	std::vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);

	S<std::vector<int>> s_vec(vi);

	/*
	std::cout << "in = " << in.val << std::endl;
	std::cout << "ch = " << ch.val << std::endl;
	std::cout << "dou = " << dou.val << std::endl;
	std::cout << "str = " << str.val << std::endl;
	for (int i = 0; i < s_vec.val.size(); ++i)
		std::cout << "s_vec[" << i << "] = " << s_vec.val[i] << std::endl;
	*/

	std::cout << "in = " << in.get() << std::endl;
	std::cout << "ch = " << ch.get() << std::endl;
	std::cout << "dou = " << dou.get() << std::endl;
	std::cout << "str = " << str.get() << std::endl;
	for (int i = 0; i < s_vec.get().size(); ++i)
		std::cout << "s_vec[" << i << "] = " << s_vec.get()[i] << std::endl;

	std::cout << "\nin = ";
	read_val(in);
	std::cout << "ch = ";
	read_val(ch);
	std::cout << "dou = ";
	read_val(dou);
	std::cout << "str = ";
	read_val(str);
	std::cout << "in = " << in.get() << std::endl;
	std::cout << "ch = " << ch.get() << std::endl;
	std::cout << "dou = " << dou.get() << std::endl;
	std::cout << "str = " << str.get() << std::endl;

	std::cout << "s_vec = ";
	read_val(s_vec);
	std::cout << "s_vec = " << s_vec.get() << std::endl;
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
		drill();

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

