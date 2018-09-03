// Section CSC160 - Computer Science I: C++
// File Name: lesson5-614-7.cpp
// Student: Chris Scarola
// Homework Number: 5
// Description:
/*
  Write a rational number class. This problem will be revisited in Chapter 11,
where operator overloading will make the problem much easier. For now
we will use member functions add, sub, mul, div, and less that each carry
out the operations +, -, *, /, and <. For example, a + b will be written
a.add(b), and a < b will be writteny a.less(b).
Define a class for rational numbers. A rational number is a "ratio-nal"
number, composed of two integers with division indicated. The division
is not carried out, it is only indicated, as in 1/2, 2/3, 15/32, 65/4, 16/5.
You should represent rational numbers by two int values, numerator and
denominator.
A principle of abstract data type construction is that constructors must
be present to create objects with any legal values. You should provide
constructors to make objects out of pairs of int values; this is a constructor
with two int parameters. Since every int is also a rational number, as in
2/1 or 17/1, you should provide a constructor with a single int parameter.
Provide member functions input and output that take an istream and
ostream argument, respectively, and fetch or write rational numbers in
the form 2/3 or 37/51 to or from the keyboard (and to or from a file).

Provide member functions add, sub, mul, and div that return a rational
value. Provide a function less that returns a bool value. These functions
should do the operation suggested by the name. Provide a member function
neg that has no parameters and returns the negative of the calling object.
Provide a main function that thoroughly tests your class implementation.
The following formulas will be useful in defining functions.
a/b + c/d = (a * d + b * c) / (b * d)
a/b - c/d = (a * d - b * c) / (b * d)
(a/b) * (c/d) = (a * c) / (b * d)
(a/b) / (c/d) = (a * d) / (c * b)
-(a/b) = (-a/b)
(a/b) < (c/d) means (a * d) < (c * b)
(a/b) == (c/d) means (a * d) == (c * b)
Let any sign be carried by the numerator; keep the denominator positive.
 */
// Last Changed: 9/29/2016

#include "cs1/mod2/cs1mod2.h"

namespace lesson5_614_7 {

using namespace std;

class rational
{
public:
    int numerator, denominator;

public:
    rational();
    //default constructor
    
    rational(int num, int denom);
    //construct rational number with numerator and denominator

    //functions to add, subtract, multiply, divide and compare rational numbers, and make negative
    rational add(rational& r);
    rational sub(rational& r);
    rational mul(rational& r);
    rational div(rational& r);
    bool less(rational& r);
    rational neg();

    rational input(istream& in);
    //recieves input from cin or ifstream
    
    void output(ostream& out);
    //outputs to cout or ofstream
};

void calculate(rational& r1, rational& r2, char op);
//calculates based on certain operations: + - * / or <

void run()
{
    do
    {
        clear_screen();

        cout << "What is r1: ";
        rational r1 = r1.input(cin);

        cout << "What is r2: ";
        rational r2 = r2.input(cin);

        cout << "What operation should be performed? (+,-,*,/,< or >): ";
        char operation;
        cin >> operation;

        calculate(r1,r2,operation);

        cout << endl << "r1 made negative is: ";
        rational r_neg = r1.neg();
        r_neg.output(cout);
    }
    while(prompt());

    keep_window_open("~~");
}

rational::rational()
    :numerator(0), denominator(1)
{}

rational::rational(int num, int denom)
    : numerator(num), denominator(denom)
{}

rational rational::add(rational& r)
{
    int n = (numerator * r.denominator) + (denominator * r.numerator);
    int d = denominator * r.denominator;
    return rational(n,d);
}

rational rational::sub(rational& r)
{
    int n = (numerator * r.denominator) - (denominator * r.numerator);
    int d = denominator * r.denominator;
    return rational(n,d);
}

rational rational::mul(rational& r)
{
    int n = numerator * r.numerator;
    int d = denominator * r.denominator;
    return rational(n,d);
}

rational rational::div(rational& r)
{
    int n = numerator * r.denominator;
    int d = r.numerator * denominator;
    return rational(n,d);
}

bool rational::less(rational& r)
{
    return (numerator * r.denominator) < (r.numerator * denominator);
}

rational rational::neg()
{
    return rational(numerator*(-1),denominator);
}

rational rational::input(istream& in)
{
    int n, d;
    char ch;
    in >> n >> ch >> d;
    if (d == 0 || ch != '/')
    {
        cout << "Invalid input - no '/' or divide by 0";
        in.clear(ios_base::failbit);
        return rational();
    }
    return rational(n,d);
}

void rational::output(ostream& out)
{
    if(denominator < 0)
        out << (-1) * numerator << "/" << (-1) * denominator;
    else
        out << numerator << "/" << denominator;
}

void calculate(rational& r1, rational& r2, char op)
{     
    r1.output(cout);
    cout << ' ' << op << ' ';
    r2.output(cout);
    cout << " = ";

    rational r_out;

    switch(op)
    {
    case '+':
    {
        r_out = r1.add(r2);
        r_out.output(cout);
        break;
    }
    case '-':
    {
        r_out = r1.sub(r2);
        r_out.output(cout);
        break;
    }
    case '*':
    {
        r_out = r1.mul(r2);
        r_out.output(cout);
        break;
    }
    case '/':
    {
        r_out = r1.div(r2);
        r_out.output(cout);
        break;
    }
    case '<':
    {
        if(r1.less(r2))
            cout << "true";
        else
            cout << "false";
        break;
    }
    case '>':
    {
        if(r2.less(r1))
            cout << "true";
        else
            cout << "false";
        break;
    }
    default:
    {
        cout << "Invalid operator";
        break;
    }
    }
    
}

}
