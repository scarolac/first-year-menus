// Section CSC160 - Computer Science I: C++
// File Name: lesson6-695-2.cpp
// Student: Chris Scarola
// Homework Number: 6
// Description:
/*
  Define a class for rational numbers. A rational number is a number that
can be represented as the quotient of two integers. For example, 1/2, 3/4,
64/2, and so forth are all rational numbers. (By 1/2, etc., we mean the
everyday meaning of the fraction, not the integer division this expression
would produce in a C++ program.) Represent rational numbers as two values
of type int, one for the numerator and one for the denominator. Call
the class Rational.
Include a constructor with two arguments that can be used to set the
member variables of an object to any legitimate values. Also include a
constructor that has only a single parameter of type int; call this single
parameter whole_number and define the constructor so that the object
will be initialized to the rational number whole_number/1. Also include a
default constructor that initializes an object to 0 (that is, to 0/1).

Overload the input and output operators >> and <<. Numbers are to be
input and output in the form 1/2, 15/32, 300/401, and so forth. Note
that the numerator, the denominator, or both may contain a minus
sign, so -1/2, 15/32, and -300/-401 are also possible inputs.

Overload all of the following operators so that they correctly apply to the type
Rational: ==, <, <=, >, >=, +, -, *, and /. Also write a test program to test
your class.

(Hints: Two rational numbers a/b and c/d are equal if a*d equals
c*b. If b and d are positive rational numbers, a/b is less than c/d
provided a*d is less than c*b.

You should include a function to normalize
the values stored so that, after normalization, the denominator
is positive and the numerator and denominator are as small
as possible. For example, after normalization 4/-8 would be represented
the same as -1/2. You should also write a test program to test
your class.)
 */
// Last Changed: 10/8/2016

#include "cs1/mod2/cs1mod2.h"

namespace lesson6_695_2 {

using namespace std;

class rational
{
private:
    int numerator, denominator;
    
    rational normalize();
    //reduces the fraction if possible

public:
    rational();
    //default constructor: 0/1

    rational(int num);
    //constructor for whole numbers: num/1
    
    rational(int num, int denom);
    //construct rational number with numerator and denominator

    //functions to add, subtract, multiply, divide, and make negative
    friend rational operator+(const rational& r1, const rational& r2);
    friend rational operator-(const rational& r1, const rational& r2); //subtracts
    friend rational operator-(const rational& r);                  //changes sign
    friend rational operator*(const rational& r1, const rational& r2);
    friend rational operator/(const rational& r1, const rational& r2);
    
    //comparison operators
    friend bool operator<(const rational& r1, const rational& r2);
    friend bool operator==(const rational& r1, const rational& r2);
    friend bool operator!=(const rational& r1, const rational& r2);
    friend bool operator>(const rational& r1, const rational& r2);
    friend bool operator<=(const rational& r1, const rational& r2);
    friend bool operator>=(const rational& r1, const rational& r2);

    friend istream& operator>>(istream& is, rational& r);
    //recieves input from istream

