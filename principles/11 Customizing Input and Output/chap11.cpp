#include <std_lib_facilities.h>
#include "punctstream.h"

void tryThisOutput()
{
	int num = 1987;

	cout << "Decimal " << num << '\t'
		<< hex << "Hex " << num << "\t\t"	//hex converts the next outputstream item to hex
		<< oct << "Octal " << num << '\n';	//oct converts to octal
	cout << showbase << dec;				//showbase will show the base listed in the next output, here is shows them all as decimals
	cout << "Decimal " << num << '\t'
		<< hex << "Hex " << num << '\t'		//hex in decimal has a 0x preceeding the number
		<< oct << "Octal " << num << '\n';	//octal in decimal has a 0 preceeding
	cout << dec;							//change back to dec
	cout << "Decimal " << num << '\t'	
		<< 0x7c3 << '\t'					//0x converts to a dec from hex
		<< 03703 << '\n';					//0 converts to dec from oct

	/*	Integer output manipulations:
		oct			use base 8
		dec			use base 10
		hex			use base 16
		showbase	prefix 0 for oct and 0x for hex
		noshowbase	dont show prefixes
	*/
}

void tryThisInput()
{
	int a, b, c, d;

	cout << "4 values: ";
	cin >> a >> hex >> b >> oct >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << endl;

	cin.unsetf(ios::dec);		//unsetf clears the flag from input stream
	cin.unsetf(ios::hex);
	cin.unsetf(ios::oct);

	cout << "4 values again: ";
	cin >> a >> b >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
}

void tryThisPrecision()
{
	double number = 1234567.89;

	cout << number << "\t(general)\n"
		<< fixed << number << "\t(fixed)\n"
		<< scientific << number << "\t(scientific)\n";
	cout << number << "\t(carried from previous)\n";
	cout << general << number << "\t(general)\n"
		<< fixed << number << "\t(fixed)\n"
		<< scientific << number << "\t(scientific)\n";

	/*	Floating point formats
		fixed		fixed-point notation, precision is after the decimal
		scientific	use mantissa and exponent notation, precision is after the decimal
		general		choose fixed or scientific to give the numberically most accurate 
					within the precsion of general. General format is the defualt but 
					to explicitly set it you need a definition of general()
					General has 6 total digits, adjusting to fixed or scientific as needed
	*/

	double number2 = 1234.56789;

	cout << general << number2 << '\t'
		<< fixed << number2 << '\t'
		<< scientific << number2 << '\n';

	cout << general << setprecision(5) 
		<< number2 << '\t'
		<< fixed << number2 << '\t'
		<< scientific << number2 << '\n';
	cout << general << setprecision(8) 
		<< number2 << '\t'
		<< fixed << number2 << '\t'
		<< scientific << number2 << '\n';

	/*	general code does not exist, only in std lib facilities

	inline ios_base& general(ios_base& b)
	{
		//clear all floating point format flags

		b.setf(ios_base::fmtflags(0), ios_base::floatfield);
		return b;
	}

	*/
}

void tryThisFields()
{
	//setw() field sizes do not stick, has to be set before each output

	cout << setw(10) << "Wuethrich" << " | " << "Benjamin" << " | "
        << setw(16) << "+1345 326 5181" << " | " << setw(29) << "benjamin.wuethrich@gmail.com" << endl
        << setw(10) << "Forrest" << " | " << setw(8) << "Kara" << " | "
        << setw(16) << "+1345 516 1920" << " | " << setw(29) << "kara_forrest@hotmail.com" << endl
        << setw(10) << "Aarnau" << " | " << setw(8) << "Mayra" << " | "
        << "+34 66 696 55 63" << " | " << setw(29) << "mayraaachen@hotmail.com" << endl
        << setw(10) << "Michel" << " | " << setw(8) << "Tanael" << " | "
        << "+41 79 374 48 62" << " | " << setw(29) << "tanael@gmail.com" << endl
        << setw(10) << "Widler" << " | " << setw(8) << "Andrea" << " | "
        << "+41 79 293 29 38" << " | " << setw(29) << "andreawidler@bluewin.ch" << endl
        << "Amanatidou" << " | " << "Elisabet" << " | "
        << "+41 76 701 61 28" << " | " << "elisabet.amanatidou@gmail.com" << endl;
}

namespace fileOpenModes
{
	/*	Filestream open modes
		ios_base::app		append (add to the end of the file)
		ios_base::ate		"at end" (open and seek to end)
		ios_base::binary	binary mode - beware of system-spcific behavior
		ios_base::in		for reading (default for ifstream)
		ios_base::out		for writing (default for ofstream)
		ios_base::trunc		truncate file to 0-length
	*/
	string name = "mydata.txt";
	ofstream of1(name, ios_base::app);

	fstream fs(name, ios_base::in | ios_base::out);	//both in and out, '|' is the bitwise or operator, used to combine modes
	//with file names, output will create a file if it does not exist
	//input will turn ifstream into a non good() state


}

