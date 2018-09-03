#include <std_lib_facilities.h>
//(4!+8)/4+(2+3*4)^2-3^4+(9+10)*(15-21)+7*(17-15)=
int version1()
{
	cout << "Please enter expression (we can handle + and -): ";
	int lval = 0;
	int rval;
	char op;
	int res;
	cin >> lval >> op >> rval;   //read something like 1 + 3

	if (op == '+') res = lval + rval;       //addition
	else if (op == '-') res = lval - rval;  //subtraction

	cout << "Result: " << res << endl;
	keep_window_open();
	return 0;
}
int version2()
{
	cout << "Please enter expression (we handle +, -, *, and /): ";
	int lval = 0;
	int rval;
	char op;
	cin >> lval;
	if (!cin) error("No first operand\n");
	while (cin >> op)
	{
		cin >> rval;
		if (!cin) error("No second operand\n");
		switch (op)
		{
		case '+':
			lval += rval;
			break;
		case '-':
			lval -= rval;
			break;
		case '*':
			lval *= rval;
			break;
		case'/':
			lval /= rval;
			break;
		default:
			cout << "Result: " << lval << endl;
			keep_window_open();
			return 0;
		}
		
	}
	error("bad expression");
}
class Token
{
public:
	char kind;                     //what kind of token
	double value;                  //stores numbers
	Token(char ch)                 //Initializes a Token from a char
		:kind(ch), value(0) {}
	Token(char ch, double val)     //Initializes a Token from a char and a double
		:kind(ch), value(val) {}
};
class Token_stream
{
public:
	Token_stream();         //make Token_stream that reads from cin
	Token get();            //get a token
	void putback(Token t);  //put a token back
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
	case'=':    //for "print"
	case'x':    //for "quit"
	case'(':case')':case'+':case'-':case'*':case'/':case'%':case'!':case'^':
		return Token(ch);  //let each character represent itself, return it as a token
	//handles the numbers and decimals
	case'.':
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	{
		cin.putback(ch);        //put back into input stream
		double val;             //define variable to store it
		cin >> val;             //read read the data from the cin stream and store into val
		return Token('8', val); //return the value of the arbitrary type '8' to represent numbers
	}
	default:
		error("Bad Token");
	}
}

Token_stream ts;     //Intializes Token_stream named ts and provides get() and putback()
double expression(); //declaration so that primary() can call expression()
/*
A Grammar for PEMDAS
{
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
Number:
floating-point-literal
}*/
//Functions for the grammar rules set 
double primary()    //deal with numbers and parentheses
{
	Token t = ts.get();                            //get the next token from cin
	switch (t.kind)
	{
	case'(':
	{
		double d = expression();                   //if ( ): evaluate expresion() inside them
		t = ts.get();                              //once complete, get the next token
		if (t.kind != ')') error("')' expected");  //check if it is a closing paraentheses
		return d;                                  //retrun the result of the expression()
	}
	case'=':
	case'x':
		ts.putback(t);    //puts the quit and result code back into token stream to be used by main()
	case'8':
		return t.value;                            //returns the value of the number
	default:
		error("Primary expected");                 //non supported symbol or no number is given
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
			for (int i = left - 1; i > 0; --i)     //count down from 'left' starting with the next lowest
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
		{   //to define and initialize varibles in a switch, put a block around the case section
			double d = factorial();               //evaluate the symbols under the divsor line
			if (d == 0) error("divide by zero");  //makes sure divide by 0 does not occur
			left /= d;                            //evaulate all symbols factorial and below, then divide
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);                        //return unused token, and the answer
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

int main()
{
	try
	{
		double val = 0;               //initializes val to be used to perform math
		cout << "Welcome to our simple calculator.\n"
			<< "Please enter an expression using floating point numbers.\n"
			<< "+, -, *, /, !, and ^ can be performed.\n"
			<< "= to produce result, x to exit.\n";
		while (cin)
		{
			Token t = ts.get();        //gets the token

			if (t.kind == 'x') break;  //'x' for quit, breaks the loop
			if (t.kind == '=') cout << "= " << val << endl; //shows the result of the math performed
			else ts.putback(t);        //if neither 'x' or '=', put the token back, for next cycle in loop
			val = expression();        //val is defined as expresion() which runs through the math, pulling that first token again that was just put back
		}
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "error " << e.what() << endl;
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown Exception.\n";
		keep_window_open();
		return 2;
	}
}