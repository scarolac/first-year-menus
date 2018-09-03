#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

namespace notes
{
	//convert to strings
	template<class T> string to_string(const T& t)
	{
		ostringstream os;
		os << t;
		return os.str();
	}

	//convert from string
	struct bad_from_string : std::bad_cast
	{
		const char* what() const
		{
			return "bad cas from string";	//handle errors in converting
		}
	};

	template<class T>T from_string(const string& s)
	{
		istringstream is(s);		//convert the string to input
		T t;
		if (!(is >> t)) throw bad_from_string();	//input into the T object
		return t;					//return T
	}

	//email message reading and storing
	namespace email
	{
		typedef std::vector<string>::const_iterator Line_iter;
		class Message	//a message points to the first and last lines of a message
		{
			Line_iter first;
			Line_iter last;
		public:
			Message(Line_iter p1, Line_iter p2) : first(p1),last(p2) {}
			Line_iter begin() const { return first; }
			Line_iter end() const { return last; }

		};

		typedef std::vector<Message>::const_iterator Mess_iter;
		struct Mail_file	//a mail file holds all the lines from a file and simplifies access to messages
		{
			string name;			//file name
			vector<string> lines;	//the lines in order
			vector<Message> m;		//Messages in order

			Mail_file(const string& n);	//read file n into lines

			Mess_iter begin() { return m.begin(); }
			Mess_iter end() { return m.end(); }
		};

		Mail_file::Mail_file(const string& n)
		{
			//open file named n, read lines from n into "lines"
			//find messages in the lines and compose them in m
			//for simplicity assyme every message is ended by "----"

			ifstream in(n.c_str());	//open the file
			if (!in)
			{
				cerr << "no" << n << endl;
				exit(1);		//terminate the program
			}

			string s;
			while (getline(in, s)) lines.push_back(s);	//build the vector of lines

			Line_iter first = lines.begin();	//build the vector of messages
			for (Line_iter p = lines.begin(); p != lines.end(); ++p)
			{
				if (*p == "----")				//end of message
				{
					m.push_back(Message(first, p));
					first = p + 1;		// ---- is not part of message
				}
			}
		}

		//need three helper functions: find the name of the sender, return true if found, place senders name in s
		int is_prefix(const string& s, const string& p)
		{
			//is p the first part of s

			int n = p.size();
			if (string(s, 0, n) == p) return n;	//creates string from s[0] to n which is the size of p, p == subject or from
			return 0;
		}

		bool find_from_addr(const Message* m, string& s)
		{
			for (Line_iter p = m->begin(); p != m->end(); ++p)
			{
				if (int n = is_prefix(*p, "From: "))
				{
					s = string(*p, n);
					return true;
				}
			}
			return false;
		}

		string find_subject(const Message* m)
		{
			for (Line_iter p = m->begin(); p != m->end(); ++p)
			{
				if (int n = is_prefix(*p, "Subject: ")) return string(*p, n);	//creates and returns string starting at *p[n], so right after "subject: "
			}
			return "";
		}

	}

	void mail_test()
	{
		email::Mail_file mfile("my-mail-file.txt");	//initialize mfile from a file

		//first gather messages from each sender together in a multimap

		multimap<string, const email::Message*> sender;

		for (email::Mess_iter p = mfile.begin(); p != mfile.end(); ++p)
		{
			const email::Message& m = *p;
			string s;
			if (email::find_from_addr(&m,s))
				sender.insert(make_pair(s, &m));
		}

		//now iterate through the multimap and extract the subjects of John Doe's messages:
		typedef multimap<string, const email::Message*>::const_iterator MCI;
		pair<MCI, MCI> pp = sender.equal_range("John Doe");		//finds all the pairs with John Doe, a couple of messages are found
		for (MCI p = pp.first; p != pp.second; ++p)				//increment through the messages checking subjects
			cout << email::find_subject(p->second) << '\n';		//list the subjects with the sender 
	}

	/* Regex - regular expression
		\w{2}\s*\d{5}(-\d{4})?
		means 2 "words" or letters, with 0 or more spaces \s*, then 5 digits, 
		with the option of a dash and 4 digits (-\d{4})? to represent zip codes 
		ex: TX77845 or TX 77845 or TX77845-5629

		pg 834

		character meanings:
		.	any single character, ex: x...y means starts with x, ends with ym is 5 characters long
		[]	character class, ex: [\w @]	- word character, a space, or an @, [a-z] - the lowercase characters from a to z
		{}	count, ex: {5} is 5 of something
		()	grouping
		\	next character has special meaning
		*	zero or more
		+	one or more
		?	optional (zero or one)
		|	alternative (or)
		^	start of line; negation
		$	end of line

		special characters:
		\d	a decimal digit
		\l	lowercase character
		\s	space or tab
		\u	uppercase character
		\w	a letter or digit or underscore _
		\D	not \d
		\L	not \l
		\S	not \s
		\U	not \u
		\W	not \w

		repeats:
		{ n }	exactly n times
		{ n, }	n or more times
		{n,m}	at least n and at most m times
		*		zero or more, {0,}
		+		one or more, {1,}
		?		optional, {0,1}
	*/

