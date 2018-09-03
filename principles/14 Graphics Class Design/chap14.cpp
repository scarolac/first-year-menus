#include "drill.h"
/*
void number1()
{
	cout << "number 1" << endl;
	B1 b;
	b.vf();
	b.f();
}
*/

void number2()
{
	cout << "number 2" << endl;
	D1 d;

	d.vf();
	d.f();
}

void number3()
{
	cout << "number 3" << endl;
	D1 d;
	d.vf();
	d.f();

	B1& br = d;
	br.vf();
	br.f();
}

void number5()
{
	cout << "number 5" << endl;
	D1 d;
	d.pvf();
	d.vf();
	d.f();

	B1& br = d;
	br.pvf();
	br.vf();
	br.f();
}

void number6()
{
	cout << "number 6" << endl;
	D2 d;

	d.pvf();
	d.vf();
	d.f();
}

void f(B2& b)
{
	b.pvf();
}

void number7()
{
	D21 d1;
	D22 d2;
	d1.s = "fast";
	d2.i = 12;

	f(d1);
	f(d2);

}

int main()
{
	try
	{
		number7();
			
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;
		keep_window_open("~~");
		return 2;
	}
}