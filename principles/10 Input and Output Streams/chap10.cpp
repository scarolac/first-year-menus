#include "notes.h"
#include "structured.h"

void readAndWrite()
{
	using namespace section105;
	section1();
}

void runIt()
{
	using namespace Structured;
	//initialize the representation tables
	init_input_tbl(month_input_tbl);
	init_print_tbl(month_print_tbl);

	//open input file
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs(iname);
	if (!ifs) error("cant open input file", iname);

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);	//throw for bad()

															//open output file
	cout << "Please enter output file name\n";
	string oname;
	cin >> oname;
	ofstream ofs(oname);
	if (!ofs) error("cant open output file");

	//read an arbitrary number of years
	vector<Year> ys;
	while (true)
	{
		Year y;		//get a freshly initialized year each time around the loop
		if (!(ifs >> y)) break;
		ys.push_back(y);
	}
	cout << "read" << ys.size() << " years of readings\n";

	//for(int i = 0; i < ys.size(); ++i) print_year(ofs,y[i]);
}

struct Point
{
	int x, y;
	Point()
		:x(0),y(0){}
	Point(int x, int y)
		:x(x),y(y){}
};

bool operator==(const Point& p1, const Point& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point& p1, const Point& p2)
{
	return !(p1 == p2);
}

ostream& operator<<(ostream& os, const Point& p)
{
	return os << '(' << p.x << ',' << p.y << ')';
}

istream& operator>>(istream& is, Point& p)
{
	int x, y;
	char ch1, ch2, ch3;
	is >> ch1 >> x >> ch2 >> y >> ch3;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	p = Point(x, y);
	return is;
}

void print_vector(const vector<Point>& points)
{
	for (int i = 0; i < points.size(); ++i)
	{
		cout << points[i] << endl;
	}
}

void write_to_file(const vector<Point>& points, const string& name)
{
	ofstream ofs(name.c_str());
	if (!ofs) error("cannot open output file", name);
	for (int i = 0; i < points.size(); ++i)
	{
		ofs << points[i] << endl;
	}
}

void fill_from_file(vector<Point>& points, const string& name)
{
	ifstream ifs(name.c_str());
	if (!ifs) error("cant open input file", name);
	Point pp;
	while (ifs >> pp) points.push_back(pp);
}

void compare_vectors(const vector<Point>& p1, const vector<Point>& p2)
{
	if (p1.size() != p2.size())
		error("Something's wrong!");
	for (int i = 0; i < p1.size(); ++i)
		if (p1[i] != p2[i])
			error("Something's wrong!");
}

void drillTime()
{
	vector<Point> original_points;

	//input the data
	cout << "Input 7 points (x,y): ";
	for (int i = 0; i < 7; ++i)
	{
		Point p;
		cin >> p;
		original_points.push_back(p);
	}

	//print the data
	cout << "Original Points:\n";
	print_vector(original_points);

	//write to output file
	string name = "mydata.txt";
	write_to_file(original_points, name);

	//read points from input file 
	vector<Point> processed_points;
	fill_from_file(processed_points, name);

	//Print both vectors
	cout << "\nData from ifstream:\n";
	print_vector(processed_points);
	cout << "\nOriginal Points:\n";
	print_vector(original_points);

	//compare the vectors
	compare_vectors(original_points, processed_points);
}


int main()
{
	try
	{
		//put functions here
		drillTime();
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cout << "Exception Unknown" << endl;
		keep_window_open("~~");
		return 2;
	}
}

