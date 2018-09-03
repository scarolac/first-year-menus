#include "Lines_Window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	color_menu(Point(x_max() - 80, 40), 70, 20, Menu::vertical, "color"),
	menu_button(Point(x_max() - 90, 20), 80, 20, "color menu", cb_menu),
	style_menu(Point(x_max() - 170, 40), 90, 20, Menu::vertical, "style"),
	style_button(Point(x_max() - 170, 20), 80, 20, "style menu", cb_style),
	next_button(Point(x_max() - 150, 0), 70, 20, "Next point", cb_next),
	quit_button(Point(x_max() - 80, 0), 70, 20, "Quit", cb_quit),
	next_x(Point(x_max() - 310, 0), 50, 20, "next x:"),
	next_y(Point(x_max() - 210, 0), 50, 20, "next y:"),
	xy_out(Point(100, 0), 100, 20, "current (x,y):")
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");

	color_menu.attach(new Button(Point(0, 0), 0, 0, "red", cb_red));
	color_menu.attach(new Button(Point(0, 0), 0, 0, "blue", cb_blue));
	color_menu.attach(new Button(Point(0, 0), 0, 0, "black", cb_black));
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);

	style_menu.attach(new Button(Point(0, 0), 0, 0, "solid", cb_solid));
	style_menu.attach(new Button(Point(0, 0), 0, 0, "dash", cb_dash));
	style_menu.attach(new Button(Point(0, 0), 0, 0, "dot", cb_dot));
	style_menu.attach(new Button(Point(0, 0), 0, 0, "dashdot", cb_dashdot));
	style_menu.attach(new Button(Point(0, 0), 0, 0, "dashdotdot", cb_dashdotdot));
	attach(style_menu);
	style_menu.hide();
	attach(style_button);

	attach(lines);	
}

void Lines_window::quit()
{
	hide();
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Point(x, y));

	//update the current position readout
	stringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_window::cb_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).menu_pressed();
}

void Lines_window::cb_style(Address,Address pw)
{
	reference_to<Lines_window>(pw).style_pressed();
}

void Lines_window::cb_next(Address, Address pw)
{
	reference_to<Lines_window>(pw).next();
}

void Lines_window::cb_quit(Address, Address pw)
{
	reference_to<Lines_window>(pw).quit();
}

void Lines_window::cb_red(Address, Address pw)
{
	reference_to<Lines_window>(pw).red_pressed();
}

void Lines_window::cb_blue(Address, Address pw)
{
	reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw)
{
	reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_solid(Address, Address pw)
{
	reference_to<Lines_window>(pw).solid_pressed();
}

void Lines_window::cb_dash(Address, Address pw)
{
	reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_dot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dot_pressed();
}

void Lines_window::cb_dashdot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dashdot_pressed();
}

void Lines_window::cb_dashdotdot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dashdotdot_pressed();
}

