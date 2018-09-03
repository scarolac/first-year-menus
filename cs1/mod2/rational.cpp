// Section CSC160 - Computer Science I: C++
// File Name: rational.cpp
// Student: Chris Scarola
// Homework Number: 7
// Description: rational class definitions file
// Last Changed: 10/10/2016

#include <cmath>
#include "rational.h"


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


