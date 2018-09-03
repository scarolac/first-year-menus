#include "Chrono.h"

namespace Chrono
{
	Date::Date(int yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if (!is_date(yy, mm, dd)) throw Invalid();
	}

	const Date& default_date()
	{
		static Date dd(2001, Month::jan, 1);	//start of the 21st century
		return dd;
	}

	Date::Date()
		:y(default_date().year()),
		m(default_date().month()),
		d(default_date().day())
	{}

	void Date::add_day(int n)
	{
		int days_in_month = 31;

		for (int i = 0; i < n; ++i)
		{
			switch (m)
			{
			case feb:
				days_in_month = (leapyear(y)) ? 29 : 28;
				break;
			case apr:
			case jun:
			case sep:
			case nov:
				days_in_month = 30;
				break;
			default:
				days_in_month = 31;
			}
			if (d == days_in_month)
			{
				add_month(1);
				d = 1;
			}
			else
				++d;
		}
	}
	
	Month operator++(Month& m)
	{
		m = (m == dec) ? jan : Month(m + 1);
		return m;
	}

	void Date::add_month(int n)
	{
		for (int i = 0; i < n; ++i)
		{
			if (m == dec) ++y;	//if the month rolls over, roll over the year
			++m;
		}
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n))
		{
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	//helper non class functions
	bool is_date(int y, Month m, int d)
	{
		//assume y is valid

		if (d <= 0) return false;	//d must be positive
		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month = 31;		//most months have 31 days

		switch (m)
		{
		case Month::feb:
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			days_in_month = 30;
			break;
		}

		if (days_in_month < d) return false;

		return true;
	}

	// a leap year is divisible by 4, but not by 100, except if it is divisible by 400
	bool leapyear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day()
			<< ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;

		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')	//format error
		{
			is.clear(ios_base::failbit);		//set the failbit
			return is;
		}
		dd = Date(y, Month(m), d);		//update dd

		return is;
	}
		
	const Date first_date = Date(1970, Month::jan, 1);
	const Day first_day = thursday;
	Day day_of_week(const Date& d)
	{
		if (d.year() < first_date.year()) error("day_of_week: works only for 1970 and later");
		int dlin = days_linear(d);
		return Day((first_day + dlin) % 7);
	}

	int nmonth(Month m)
	{
		switch (m) 
		{
		case Month::jan: return 0;
		case Month::feb: return 31;
		case Month::mar: return 31 + 28;
		case Month::apr: return 31 + 28 + 31;
		case Month::may: return 31 + 28 + 31 + 30;
		case Month::jun: return 31 + 28 + 31 + 30 + 31;
		case Month::jul: return 31 + 28 + 31 + 30 + 31 + 30;
		case Month::aug: return 31 + 28 + 31 + 30 + 31 + 30 + 31;
		case Month::sep: return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
		case Month::oct: return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		case Month::nov: return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		case Month::dec: return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
		default:
			return 0;
		}
	}

	int day_in_year(const Date& d)
	{
		int diy = nmonth(d.month());	//days in month before d
		diy += d.day();					//days in month of d
		if (leapyear(d.year()) && d.month() > Month::feb) ++diy;	//if leapyear, and past feb, add one day
		return diy;
	}
	
	int n_leapyears(int y)
	{
		int nl = 0;
		for (int i = 1970; i < y; ++i)
		{
			if (leapyear(i)) ++nl;
		}
		return nl;
	}
	long int days_linear(const Date& d)
	{
		if (d.year() < first_date.year()) error("days_linear: year must be 1970 or later");
		int y = d.year() - first_date.year();
		return y * 365 + n_leapyears(d.year()) + day_in_year(d) - 1;
	}
	Date next_Sunday(const Date& d)
	{
		Date nsd = d;
		Day day = day_of_week(d);
		nsd.add_day(7 - day);
		return nsd;
	}

	Date next_weekday(const Date& d)
	{
		Date nwd = d;
		Day day = day_of_week(d);

		switch (day)
		{
		case sunday:
		case monday:
		case tuesday:
		case wednesday:
		case thursday:
			nwd.add_day(1);
			break;
		case saturday:
			nwd.add_day(2);
			break;
		case friday:
			nwd.add_day(3);
			break;
		}
		return nwd;
	}
	
}

namespace Chrono941
{
	void init_day(Date& dd, int y, int m, int d)
	{
		if (m < 0 || 12 < m || d < 0 || 31 < d) error("invalid date");
		dd.y = y;
		dd.m = m;
		dd.d = d;
	}

	void add_day(Date& dd, int n)
	{
		init_day(dd, dd.y, dd.m, dd.d + n);
	}
	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.y
			<< ',' << d.m
			<< ',' << d.d
			<< ')';
	}
}

namespace Chrono942
{
	Date::Date(int y, int m, int d)
		:y(y), m(m), d(d)
	{
		if (m < 0 || 12 < m || d < 0 || 31 < d) error("invalid date");
	}

	void Date::add_day(int n)
	{
		d += n;
		if (d > 31) error("add_day() results in invalid date");
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.y
			<< ',' << d.m
			<< ',' << d.d
			<< ')';
	}
}

namespace Chrono943
{
	Date::Date(int y, int m, int d)
		:y(y), m(m), d(d)
	{
		if (m < 0 || 12 < m || d < 0 || 31 < d) error("invalid date");
	}

	void Date::add_day(int n)
	{
		d += n;
		if (d > 31) error("add_day() results in invalid date");
	}

	ostream& operator<<(ostream& os, Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day()
			<< ')';
	}
}

namespace Chrono971
{
	Date::Date(int yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if (m < Month::jan || Month::dec < m || d < 0 || 31 < d) error("invalid date");
	}

	void Date::add_day(int n)
	{
		d += n;
		if (d > 31) error("add_day() results in invalid date");
	}

	ostream& operator<<(ostream& os, Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day()
			<< ')';
	}
}

namespace Chrono974
{
	Date::Date(int yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if (m < jan || dec < m || d < 0 || 31 < d) error("invalid date");
	}

	// a leap year is divisible by 4, but not by 100, except if it is divisible by 400
	bool leapyear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
	}

	void Date::add_day(int n)
	{
		if (n < 2) cout << "Add " << n << " day" << endl;
		else
			cout << "Add " << n << " days" << endl;
		int days_in_month = 31;
		
		for (int i = 0; i < n; ++i)
		{
			switch (m)
			{
			case feb:
				days_in_month = (leapyear(y)) ? 29 : 28;
				break;
			case apr:
			case jun:
			case sep:
			case nov:
				days_in_month = 30;
				break;
			default:
				days_in_month = 31;
			}
			if (d == days_in_month)
			{
				add_month(1);
				d = 1;
			}
			else
				++d;
		}			
	}

	Month operator++(Month& m)
	{
		m = (m == dec) ? jan : Month(m + 1);
		return m;
	}

	void Date::add_month(int n)
	{
		for (int i = 0; i < n; ++i)
		{
			if (m == dec) ++y;	//if the month rolls over december, roll over the year
			++m;
		}
	}

	void Date::add_year(int n)
	{
		if (m == feb && d == 29 && !leapyear(y + n))
		{
			m = mar;
			d = 1;
		}
		y += n;
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day()
			<< ')';
	}
}