	void regex_searching()
	{
		ifstream in("file.txt");
		if (!in)cerr << "no file\n";

		const string pat_string = "\\w{2}\\s*\\d{5}(-\\d{4})?";
		regex pat(pat_string);
		cout << "pattern: " << pat_string << '\n';

		int lineno = 0;
		string line;
		while (getline(in, line))
		{
			++lineno;
			smatch matches;										//finds sub matches, anythign with a () in the pattern
			if (regex_search(line, matches, pat))
			{
				cout << lineno << ": " << matches[0] << endl;	//returns the first submatch
				if (1 < matches.size() && matches[1].matched)	//finds the next submatch in () - in this case the end of the zip codes
					cout << "\t: " << matches[1] << endl;
			}
		}

	}

	void regex_errors()
	{
		regex pattern;

		string pat;
		cout << "enter pattern: ";
		getline(cin, pat);

		try
		{
			pattern = pat;
			cout << "pattern: " << pat << '\n';
		}
		catch(regex_error)
		{
			cout << pat << " is not a valid regular expression\n";
			exit(1);
		}

		cout << "now enter lines:\n";
		string line;
		int lineno = 0;

		while (getline(cin, line))
		{
			++lineno;
			smatch matches;										//finds sub matches, anythign with a () in the pattern
			if (regex_search(line, matches, pattern))
			{
				cout << "line " << lineno << ": " << line << endl;	//shows the line number
				for (int i = 0; i < matches.size(); ++i)
				{
					cout << "\tmatches[" << i << "]: " << matches[i] << endl;
				}
			}
			else
				cout << "didnt match\n";
		}

	}

	void regex_matching_check()
	{
		ifstream in("table.txt");
		if (!in)cerr << "no input file\n";

		string line;
		int lineno = 0;

		const string str_header = "^[\\w ]+(	[\\w ]+)*$";
		const string str_row = "^[\\w ]+(	\\d+)(	\\d+)(	\\d+)$";
		regex header(str_header);
		regex row(str_row);

		if (getline(in, line))
		{
			smatch matches;
			if (!regex_match(line, matches, header))
				throw runtime_error("no header");
		}

		while (getline(in, line))
		{
			++lineno;
			smatch matches;
			if (!regex_match(line, matches, row))
				throw runtime_error("bad line");
		}
	}

	void regex_matching_test()
	{
		ifstream in("table.txt");    // input file
		if (!in) throw runtime_error("no input file");

		string line;            // input buffer
		int lineno = 0;

		regex header("^[\\w ]+(	[\\w ]+)*$");
		regex row("^[\\w ]+(	\\d+)(	\\d+)(	\\d+)$");

		if (getline(in, line))	 // check header line
		{       
			smatch matches;
			if (!regex_search(line, matches, header)) {
				throw runtime_error("no header");
			}
		}

		// column totals:
		int boys = 0;
		int girls = 0;

		// current line values:
		int curr_boy = 0;
		int curr_girl = 0;

		while (getline(in, line))	// extract and check data
		{    
			++lineno;
			smatch matches;
			if (!regex_search(line, matches, row))
				throw runtime_error("bad line");

			// check row:
			curr_boy = from_string<int>(matches[1]);
			curr_girl = from_string<int>(matches[2]);
			int curr_total = from_string<int>(matches[3]);
			if (curr_boy + curr_girl != curr_total) throw runtime_error("bad row sum");

			boys += curr_boy;
			girls += curr_girl;
		}

		// check columns:
		if (2 * curr_boy != boys)  throw runtime_error("boys don't add up");
		if (2 * curr_girl != girls) throw runtime_error("girls don't add up");
		cout << "All checks passed" << endl;
	}


}

void keep_open()
{
	std::cout << "Press a key to exit\n";
	std::cin.clear();
	char ch;
	std::cin >> ch;
}
int main()
{
	try
	{
		notes::regex_matching_test();

		keep_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_open();
		return 2;
	}
	catch (...)
	{
		cerr << "Error unknown" << endl;
		keep_open();
		return 3;
	}
}