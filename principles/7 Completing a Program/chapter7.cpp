#include <std_lib_facilities.h>
//Test Case is 5: 0.204168 + sqrt((4!+8)/4+(2+3*4)^2-3^4+(9+10)*(15-21)+7*(17-15))
/*
A Grammar for PEMDAS
Calculation:
	Expression
	Print = "="
	Quit = "x"
	Calculation statement
Statement:
	Declaration
	Expression
Declaration:
	"let" Name "=" Expression
Expression:
	Term
	Expression "+" Term
	Expression "-" Term
Term:
	Factorial
	Term "*" Factorial
	Term "/" Factorial
	Term "%" Factorial
Factorial:
	Primary
	Primary! (N * N-1 * N-2...* 1) if N = 0, N! = 1
	Primary "^" Number
Primary:
	Number
	"(" Expression ")"
	+ Primary
	- Primary
	sqrt(Expression)
Number:
	floating-point-literal

Input comes from cin, through Token_Stream called ts
*/
const char number = '8';
const char quit = 'q';
const char print = ';';
const char name = 'a';
const char let = 'L';
const char sqroot = 'S';
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string sqrtkey = "sqrt";

class Token
{
public:
	char kind;                     //what kind of token
	double value;                  //stores numbers
	string name;			
	Token(char ch)                 //Initializes a Token from a char
		:kind(ch), value(0) {}
	Token(char ch, double val)     //Initializes a Token from a char and a double
		:kind(ch), value(val) {}
	Token(char ch, string n)		//Initializes Token from char and string
		:kind(ch), name(n){}
};
class Token_stream
{
public:
	Token_stream();         //make Token_stream that reads from cin
	Token get();            //get a token
	void putback(Token t);  //put a token back
	void ignore(char c);	//ignore characters until c is reached, ignore c then return
private:
	bool full;    //is there token in the buffer?
	Token buffer; //here is where the token from putback() is stored
};
Token_stream::Token_stream()      //Initializes the Token_stream() class to have full set to false and a default buffer token initialized
	:full(false), buffer(0) {}    //no token in buffer
void Token_stream::putback(Token t)  //builds the putback() function in the Token_stream class
{
	if (full) error("putback() into a full buffer");  //checks buffer not full
	buffer = t;   //copy t to buffer
	full = true;  //buffer is now full
}

