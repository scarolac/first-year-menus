#include "Graph.h"
#include "Simple_window.h"

using namespace Graph_lib;

int main()
{
	try
	{
		Point tl(100, 100);

		Simple_window win(tl, 600, 400, "My Window");

		//Make object, adjust settings, add to window
		Axis xa(Axis::x, Point(20, 300), 280, 10, "x axis");
			//Axis::x is horizontal, starts at 20,300, 280 pixels long, 10 notches
		win.attach(xa);					//attach xa to the window

		Axis ya(Axis::y, Point(20, 300), 280, 10, "y axis");
		ya.set_color(Color::cyan);
		ya.label.set_color(Color::dark_red);
		win.attach(ya);

		Function sine(sin, 0, 100, Point(20, 150), 1000, 50, 50);	
		//range 0:100, 0,0 is at 20,150, using 100 points, scale x and y values * 50
		win.attach(sine);

		sine.set_color(Color::blue);

		Graph_lib::Polygon poly;		//there is a Polygon in std I think, Graph_lib has to be used here because std lib facilities is used in window.h making namespace std and Graph_lib active
		poly.add(Point(300, 200));
		poly.add(Point(350, 100));
		poly.add(Point(400, 200));
		poly.set_color(Color::red);
		poly.set_style(Line_style::dash);
		win.attach(poly);

		Graph_lib::Rectangle r(Point(200, 200), 100, 50);
		win.attach(r);

		Closed_polyline poly_rect;		//makes a connected box, not real shapes
		poly_rect.add(Point(100, 50));		//start here
		poly_rect.add(Point(200, 50));		//connect down to second point
		poly_rect.add(Point(200, 100));		//then go right to 3rd point
		poly_rect.add(Point(100, 100));		//4th point above previous and to the right of first point
		poly_rect.add(Point(50, 75));	//prove it is not an actual rectangle object, just something that looks like it
		win.attach(poly_rect);

		//Fill and adjust settings
		r.set_fill_color(Color::yellow);
		poly.set_style(Line_style(Line_style::dash, 4));
		poly_rect.set_style(Line_style(Line_style::dash, 2));
		poly_rect.set_fill_color(Color::dark_green);

		//Text object
		Text t(Point(150, 150), "Hello graphics ");
		win.attach(t);

		t.set_font(Font::times_bold);
		t.set_font_size(20);

		//Image
		Image ii(Point(100, 350), "image.jpg");
		win.attach(ii);

		ii.move(100, -100);	//does not set a location, moves by an amount of original x + new x, same for y

		//more stuff
		Circle c(Point(100, 200), 50);
		Graph_lib::Ellipse e(Point(100, 200), 75, 25);
		e.set_color(Color::dark_red);
		Mark m(Point(100, 200), 'x');

		ostringstream oss;
		oss << "screen size: " << x_max() << " * " << y_max()
			<< "; window size: " << win.x_max() << " * " << win.y_max();

		Text sizes(Point(200, 40), oss.str());

		Image cal(Point(225, 225), "snow_cpp.gif");
		cal.set_mask(Point(40, 40), 200, 150);

		cal.move(200, -150);

		win.attach(c);
		win.attach(e);
		win.attach(m);
		//win.attach(sizes);
		win.attach(cal);

		win.set_label("My Window KEEPS CHANGING");	//relabel the window
		win.wait_for_button();
	}
	catch (exception& e)
	{
		cout << "error: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cout << "unknown error" << endl;
		keep_window_open("~~");
		return 2;
	}

}