namespace positioningInFiles
{
	void function()
	{
		string name = "mydata.txt";
		fstream fs(name.c_str());		//open for input and output
		if (!fs) error("cant read");

		fs.seekg(5);	//move reading position (g for get) to 5, the 6th character (0-5)
		char ch;
		fs >> ch;		//read and increment reading position
		cout << "character 6 is " << ch << '(' << int(ch) << ")\n";

		fs.seekp(1);	//move writing position (p for put) to 1
		fs << 'y';		//write and increment writing position
	}

	//seekg to start reading from a position and seekp to start writing at a specific position
}

/*	Causes a weird runtime error even though it is never used
namespace stringStreams
{
	double str_to_double(string s)
	{
		//if possible, convert characters in s to a floating-point value
		istringstream is(s);	//make a stream so that we can read from s
		double d;
		is >> d;
		if (!is) error("double format error: ", s);
		return d;
	}

	double d1 = str_to_double("12.4");					//testing
	double d2 = str_to_double("1.34e-3");	
	double d3 = str_to_double("twelve point three");	//will call error()

	//istringstream needs a string to initialize, it needs something to read input from
	//ostringstream usually starts empty, to be filled with output operators <<
	//stringstream ss can call ss.str() to return a copy of ss's string
}*/

void lineInput()
{
	//string reads until it hits whitespace
	//int reads until a non int is found
	//getline(cin, name) can read an entire line


	//game text reads: go left until you see a picture on te wall to your right 
	//remove the picture and open the doot behind it. take the bag from there

	string command;				//create string to store the whole line
	getline(cin,command);		//use getline to store the entire sentence

	stringstream ss(command);	//create a stringstream using command
	vector<string> words;		
	string s;		
	while (ss >> s) words.push_back(s);	//use the stringstream as input into a temp string s, store the individual words into vector

}

void readCharacters()
{
	//1 + 4 * x <= y / z * 5

	char ch;
	while (cin.get(ch))
	{
		if (isspace(ch)) {}	//if ch is whitespace, do nothing
		if (isdigit(ch)) {} //read a number
		else if (isalpha(ch)) {} //read an identifier
		else {}	//deal with operators
	}
	//istream::get() reads a single character, including whitespace

	/*	Character classifications
		isspace(c)		is c whitespace ('','\t','\n' etc)
		isalpha(c)		is c a letter ('a','z','A','Z' etc)
		isdigit(c)		is c a decimal digit (0-9)
		isxdigit(c)		is c a hexadecimal digit (a-f, A-F)
		isuppper(c)		is c an upper case letter
		islower(c)		is c a lower case letter
		isalnum(c)		is c a letter or decimal digit
		iscntrl(c)		is c a control character (ASCII 0..31 and 127)
		ispunct(c)		is c not a letter, digit, whitespace or invisible control character
		isprint(c)		is c printable (ACSII ' '..' '~')
		isgraph(c)		is c isalpha() | isdigit() | ispunct() (notes: not space)
	*/

	//toupper(c)	c or c's uppercase equivalent
	//tolower(c)	c or c's lowercase equivalent


}

void punctStreamTest()
{
	//given text input, produce a sorted list of all words in that text
	//ignore punctuation and case differences
	//eliminate duplicates from the output

	Punct_stream ps(cin);
	ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~"); // the '\"' means " in string
	ps.case_sensitive(false);

	cout << "Please enter words\n";
	vector<string> vs;
	string word;
	while (ps >> word) vs.push_back(word);	//read the words

	sort(vs.begin(), vs.end());	//sort in lexographical order, abc order
	for (size_t i = 0; i < vs.size(); ++i)
	{
		if (i == 0 || vs[i] != vs[i - 1]) cout << vs[i] << endl;	
		//if the first index, or current vs is different than previous, eliminates duplicates, since it is sorted in order now
	}
}

void drill()
{
	int birth_year = 1987;

	cout << "Decimal\t" << "Hex\t" << "Octal\n";
	cout << showbase;
	cout << birth_year << '\t'
		<< hex << birth_year << '\t'
		<< oct << birth_year << endl;
	cout << dec;
	cout << "My Age: " << 2016 - birth_year << endl;

	int a, b, c, d;
	
	cout << "4 values: ";
	cin >> a >> hex >> b >> oct >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
	//takes the input as a hex value then an oct value
	//outputs the decimal version of the input 

	double num = 1234567.89;

	cout << num << '\t'
		<< fixed << num << '\t'
		<< scientific << num << endl;
	//fixed is most accurate because it takes 6 digits after the decimal
	//scientific also does, but it moves the decimal first, losing the last value

	tryThisFields();
}

int main()
{
	try
	{
		drill();

		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cout << "error: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cout << "unknown error" << endl;
		keep_window_open("~~");
		return 2;
	}
}