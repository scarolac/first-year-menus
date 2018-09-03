// Section CSC160 - Computer Science I: C++
// File Name: lesson3-245-3.cpp
// Student: Chris Scarola
// Homework Number: 3
// Description:
/*
  The price of stocks is sometimes given to the nearest eighth of a dollar; for
example, 29 7/8 or 89 1/2. Write a program that computes the value of the
users holding of one stock. The program asks for the number of shares of
stock owned, the whole-dollar portion of the price, and the fraction portion.
The fraction portion is to be input as two int values, one for the numerator
and one for the denominator. The program then outputs the value of the
users holdings. Your program should allow the user to repeat this calculation
as often as the user wishes and will include a function definition that has
three int arguments consisting of the whole-dollar portion of the price and
the two integers that make up the fraction part. The function returns the price
of one share of stock as a single number of type double.
 */
// Last Changed: 9/9/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson3_245_3 {

void intro();
//introduces the program

void get_data(int& owned, int& whole, int& numer, int& denom);
//precondition: needs amount of shares owned, whole price with numerator and denominator
//post: updates the variables by reference in main()

double share_price(int& owned, int& whole, int& numer, int& denom);
//precondition: takes get_data() input, number of shares >= 0, the whole dollar
//value followed by the numerator and denominator where denom > 0
//returns the value of the stocks

void output_data(int& owned, int& whole, int& numer, int& denom, double price);
//outputs the original data and the share price

void run()
{
    int shares_owned, whole_dollar, numerator, denominator;


    do
    {
        clear_screen();

        intro();

        get_data(shares_owned, whole_dollar, numerator, denominator);

        output_data(shares_owned, whole_dollar, numerator, denominator,
                    share_price(shares_owned, whole_dollar, numerator, denominator));
    }
    while(prompt());

}

void intro()
{
    using namespace std;
    cout << "Stock value calculator\n"
         << "Calculated stock value based on input of one share price \n"
         << "using nearest 1/8th of a dollar\n";
}

void get_data(int& owned, int& whole, int& numer, int& denom)
{
    using namespace std;
    cout << "\nEnter the number of shares owned: ";
    cin >> owned;
    cout << "Enter the whole dollar price on one share: $";
    cin >> whole;
    cout << "Enter the numerator: ";
    cin >> numer;
    cout << "Enter the denominator: ";
    while(cin >> denom)
    {
        if(denom == 0)
        {
            cout << "Denominator cannot be zero (0), input again: ";
        }
        else break;
    }
}

double share_price(int& owned, int& whole, int& numer, int& denom)
{
    double fraction = static_cast<double>(numer)/denom;
    double value  = static_cast<double>(whole) + fraction;
    if (owned < 0) return 0.0;
    
    return (value * owned);
}

void output_data(int& owned, int& whole, int& numer, int& denom, double price)
{
    using namespace std;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "\nShares owned: " << owned
         << "\nPrice per share: $" << whole << " " << numer << "/" << denom
         << " or $" << static_cast<double>(whole) + static_cast<double>(numer)/denom
         << "\nTotal value of shares: $" << price << endl;
}

}