Token Token_stream::get()   //builds get() function for the class Token_stream, returns a token
{
	if (full)           //is there already a token?
	{
		full = false;   //remove the token and send it back
		return buffer;
	}
	char ch;
	cin >> ch;    // remember >> skips whitespace like spaces, new lines, tabs, etc.

	switch (ch)
	{
	case print: 
	case quit:    
	case'=':
	case'(':
	case')':
	case'+':
	case'-':
	case'*':
	case'/':
	case'%':
	case'!':
	case'^':
		return Token(ch);  //let each character represent itself, return it as a token
	//handles the numbers and decimals
	case'.':
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	{
		cin.putback(ch);        //put back into input stream
		double val;             //define variable to store it
		cin >> val;             //read read the data from the cin stream and store into val
		return Token(number, val); //return the value of the arbitrary type '8' to represent numbers
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			if (s == sqrtkey) return Token(sqroot);
			return Token(name, s);
		}
		error("Bad Token");
	}
}
void Token_stream::ignore(char c)
{
	//check the buffer first
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	//then check the input for c
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}
//Handle saving variable names and the checking/getting/setting of them
class Variable
{
public:
	string name;
	double value;
	Variable(string n, double v)
		:name(n), value(v) {}
};
vector<Variable> var_table;
double get_value(string s)
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable ", s);

}
void set_value(string s, double d)
{
	for (Variable& v : var_table)
	{
		if (v.name == s)
		{
			cout << v.name << " was " << v.value << " and will be set to " << d << ".\n";
			v.value = d;
			return;
		}
	}
	error("set: undefined variable ", s);
}
bool is_declared(string var)
//is var already in var_table
{
	for (const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}
double define_name(string var, double val)
//add (var,val) to var_table or change the current value of var
{
	if (is_declared(var)) 
	{
		set_value(var, val);	//if there is already a variable this will change it.
		return val;
	} 
	var_table.push_back(Variable(var, val));
	return val;
}

Token_stream ts;     //Intializes Token_stream named ts and provides get() and putback()
double expression(); //declaration so that primary() can call expression()

double squareroot()
{
	Token t = ts.get();
	if (t.kind != '(') error("sqrt needs ( ) to function");
	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("close the ) for sqrt");
	return sqrt(d);
}
//Functions for the grammar rules set 
double primary()    //deal with numbers and parentheses
{
	Token t = ts.get();                            //get the next token from cin
	switch (t.kind)
	{
	case'(':
	{
		double d = expression();					//if ( ): evaluate expresion() inside them
		t = ts.get();								//once complete, get the next token
		if (t.kind != ')') error("')' expected");	//check if it is a closing paraentheses
		return d;									//return the result of the expression()
	}
	case print:
	case quit:
		ts.putback(t);    //puts the quit and result code back into token stream to be used by main()
	case number:
		return t.value;								//returns the value of the number
	case'-':
		return - primary();							//subtracts the next number, to make negative numbers
	case'+':
		return primary();							//adds the next number for people who are stubborn
	case name:
		return get_value(t.name);
	case sqroot:
		return squareroot();
	default:
		error("Primary expected");					//non supported symbol or no number is given
	}
}
double factorial()   //deal with ! and ^
{
	double left = primary();                       //evaluate symbols up to factorial()
	Token t = ts.get();                            //get next token
	while (true)
	{
		switch (t.kind)                            //determine if symbol found is used
		{
		case'!':
		{
			if (left == 0) return 1;               //0! = 1
			for (int i = (int)left - 1; i > 0; --i)     //count down from 'left' starting with the next lowest
			{
				left *= i;                         //multiply left by the lower number until it hits 1
			}
			t = ts.get();                          //get the next token
			break;
		}
		case'^':
		{
			double power = primary();              //after the ^ token, evaluate the number
			left = pow(left, power);               //raise left to that number (power)
			t = ts.get();                          //get next token
			break;
		}
		default:
			ts.putback(t);                         //return the unused token
			return left;                           //return the value calculated
		}
	}
}
double term()       //deal with *, /, and %
{
	double left = factorial();                     //evaluate symbols up to term()
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= factorial();                   //evaulate all symbols factorial and below, then multiply
			t = ts.get();
			break;
		case'/':
		{   //to define and initialize variables in a switch, put a block around the case section
			double d = factorial();					//evaluate the symbols under the divsor line
			if (d == 0) error("divide by zero");	//makes sure divide by 0 does not occur
			left /= d;								//evaulate all symbols factorial and below, then divide
			t = ts.get();
			break;
		}
		case'%':									//performs modulo % operation
		{
			double d = term();		//pulls next term() after % operator
			int i1 = int(left);		//explicit conversion to ints
			if (i1 != left) error("Left hand operand of % not an int");
			int i2 = int(d);
			if (i2 != d) error("Right hand operand of % not an int");
			if (i2 == 0) error("%: Divide by zero");
			left = i1%i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);							//return unused token, and the answer
			return left;
		}
	}
}
double expression() //deal with + and -
{
	double left = term();     //read and evaluate a term
	Token t = ts.get();       //get the next token
	while (true) {
		switch (t.kind)           //see what kind of token that is
		{
		case '+':
			left += term();      //evaluate term and add
			t = ts.get();        //get the next token
			break;
		case'-':
			left -= term();      //evaluate term and subtract
			t = ts.get();        //get next token
			break;
		default:
			ts.putback(t);        //not + or -, put the token back
			return left;          //return the value
		}
	}
}
double declaration()
	//assume we have seen "let"
	//handle: name = expression
	//declare a variable called "name" with the initial value "expression"
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}
void clean_up_mess()
{
	ts.ignore(print); //ignore characters until the print character is reached, ignore that too
	//after error is called, program will continue if cin has input remaining due to while loop in calculate()
}
void calculate()
{
	cout << "+, -, *, /, %, !, sqrt() and ^ can be performed.\n"
		<< "Use 'let' to define variables.\n"
		<< print << " to produce result, "<< quit << " to exit.\n";
	while (cin)
	{
		try
		{
			cout << prompt;			//puts "> " at the beginning of inputs
			Token t = ts.get();		//gets the token
			while (t.kind == print) t = ts.get();	//get the next token, ignore the print
			if (t.kind == quit)	return;		//if the quit command is sent, return 0 to end program
			ts.putback(t);			//if neither quit or print, put the token back, for next cycle in loop
			cout << result << statement() << endl;	//print the answer by calling the main function to start the chain
		}
		catch (exception& e)
		{
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
	
}
int main()
{
	try
	{
		//predefined names
		define_name("pi", 3.1415926535);
		define_name("e", 2.7182818284);

		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "error " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown Exception.\n";
		keep_window_open("~~");
		return 2;
	}
}