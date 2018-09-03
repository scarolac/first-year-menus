//#include "Graph.h"
//#include "Simple_window.h"
#include "class_drill.h"

/*
	change subsystem under linker to Windows to allow the graphs to be drawn
*/
/*
double one(double) { return 1; }

double slope(double x) { return x / 2; }

double square(double x) { return x*x; }

double sloping_cos(double x) { return cos(x) + slope(x); }

void simplefunctions()
{
	const int xmax = 640;			//window size
	const int ymax = 480;

	const int x_orig = xmax / 2;	//position of 0,0 is the center of window
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	const int r_min = -10;			//range [-10:10]
	const int r_max = 10;

	const int n_points = 400;		//number of points used in range

	const int x_scale = 30;			//scaling factors
	const int y_scale = 30;

	const int xlength = xmax - 40;	//make the axis a bit smaller than the window
	const int ylength = ymax - 40;

	Simple_window win(Point(100, 100), xmax, ymax, "Function graphing");

	Function s(one, r_min, r_max, orig, n_points, x_scale, y_scale);
	Function s2(slope, r_min, r_max, orig, n_points, x_scale, y_scale);
	Function s3(square, r_min, r_max, orig, n_points, x_scale, y_scale);
	Function s4(cos, r_min, r_max, orig, 400, 20, 20);
	Function s5(sloping_cos, r_min, r_max, orig, 400, 20, 20);

	Function f1(log, 0.000001, r_max, orig, 200, 30, 30);
	Function f2(sin, r_min, r_max, orig, 200, 30, 30);
	f2.set_color(Color::blue);
	Function f3(cos, r_min, r_max, orig, 200, 30, 30);
	Function f4(exp, r_min, r_max, orig, 200, 30, 30);
	f4.set_color(Color::green);

	Text ts(Point(100, y_orig - 40), "one");
	Text ts2(Point(100, y_orig + y_orig / 2 - 20), "x/2");
	Text ts3(Point(x_orig - 100, 20), "x*x");

	Axis x(Axis::x, Point(20, y_orig), xlength, xlength / x_scale, "one notch == 1");
	Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, ylength / y_scale, "one notch == 1");
	x.set_color(Color::dark_red);
	y.set_color(Color::dark_red);

	x.label.move(-160, 0);

	win.attach(x);
	win.attach(y);
	win.attach(s);
	win.attach(s2);
	win.attach(s3);
	win.attach(s4);
	win.attach(s5);
	win.attach(f1);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);
	win.attach(ts);
	win.attach(ts2);
	win.attach(ts3);

	win.wait_for_button();
}

int fac(int n)
{
	int r = 1;
	while (n > 1)
	{
		r *= n;
		--n;
	}
	return r;
}

double term(double x, int n) { return pow(x, n) / fac(n); }

double exp(double x, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += term(x, i);
	}
	return sum;
}

int expN_number_of_terms = 10;

double expN(double x)
{
	return exp(x, expN_number_of_terms);
}

void approximations()
{
	const int xmax = 640;			//window size
	const int ymax = 480;

	const int x_orig = xmax / 2;	//position of 0,0 is the center of window
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	const int r_min = -10;			//range [-10:10]
	const int r_max = 10;

	const int n_points = 400;		//number of points used in range

	const int x_scale = 30;			//scaling factors
	const int y_scale = 30;

	const int xlength = xmax - 40;	//make the axis a bit smaller than the window
	const int ylength = ymax - 40;

	Simple_window win(Point(100, 100), xmax, ymax, "Function graphing");

	Axis x(Axis::x, Point(20, y_orig), xlength, xlength / x_scale, "one notch == 1");
	Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, ylength / y_scale, "one notch == 1");
	x.set_color(Color::dark_red);
	y.set_color(Color::dark_red);

	Function real_exp(exp, r_min, r_max, orig, 200, x_scale, y_scale);
	real_exp.set_color(Color::blue);

	win.attach(x);
	win.attach(y);
	win.attach(real_exp);

	//loop through approximations 
	for (unsigned int n = 0; n < 20; ++n)
	{
		ostringstream ss;
		ss << "exp approximation; n == " << n;
		win.set_label(ss.str().c_str());
		expN_number_of_terms = n;

		//get the next approximation
		Function e(expN, r_min, r_max, orig, 200, x_scale, y_scale);
		win.attach(e);
		win.wait_for_button();
		win.detach(e);
	}

	win.wait_for_button();
}

struct Distribution
{
	int year, young, middle, old;
};

istream& operator >> (istream& is, Distribution& d)
{
	//format is: ( year : young middle old )

	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Distribution dd;

	//check the input
	if (is >> ch1 >> dd.year >> ch2 >> dd.young >> dd.middle >> dd.old >> ch3)
	{
		//if the input characaters are incorrect, set the failbit and return the istream
		if (ch1 != '(' || ch2 != ':' || ch3 != ')')
		{
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else
		return is;	//if the input is incorrect

	d = dd;
	return is;
}

class Scale
{
	int cbase;		//coordinate base
	int vbase;		//base of values
	double scale;
public:
	Scale(int b, int vb, double s) : cbase(b),vbase(vb),scale(s){}
	int operator()(int v) const { return cbase + (v - vbase)*scale; }
};

void load_file_and_draw()
{
	//load the file
	string file_name = "japanese-age-data.txt";
	ifstream ifs(file_name.c_str());
	if (!ifs) error("cant open file ", file_name);


	//set constants for the window
	const int xmax = 640;		//window size
	const int ymax = 480;

	const int xoffset = 100;	//distance from left hand side of windo to y axis
	const int yoffset = 60;		//distance from bottom of window to x axis

	const int xspace = 40;		//space beyond axis
	const int yspace = 40;

	const int xlength = xmax - xoffset - xspace;	//length of axis
	const int ylength = ymax - yoffset - yspace;

	const int base_year = 1960;
	const int end_year = 2040;

	const double xscale = double(xlength) / (end_year - base_year);	
	const double yscale = double(ylength) / 100;

	//set scale for data
	Scale xs(xoffset, base_year, xscale);
	Scale ys(ymax - yoffset, 0, -yscale);
	
	//create the window
	Simple_window win(Point(100, 100), xmax, ymax, "Aging Japan");

	Axis x(Axis::x, Point(xoffset, ymax - yoffset), xlength, 
		(end_year - base_year) / 10,
		"year    1960      1970      1980      1990      "
		"2000      2010      2020      2030     2040");
	x.label.move(-120, 0);

	Axis y(Axis::y, Point(xoffset, ymax - yoffset), ylength, 10, "% of population");

	//draws a line at 2008 straight up
	Line current_year(Point(xs(2008), ys(0)), Point(xs(2008), ys(100)));
	current_year.set_style(Line_style::dash);

	//build the lines for the data
	Open_polyline children;
	Open_polyline adults;
	Open_polyline aged;

	//gather the data from the input file stream that was opened
	Distribution d;
	while (ifs >> d)
	{
		if (d.year < base_year || end_year < d.year) error("year out of range");
		if (d.young + d.middle + d.old != 100) error("percentages dont add up");

		int x = xs(d.year);		//data comes in as: ( year : young middle old )
		children.add(Point(x, ys(d.young)));
		adults.add(Point(x, ys(d.middle)));
		aged.add(Point(x, ys(d.old)));
	}

	//Label the graph
	Text children_label(Point(20, children.point(0).y), "age 0-14");
	children.set_color(Color::red);
	children_label.set_color(Color::red);

	Text adults_label(Point(20, adults.point(0).y), "age 15-64");
	adults.set_color(Color::blue);
	adults_label.set_color(Color::blue);

	Text aged_label(Point(20, aged.point(0).y), "age 65+");
	aged.set_color(Color::dark_green);
	aged_label.set_color(Color::dark_green);

	win.attach(children);
	win.attach(adults);
	win.attach(aged);

	win.attach(children_label);
	win.attach(adults_label);
	win.attach(aged_label);

	win.attach(x);
	win.attach(y);
	win.attach(current_year);

	win.wait_for_button();
}

void f_drill()
{
	//set bounds
	const int xmax = 600;
	const int ymax = 600;

	//create origin of axis at 300,300 or the halfway of the window size
	const int x_orig = xmax / 2;
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	//length of axis is 400 each
	const int axis_length = 400;

	const int x_scale = 20;			//scaling factors
	const int y_scale = 20;

	//ranges
	const int r_min = -10;
	const int r_max = 10;

	const int n_points = 400;		//points for function drawing

	//notch every 20 pixels, axis is 400, so 400/20 is number of notches
	const int x_notches = axis_length / x_scale;
	const int y_notches = axis_length / y_scale;

	//make 600x600 window
	Simple_window win(Point(100, 100), xmax, ymax, "Function graphs");

	//make 400 length axis centered at 300,300
	Axis x(Axis::x, Point(100, y_orig), axis_length, x_notches, "1 == 20 pixels");
	x.label.move(-75, 0);
	Axis y(Axis::y, Point(x_orig, ymax-100), axis_length, y_notches, "1 == 20 pixels");

	//make axis red
	x.set_color(Color::red);
	y.set_color(Color::red);

	//graph functions like last time, number 1,2,3
	Function s1(one, r_min, r_max, orig, n_points, x_scale, y_scale);

	//number 4,5
	Function s2(slope, r_min, r_max, orig, n_points, x_scale, y_scale);
	Text slope_label(Point(100, 375), "x/2");	

	//number 6
	Function s3(square, r_min, r_max, orig, n_points, x_scale, y_scale);

	//number 7
	Function s4(cos, r_min, r_max, orig, n_points, x_scale, y_scale);
	s4.set_color(Color::blue);

	//number 8
	Function s5(sloping_cos, r_min, r_max, orig, n_points, x_scale, y_scale);


	win.attach(x);
	win.attach(y);
	win.attach(s1);
	win.attach(s2);
	win.attach(slope_label);
	win.attach(s3);
	win.attach(s4);
	win.attach(s5);

	win.wait_for_button();
}
*/

void c_drill()
{
	
	Person p1 = Person("Goofy","Duck", 63);
	cout << "Person p1 is named " << p1.first_name() << ' ' << p1.second_name()
		<< " and is " << p1.age() << " years old" << endl;
		
	Person p2;
	cout << "Enter a first name, second name and age: ";
	cin >> p2;	
	cout << p2 << endl;

	vector<Person> people;
	Person p3;

	cout << "Input people first name, second name then age, ctrl z to stop\n";
	while (cin >> p3)
		people.push_back(p3);
	for (int i = 0; i < people.size(); ++i)
		cout << people[i] << endl;
}

int main()
{
	try
	{
		c_drill();

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