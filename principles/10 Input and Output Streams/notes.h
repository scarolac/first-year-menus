#pragma once
#include <std_lib_facilities.h>

namespace section105
{
	struct Reading
	{
		int hour;				//hour after midnight [0:23]
		double temperature;		//in fahrenheit
		Reading(int h, double t)
			:hour(h),temperature(t){}
	};

	void section1()
	{
		cout << "Please enter input file name: ";
		string name;
		cin >> name;
		ifstream ist(name.c_str());	//ist reads from the file named name
		if (!ist) error("cant open input file ", name);

		string oname;
		cout << "Please enter output file name: ";
		cin >> oname;
		ofstream ost(oname.c_str());	//ost writes to a file named oname
		if (!ost) error("cant open output file ", oname);

		vector<Reading> temps;	//store the readings here
		int hour;
		double temperature;
		while (ist >> hour >> temperature)
		{
			if (hour < 0 || hour > 23) error("hour out of range");
			temps.push_back(Reading(hour,temperature));
		}

		for (int i = 0; i < temps.size(); ++i)
		{
			ost << '(' << temps[i].hour << " , " << temps[i].temperature << ")\n";
		}
	}
}

namespace section106
{
	void inputErrors()
	{
		int i = 0;
		cin >> i;
		if (!cin)	//cin is not good, input failed somehow
		{
			if (cin.bad()) error("cin is bad");	//stream corrupted. exit.
			if (cin.eof())
			{
				//no more input, End of file
				//this is the goal, finish reading the input
			}
			if (cin.fail())		//stream encountered something unexpected
			{
				cin.clear();	//make ready for more input
								//somehow recover
			}
		}
	}

	void fill_vector(istream& ist, vector<int>& v, char terminator)
	{
		//read integers from ist into v until we reach eof() or terminator

		//make ist throw if it goes bad
		ist.exceptions(ist.exceptions() | ios_base::badbit);
		int i = 0;
		while (ist >> i) v.push_back(i);
		if (ist.eof()) return;					//found the end of the file, exit

		if (ist.bad()) error("ist is bad");		//stream corrupted, exit
		if (ist.fail())	//clean up and report the problem
		{
			ist.clear();	//clear stream state
			
			char c;
			ist >> c;		//read a character, hopefully the terminator
			if (c != terminator)				//unexpected character
			{
				ist.unget();					//put the character back
				ist.clear(ios_base::failbit);	//set the state to fail()
			}
		}

	}

	void fill_vector2(istream& ist, vector<int>& v, char terminator)
	{
		//read integers from ist into v until we reach eof() or terminator

		//make ist throw if it goes bad
		ist.exceptions(ist.exceptions() | ios_base::badbit);

		int i = 0;
		while (ist >> i) v.push_back(i);
		if (ist.eof()) return;				//found the end of the file, exit

		//not good() and not bad() and not eof(), ist must be fail()
		ist.clear();	//clear stream state

		char c;
		ist >> c;		//read a character, hopefully the terminator
		if (c != terminator)				//unexpected character
		{
			ist.unget();					//put the character back
			ist.clear(ios_base::failbit);	//set the state to fail()
		}
	}
}

namespace section107
{
	void firstTry()
	{
		cout << "Please enter an interger in the range 1 to 10 (inclusive): \n";
		int n = 0;
		while (cin >> n)
		{
			if (n <= 10 && n >= 1) break;
			cout << "sorry " << n << " is not in the [1:10] range; please try again\n";
		}
		//use n to do stuff
	}

	void secondTry()
	{
		cout << "Please enter an interger in the range 1 to 10 (inclusive): \n";
		int n = 0;
		while (cin >> n && (n <= 10 && n >= 1))
		{
			cout << "sorry " << n << " is not in the [1:10] range; please try again\n";
		}
		//use n to do stuff
		//does not account for eof(), non integers, or no inputs
	}

	void thirdTry()
	{
		cout << "Please enter an interger in the range 1 to 10 (inclusive): \n";
		int n = 0;
		while (true)
		{
			cin >> n;
			if (cin)	//we got an integer, now check it
			{
				if (n <= 10 && n >= 1) break;	//break out of the loop to continue processing
				cout << "Sorry " << n << " is not in the [1:10] range; please try again\n";
			}
			else if (cin.fail())	//loaded a non integer
			{
				cin.clear();		//set the state back to good();
									//look at the characters
				cout << "Sorry, that was not a number; please try again\n";
				for (char ch; cin >> ch && !isdigit(ch);)	//throw away non digits
					/*nothing*/;
				if (!cin) error("no input");	//we didnt find a digit, give up
				cin.unget();	//put the digit back, so we can read a number
			}
			else
			{
				error("no input");		//eof or bad: give up
			}
		}
		//if we get here n is in range [1:10]
	}

	//overall these functions are bad because they do too much at once.
	/*	Function is trying to:
		Read values
		Prompt for input
		Write error messages
		Skip bad characters
		Test input against a range
	*/
	//Each part should be its own function

	//skips non int characters until it finds an int, otherwise fails with error
	void skip_to_int()
	{
		if (cin.fail())		//found a non integer
		{
			cin.clear();	//look at the characters
			for (char ch; cin >> ch;)	//throw away non digits
			{
				cin.unget();			//put the digit back to read the number
				return;
			}
		}
		error("no input");		//eof or bad: give up
	}

	void fourthTry()
	{
		cout << "Please enter an interger in the range 1 to 10 (inclusive): \n";
		int n = 0;
		while (true)
		{
			if (cin >> n)	//we got an integer, now check it
			{
				if (n <= 10 && n >= 1) break;	//break out of the loop to continue processing
				cout << "Sorry " << n << " is not in the [1:10] range; please try again\n";
			}
			else
			{
				cout << "Sorry, that was not a number; please try again\n";
				skip_to_int();
			}
		}
		//if we get here n is in range [1:10]
		//stil too long, and shit
	}

	//gets numbers, calls skip_to_int when non integers show
	int get_int()
	{
		int n = 0;
		while (true)
		{
			if (cin >> n) return n;
			cout << "Sorry, that was not a number; please try again\n";
			skip_to_int();
		}
	}

	//runs get_int, checks if it is in a range
	int get_int(int low, int high)
	{
		cout << "Please enter an interger in the range " << low << " to " << high << " (inclusive): \n";
		while (true)
		{
			int n = get_int();
			if (n >= low && n <= high) return n;
			cout << "Sorry "
				<< n << " is not in the [" << low << ':' << high
				<< "] range; please try again\n";
		}
	}

	//use like this
	/*	int n = get_int(1,10);
		cout << "n: " << n << endl;
	*/
	//will ask for a number and perform all the checks of the messy first 4 tries

	//or customize it with a greeting and sorry message
	int get_int(int low, int high, const string& greeting, const string& sorry)
	{
		cout << greeting << ": [" << low << ':' << high << "]\n";
		while (true)
		{
			int n = get_int();
			if (n >= low && n <= high) return n;
			cout << sorry << ": [" << low << ':' << high << "]\n";
		}
	}

}