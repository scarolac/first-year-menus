// Section CSC160 - Computer Science I: C++
// File Name: rational.h
// Student: Chris Scarola
// Homework Number: 7
// Description: header for rational clas
// Last Changed: 10/10/2016

#ifndef RATIONAL_H
#define RATIONAL_H

#include "cs1/mod2/cs1mod2.h"

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

bool prompt();
//prompts the user to continue

void keep_window_open(std::string s);
//holds the window open until the string "~~" is entered

#endif 
