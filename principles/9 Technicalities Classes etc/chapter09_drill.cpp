#include <std_lib_facilities.h>
#include "Chrono.h"

void section941()
{
	using namespace Chrono941;
	cout << "Section 9.4.1\n";
	Date today;
	init_day(today, 1978, 6, 25);
	Date tomorrow = today;
	add_day(tomorrow, 1);
	cout << "Today is " << today << endl;
	cout << "Tomorrow is " << tomorrow << endl;
	//Date invalid;
	//init_day(invalid, 2004, 13, -5);
	//cout << "Invalid is " << invalid << endl;
}

void section942()
{
	using namespace Chrono942;
	cout << "Section 9.4.2\n";
	Date today(1978, 6, 25);
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << "Today is " << today << endl;
	cout << "Tomorrow is " << tomorrow << endl;
	//Date invalid(2004, 13, -5);
	//cout << "Invalid is " << invalid << endl;
}

void section943()
{
	using namespace Chrono943;
	cout << "Section 9.4.3\n";
	Date today(1978, 6, 25);
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << "Today is " << today << endl;
	cout << "Tomorrow is " << tomorrow << endl;
	//Date invalid(2004, 13, -5);
	//cout << "Invalid is " << invalid << endl;
}

void section971()
{
	using namespace Chrono971;
	cout << "Section 9.7.1\n";
	Date today(1978, jun, 25);
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << "Today is " << today << endl;
	cout << "Tomorrow is " << tomorrow << endl;
	//Date invalid(2004, jun, -5);
	//cout << "Invalid is " << invalid << endl;
}

void section974()
{
	using namespace Chrono974;
	cout << "Section 9.7.4\n";
	Date today(1978, jun, 25);
	cout << "Today is " << today << endl;
	Date tomorrow = today;
	tomorrow.add_day(205);
	//tomorrow.add_month(7);	
	cout << "Tomorrow is " << tomorrow << endl;
	//Date invalid(2004, jun, -5);
	//cout << "Invalid is " << invalid << endl;
}

int main()
{
	try
	{
		//the function to run
		section941();
		section942();
		section943();
		section971();			
		section974();

		//keeps window open to view the output
		keep_window_open();

		return 0;
	}
	catch (exception& e)
	{
		cerr << "exception: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown Exception\n" << endl;
		keep_window_open("~~");
		return 2;
	}
}