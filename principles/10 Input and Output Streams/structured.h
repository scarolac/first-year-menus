#include <std_lib_facilities.h>

namespace Structured
{
	const int not_a_reading = -7777;
	const int not_a_month = -1;

	struct Day
	{
		//vector of hours, 0-23, defaulted to not_a_reading
		vector<double> hour;
		Day()
			:hour(24)
		{
			for (int i = 0; i < hour.size(); ++i)
			{
				hour[i] = not_a_reading;
			}
		}
	};

	struct Month
	{
		int month;					//[0:11] January is 0
		vector<Day> day;			//[1:31] one vector of readings per day, 0 is omitted from days, start at 1
		Month()
			:month(not_a_month), day(32){}
	};

	struct Year
	{
		int year;					//positive == AD
		vector<Month> month;		//[0:11] January is 0
		Year()
			:month(12){}
	};

	struct Reading
	{
		int day;
		int hour;
		double temperature;
	};

	void end_of_loop(istream& ist, char term, const string& message);

	istream& operator>>(istream& is, Reading& r);

	constexpr int inplausible_min = -200;
	constexpr int inplausible_max = -200;

	bool is_valid(const Reading& r);
	
	extern vector<string> month_input_tbl;
	extern vector<string> month_print_tbl;
	
	void init_input_tbl(vector<string>& tbl);
	void init_print_tbl(vector<string>& tbl);

	int month_to_int(string s);
	string int_to_month(int i);

	istream& operator>>(istream& is, Month& m);

	istream& operator>>(istream& is, Year& y);
}