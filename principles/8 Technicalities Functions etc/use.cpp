#include "my.h"
#include <iostream>
namespace X
{
	int var;
	void print()
	{
		std::cout << "X's var = " << var << std::endl;
	}
}
namespace Y
{
	int var;
	void print()
	{
		std::cout << "Y's var = " << var << std::endl;
	}
}
namespace Z
{
	int var;
	void print()
	{
		std::cout << "Z's var = " << var << std::endl;
	}
}


/*int main()
{
	foo = 7;

	print_foo();
	print(99);

	int x = 7;
	int y = 9;

	const int cx = 7;
	const int cy = 9;

	double dx = 7.7;
	double dy = 9.9;

	std::cout << "x = " << x << " y = " << y << std::endl;
	std::cout << "cx = " << cx << " cy = " << cy << std::endl;
	std::cout << "dx = " << dx << " dy = " << dy << std::endl;
	swap_v(dx,dy);
	std::cout << "x = " << x << " y = " << y << std::endl;


	char cc;
	std::cin >> cc;
}*/

int main()
{
	X::var = 7;
	X::print();		//print X's var
	using namespace Y;
	var = 9;
	print();		//print Y's var
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	print();
	X::print();

	char cc;
	std::cin >> cc;
}