    friend ostream& operator<<(ostream& os, const rational& r);
    //outputs to ostream
};

void rational_processing();
//receives input from user and outputs the format listed in homework page

void test_case();
//calculates based on certain operations: + - * /, < or >, used to test the class

void run()
{
    do
    {
        clear_screen();

        cout << "Rational numbers are input with a numerator and denominator with a \"/\""
             << "\nOperations will reduce fractions" << endl;

        //input tester
        //test_case();

        rational_processing();
    }
    while(prompt());

    keep_window_open("~~");
}

rational::rational()
    :numerator(0), denominator(1)
{}

rational::rational(int num)
    :numerator(num),denominator(1)
{}

rational::rational(int num, int denom)
    : numerator(num), denominator(denom)
{}

rational rational::normalize()
{
    //ignore negatives to reduce
    int n = abs(numerator);
    int d = abs(denominator);
    
    if(n < d)
    {
        for(int i = n; i > 1; --i)
        {
            if (n % i == 0 && d % i == 0)
            {
                n /= i;
                d /= i;
            }
        }
    }
    else
    {
        for(int i = d; i > 1; --i)
        {
            if (n % i == 0 && d % i == 0)
            {
                n /= i;
                d /= i;
            }
        }
    }

    //restore negatives if needed
    if(numerator < 0) n *= -1;
    if(denominator < 0) d *= -1;

    return rational(n,d);
}

rational operator+(const rational& r1, const rational& r2)
{
    int n = (r1.numerator * r2.denominator) + (r1.denominator * r2.numerator);
    int d = r1.denominator * r2.denominator;
    return rational(n,d).normalize();
}

rational operator-(const rational& r1, const rational& r2)
{
    int n = (r1.numerator * r2.denominator) - (r1.denominator * r2.numerator);
    int d = r1.denominator * r2.denominator;
    return rational(n,d).normalize();
}

rational operator-(const rational& r1)
{
    return rational(r1.numerator*(-1),r1.denominator).normalize();
}

rational operator*(const rational& r1, const rational& r2)
{
    int n = r1.numerator * r2.numerator;
    int d = r1.denominator * r2.denominator;
    return rational(n,d).normalize();
}

rational operator/(const rational& r1, const rational& r2)
{
    int n = r1.numerator * r2.denominator;
    int d = r2.numerator * r1.denominator;
    return rational(n,d).normalize();
}

bool operator<(const rational& r1, const rational& r2)
{
    return (r1.numerator * r2.denominator) < (r2.numerator * r1.denominator);
}

bool operator==(const rational& r1, const rational& r2)
{
    return ((r1.numerator * r2.denominator) == (r2.numerator * r1.denominator));
}

//friend functions
bool operator!=(const rational& r1, const rational& r2)
{
    return (!(r1 == r2));
}

bool operator>(const rational& r1, const rational& r2)
{
    return (r2 < r1);
}

bool operator<=(const rational& r1, const rational& r2)
{
    return ((r1 < r2 || r1 == r2));
}

bool operator>=(const rational& r1, const rational& r2)
{
    return ((r1 > r2 || r1 == r2));
}

//input and output operators
istream& operator>>(istream& is, rational& r)
{
    int n, d;
    char ch;

    //get, check and set numerator
    is >> n;
    if(!is) return is;
    r.numerator = n;

    //get and check for / or space
    is.get(ch);
    if(ch == '\n' || ch == ' ') return is;  //if space or enter, accept the entry and move on
    else if(ch == '/')                      //look for slash if not space or enter to build rational
    {
        //if slash present > needs a denominator, get, check, check for 0, set denominator
        is >> d;
        if(!is) return is;
        if(d == 0)
        {
            cout << "Invalid input - divide by 0";
            is.clear(ios_base::failbit);
            return is;
        }

        r.denominator = d;

        return is;
    }
    else                                     //give error with invalid char entry
    {
        cout << "Invalid input - / or ' ' missing";
        is.clear(ios_base::failbit);
        return is;
    }
}

ostream& operator<<(ostream& os, const rational& r)
{
    //handle negative denominators
    if(r.denominator < 0)
    {
        if(r.numerator == 0 || r.denominator == 1)  //handle whole numbers or 0
            return os << r.numerator;
        return os << (-1) * r.numerator << "/" << (-1) * r.denominator;
    }
    else
    {
        if(r.numerator == 0 || r.denominator == 1)
            return os << r.numerator;
        return os << r.numerator << "/" << r.denominator;
    }
}

void rational_processing()
{

    cout << "\nInput two space separated integers: ";

    rational test1;
    cin >> test1;

    rational test2;
    cin >> test2;
    
    cout << "Input a rational number (Ex: 3/4): ";
    rational test3;
    cin >> test3;

    //Display test values
    cout << "\nTest1 = " << test1;
    cout << "\nTest2 = " << test2;
    cout << "\nTest3 = " << test3;

    //Test operators
    cout << "\nTest1 * Test2 equals " << test1 << " * " << test2 << " = " << test1*test2;
    cout << "\nTest1 / Test3 equals " << test1 << " / " << test3 << " = " << test1/test3;
    cout << "\nTest2 + Test3 equals " << test2 << " + " << test3 << " = " << test2+test3;
    cout << "\nTest3 - Test1 equals " << test3 << " - " << test1 << " = " << test3-test1;
    cout << "\nTest3 sign change is " << -test3;

    if(test1 == test2) cout << "\nTest1 is equal to Test2";
    else
    {
        if(test1 != test2) cout << "\nTest1 is not equal to Test2";

        if(test1 < test2) cout << "\nTest1 is less than Test2";
        if(test1 > test2) cout << "\nTest1 is greater than Test2";

    }
    
    if(test3 <= test1) cout << "\nTest3 is less than or equal to Test 1";
    if(test3 >= test1) cout << "\nTest3 is greater than or equal to Test 1";
}

void test_case()
{
    cout << "What is r1: ";
    rational r1;
    cin >> r1;
    
    cout << "What is r2: ";
    rational r2;
    cin >> r2;

    cout << "What operation (+,-,*,/) or comparison (< or >) should be performed? ";
    char operation;
    cin >> operation;

    cout << r1 << ' ' << operation << ' ' << r2 << " = ";

    switch(operation)
    {
    case '+':
    {
        cout << (r1 + r2);
        break;
    }
    case '-':
    {
        cout << (r1 - r2);
        break;
    }
    case '*':
    {
        cout << (r1 * r2);
        break;
    }
    case '/':
    {
        cout << (r1 / r2);
        break;
    }
    case '<':
    {
        if(r1 < r2)
            cout << "true";
        else
            cout << "false";
        break;
    }
    case '>':
    {
        if(r1 > r2)
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

    cout << endl << r1 << " (r1) made negative is: ";
    rational r_neg = -r1;
    cout << r_neg << endl;
}

}
