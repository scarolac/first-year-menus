#pragma once
#include "structured.h"

namespace Structured
{
		
	void end_of_loop(istream& ist, char term, const string& message)
	{
		if (ist.fail())
		{
			ist.clear();
			char ch;
			if (ist >> ch && ch == term) return;
			error(message);
		}
	}

	istream& operator>>(istream& is, Reading& r)
	{
		//read a temperature reading from is into r, format: (3 4 9.7 )
		char ch1;
		if (is >> ch1 && ch1 != '(')	//could it be a Reading?
		{
			is.unget();
			is.clear(ios_base::failbit);
			return is;
		}

		char ch2;
		int d;
		int h;
		double t;
		is >> h >> d >> t >> ch2;
		if (!is || ch2 != ')') error("bad reading");	//messed-up reading

		r.day = d;
		r.hour = h;
		r.temperature = t;
		return is;
	}

	bool is_valid(const Reading& r)
	{
		//a rough test of reading
		if (r.day < 1 || r.day > 31) return false;
		if (r.hour < 0 || r.hour > 23) return false;
		if (r.temperature < inplausible_min || r.temperature > inplausible_max) return false;
		return true;
	}

	vector<string> month_input_tbl;
	vector<string> month_print_tbl;

	void init_input_tbl(vector<string>& tbl)
	{
		tbl.push_back("jan");
		tbl.push_back("feb");
		tbl.push_back("mar");
		tbl.push_back("apr");
		tbl.push_back("may");
		tbl.push_back("jun");
		tbl.push_back("jul");
		tbl.push_back("aug");
		tbl.push_back("sep");
		tbl.push_back("oct");
		tbl.push_back("nov");
		tbl.push_back("dec");
	}
	void init_print_tbl(vector<string>& tbl)
	{
		tbl.push_back("January");
		tbl.push_back("February");
		tbl.push_back("March");
		tbl.push_back("April");
		tbl.push_back("May");
		tbl.push_back("June");
		tbl.push_back("July");
		tbl.push_back("August");
		tbl.push_back("September");
		tbl.push_back("October");
		tbl.push_back("November");
		tbl.push_back("December");
	}

	int month_to_int(string s)
	{
		for (int i = 0; i < 12; ++i) if (month_input_tbl[i] == s) return i;
		return -1;
	}

	string int_to_month(int i)
	{
		if (i < 0 || i >= 12) error("bad month index");
		return month_print_tbl[i];
	}

	istream& operator>>(istream& is, Month& m)
	{
		//read a month from is into m, format: { month feb ...}
		char ch = 0;
		if (is >> ch && ch != '{')
		{
			is.unget();
			is.clear(ios_base::failbit);	//failed to read a month
			return is;
		}

		string month_marker;
		string mm;
		is >> month_marker >> mm;
		if (!is || month_marker != "month") error("bad start of month");
		m.month = month_to_int(mm);
		
		Reading r;
		int duplicates = 0;
		int invalids = 0;
		while (is >> r)
		{
			if (is_valid(r))
			{
				if (m.day[r.day].hour[r.hour] != not_a_reading)
					++duplicates;
				m.day[r.day].hour[r.hour] = r.temperature;
			}
			else
				++invalids;
		}

		if (invalids) error("invalid readings in month ", invalids);
		if (duplicates) error("duplicate readings in month ", duplicates);
		end_of_loop(is, '}', "bad end of month");
		return is;
	}

	istream& operator>>(istream& is, Year& y)
	{
		//read a year from is into y, format: { year 1972 ...}
		char ch;
		is >> ch;
		if (ch != '{')
		{
			is.unget();
			is.clear(ios_base::failbit);
			return is;
		}

		string year_marker;
		int yy;
		is >> year_marker >> yy;
		if (!is || year_marker != "year") error("bad start of year");
		y.year = yy;

		while (true)
		{
			Month m;	//get a clean m each time around
			if (!(is >> m)) break;
			y.month[m.month] = m;
		}

		end_of_loop(is, '}', "bad end of year");
		return is;
	}

}
