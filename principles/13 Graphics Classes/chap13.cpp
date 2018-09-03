#include "Graph.h"
#include "Simple_window.h"

using namespace Graph_lib;

void lineGrid()
{
	Simple_window win(Point(100, 100), 640, 480, "GridTest");

	//get the size of the window
	int x_size = win.x_max();
	int y_size = win.y_max();

	//set the grid sizes
	int x_grid = 100;
	int y_grid = 100;

	Lines grid;
	for (int x = x_grid; x < x_size; x += x_grid)	//define x, add x_grid sizes until max window size reached on x axis
		grid.add(Point(x, 0), Point(x, y_size));	//lines go up and down, start at top go to bottom, x position is always x, y position is from 0 to y_size)
	for (int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point(0, y), Point(x_size, y));	//lines left and right, x is from 0 to x_size, y is always y

	win.attach(grid);

	grid.set_color(Color::blue);
	grid.set_style(Line_style::dashdot);

	win.wait_for_button();
}

void polyPratice()
{
	Simple_window win(Point(100, 100), 640, 480, "PolyPractice");

	Open_polyline opl;
	opl.add(Point(100, 100));
	opl.add(Point(150, 200));
	opl.add(Point(250, 250));
	opl.add(Point(300, 200));

	Closed_polyline cpl;
	cpl.add(Point(400, 100));
	cpl.add(Point(450, 200));
	cpl.add(Point(550, 250));
	cpl.add(Point(600, 200));

	Marked_polyline mpl("1234");
	mpl.add(Point(100, 150));
	mpl.add(Point(150, 250));
	mpl.add(Point(250, 300));
	mpl.add(Point(300, 250));


	win.attach(opl);
	win.attach(cpl);
	win.attach(mpl);
	win.wait_for_button();
}

void someRectangles()
{
	Simple_window win(Point(100, 100), 640, 480, "RECTANGLES");

	Graph_lib::Rectangle rect00(Point(150, 100), 200, 100);
	Graph_lib::Rectangle rect11(Point(50, 50), Point(250, 150));
	Graph_lib::Rectangle rect12(Point(50, 150), Point(250, 250));
	Graph_lib::Rectangle rect21(Point(250, 50), 200, 100);
	Graph_lib::Rectangle rect22(Point(250, 150), 200, 100);

	rect00.set_fill_color(Color::yellow);
	rect11.set_fill_color(Color::blue);
	rect12.set_fill_color(Color::red);
	rect21.set_fill_color(Color::green);

	rect00.set_color(Color::invisible);
	rect11.set_color(Color::invisible);
	rect12.set_color(Color::invisible);
	rect21.set_color(Color::invisible);
	rect22.set_color(Color::invisible);

	rect11.move(400, 0);
	rect11.set_fill_color(Color::white);
	
	win.attach(rect00);
	win.attach(rect11);
	win.attach(rect12);
	win.attach(rect21);
	win.attach(rect22);
	win.put_on_top(rect00);

	win.wait_for_button();
}

void colorMatrix()
{
	Simple_window win(Point(100, 100), 640, 480, "16 * 16 color matrix");

	Vector_ref<Graph_lib::Rectangle> vr;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			vr.push_back(new Graph_lib::Rectangle(Point(i * 20, j * 20), 20, 20));
			vr[vr.size() - 1].set_fill_color(i * 16 + j);
			win.attach(vr[vr.size() - 1]);
		}
	}
	

	win.wait_for_button();
}

void makeCircles()
{
	Simple_window win(Point(100, 100), 640, 480, "Circles");

	Circle c1(Point(100, 200), 50);
	Circle c2(Point(150, 200), 100);
	Circle c3(Point(200, 200), 150);

	Graph_lib::Ellipse e1(Point(500, 200), 50, 50);
	Graph_lib::Ellipse e2(Point(500, 200), 100, 50);
	Graph_lib::Ellipse e3(Point(500, 200), 100, 150);


	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(e1);
	win.attach(e2);
	win.attach(e3);
	win.wait_for_button();
}

void loadImage()
{
	Simple_window win(Point(100, 100), 640, 480, "Pictures");

	Image rita(Point(0, 0), "rita.jpg");
	Image path(Point(0, 0), "rita_path.gif");

	path.set_mask(Point(50, 250), 600, 400);	//cuts image down, loads from point

	win.attach(path);
	win.attach(rita);
	win.wait_for_button();
}

void drill()
{
	Simple_window win(Point(100, 100), 800, 1000, "Drilltime");

	//step 2, make an 800x800 grid with 100x100 squares
	int x_size = 800;
	int y_size = 800;

	int x_grid = 100;
	int y_grid = 100;

	Lines grid;
	for (int x = x_grid; x < x_size; x += x_grid)
		grid.add(Point(x, 0), Point(x, y_size));
	for (int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point(0, y), Point(x_size, y));

	win.attach(grid);

	//step 3, make rectangles taking up a diagonal of 8 squares
	Vector_ref <Graph_lib::Rectangle> eight;
	for (int i = 0; i < 8; ++i)
	{
		eight.push_back(new Graph_lib::Rectangle(Point(i*100, i*100), 100, 100));
		eight[i].set_fill_color(Color::red);
		win.attach(eight[i]);
	}
	
	//step 4, add 200x200 image in 3 places
	Image img1(Point(200, 0), "jet.jpg");
	img1.set_mask(Point(200, 0), 200, 200);
	Image img2(Point(0, 300), "jet.jpg");
	img2.set_mask(Point(200, 0), 200, 200);
	Image img3(Point(400, 200), "jet.jpg");
	img3.set_mask(Point(200, 0), 200, 200);
	win.attach(img1);
	win.attach(img2);
	win.attach(img3);

	//step 5, add 100x100 image, move from square to square when hitting next
	Image jump(Point(0, 0), "snow_cpp.gif");
	jump.set_mask(Point(30, 90), 100, 100);
	win.attach(jump);

	int y = 0;
	for (int i = 0; i < 64; ++i)
	{
		win.wait_for_button();			//wait for button, position is 0,0
		y += y_grid;					//push button, increment y by 100
		if (y > 700)				
		{
			y = 0;						//y > 700, set y to 0
			jump.move(x_grid, 0);		//move the x position by 100
			jump.move(0, -700);			//set y position back to 0
		}
		else
			jump.move(0, y_grid);		//increment y position by 100
	}
	
}

int main()
{
	try
	{
		drill();

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
		cerr << "Error unknown" << endl;
		keep_window_open("~~");
		return 2;
	}
}