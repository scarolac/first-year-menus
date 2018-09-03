#ifndef LINES_WINDOW_GUARD
#define LINES_WINDOW_GUARD

#include "GUI.h"
#include "Graph.h"

using  namespace Graph_lib;

struct Lines_window : Window
{
	Lines_window(Point xy, int w, int h, const string& title);

private:
	//data
	Open_polyline lines;

	//widgets
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Menu color_menu;
	Button menu_button;
	Menu style_menu;
	Button style_button;

	void change_color(Color c) { lines.set_color(c); }

	void change_style(Line_style ls) { lines.set_style(ls); }

	void hide_color_menu() { color_menu.hide(); menu_button.show(); }

	void hide_style_menu() { style_menu.hide(); style_button.show(); }

	//actions invoked by callbacks
	void red_pressed() { change_color(Color::red); hide_color_menu(); }
	void blue_pressed() { change_color(Color::blue); hide_color_menu();	}
	void black_pressed() { change_color(Color::black); hide_color_menu();	}
	void menu_pressed() { menu_button.hide(); color_menu.show(); }

	void solid_pressed() { change_style(Line_style::solid); hide_style_menu(); }
	void dash_pressed() { change_style(Line_style::dash); hide_style_menu(); }
	void dot_pressed() { change_style(Line_style::dot); hide_style_menu(); }
	void dashdot_pressed() { change_style(Line_style::dashdot); hide_style_menu(); }
	void dashdotdot_pressed() { change_style(Line_style::dashdotdot); hide_style_menu(); }
	void style_pressed() { style_button.hide(); style_menu.show(); }

	void next();
	void quit();

	//callback functions
	static void cb_red(Address, Address);
	static void cb_blue(Address, Address);
	static void cb_black(Address, Address);
	static void cb_menu(Address, Address);

	static void cb_solid(Address, Address);
	static void cb_dash(Address, Address);
	static void cb_dot(Address, Address);
	static void cb_dashdot(Address, Address);
	static void cb_dashdotdot(Address, Address);
	static void cb_style(Address, Address);

	static void cb_next(Address, Address);
	static void cb_quit(Address, Address);

};

#endif // !LINES_WINDOW_GUARD

