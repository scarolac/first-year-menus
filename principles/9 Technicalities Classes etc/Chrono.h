#include <std_lib_facilities.h>

namespace Chrono
{
	enum Month
	{
		jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
	};

	class Date
	{
	public:
		class Invalid{};	//to throw as an exception

		Date(int y, Month m, int d);	//check for valid date and initialize
		Date();							//default constructor

		//non-modifying operations:
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		//modifying operations:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		int y;
		Month m;
		int d;
	};
	//helper, non class functions

	bool is_date(int y, Month m, int d);	//true for valid date
	bool leapyear(int y);		//true if y is a leapyear

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	Month operator++(Month& m);

	ostream& operator<<(ostream& os, const Date& d);

	istream& operator>>(istream& is, Date& d);

	int day_in_year(const Date& d);
	int n_leapyears(int y);
	long int days_linear(const Date& d);
	enum Day
	{
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	Day day_of_week(const Date& d);

}

namespace Chrono941
{
	struct Date
	{
		int y;
		int m;
		int d;
	};

	//helper functions
	void init_day(Date& dd, int y, int m, int d);

	void add_day(Date& dd, int n);

	ostream& operator<<(ostream& os, const Date& d);
}

namespace Chrono942
{
	struct Date
	{
		int y, m, d;
		Date(int y, int m, int d);
		void add_day(int n);
	};

	ostream& operator<<(ostream& os, const Date& d);
}

namespace Chrono943
{
	class Date
	{
		int y, m, d;
	public:
		Date(int y, int m, int d);
		void add_day(int n);
		int year() { return y; }
		int month() { return m; }
		int day() { return d; }
	};

	ostream& operator<<(ostream& os, Date& d);
}

namespace Chrono971
{
	enum Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date
	{
	public:
		Date(int y, Month m, int d);
		void add_day(int n);
		int year() { return y; }
		Month month() { return m; }
		int day() { return d; }
	private:
		int y;
		Month m;
		int d;
	};

	ostream& operator<<(ostream& os, Date& d);
}

namespace Chrono974
{
	enum Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date
	{
	public:
		Date(int y, Month m, int d);
		int day() const {return d; }
		Month month() const { return m; }
		int year() const { return y; }

		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int y;
		Month m;
		int d;
	};

	ostream& operator<<(ostream& os, const Date& d);

	Month operator++(Month& m);
}
