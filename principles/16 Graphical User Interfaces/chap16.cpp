#include "Lines_Window.h"

int main()
{
	try
	{
		Lines_window win(Point(100, 100), 640, 480, "lines");
		return gui_main();
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Error unknown" << endl;
		return 2;
	}
}