#include <std_lib_facilities.h>

int main()
{
	try
	{
		cout << "success!\n";
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << endl;
		keep_window_open();
		return 1;
	} 
	catch (...)
	{
		cerr << "Opps: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}




