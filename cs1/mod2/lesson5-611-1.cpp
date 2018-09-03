// Section CSC160 - Computer Science I: C++
// File Name: lesson5-611-1.cpp
// Student: Chris Scarola
// Homework Number: 5
// Description:
/*
  Redefine CDAccount from Display 10.1 so that it is a class rather than a
structure. Use the same member variables as in Display 10.1 but make
them private. Include member functions for each of the following: one
to return the initial balance, one to return the balance at maturity, one to
return the interest rate, and one to return the term. Include a constructor
that sets all of the member variables to any specified values, as well as a
default constructor. Embed your class definition in a test program.
 */
// Last Changed: 9/28/2016

#include "cs1/mod2/cs1mod2.h"

namespace lesson5_611_1 {

using namespace std;

class CDAccount
{
private:
    double balance;
    double interest_rate;
    int term;
    
public:
    CDAccount();
    //default constructor sets everything to 0
    
    CDAccount(int bal, double rate, int t);
    //contstructor allows setting of values
    
    double get_balance() { return balance; }
    double get_interest_rate() { return interest_rate; }
    int get_term() { return term; }

    double maturity_balance();
    //returns the balance with interest after the term length
};

void output_account(CDAccount& act);
//outputs different accounts

void run()
{
    clear_screen();

    cout << "test1 account" << endl;
    CDAccount test1(5000, 18, 9);
    output_account(test1);

    cout << "book_numbers account" << endl;
    CDAccount book_numbers(100, 10, 6); 
    output_account(book_numbers);

    keep_window_open("~~");
}

CDAccount::CDAccount() : balance(0.0), interest_rate(0.0), term(0) {}

CDAccount::CDAccount(int bal, double rate, int t)
    : balance(bal), interest_rate(rate), term(t)
{
    if (bal < 0 || rate < 0 || term < 0)
        {
            cout << "\nInvalid values for balance, interest rate, or term.\n\n";
        }
}

double CDAccount::maturity_balance()
{
    return (balance + (balance * (interest_rate / 100.0) * (term/12.0)));
    //balance + interest over term
}

void output_account(CDAccount& act)
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    cout << "Initial Balance: $" << act.get_balance() << endl
         << "Interest rate: " << act.get_interest_rate() << "%" << endl
         << "Term (months): " << act.get_term() << endl;

    cout << "Account value after " << act.get_term()
         << " months will be $" << act.maturity_balance() << endl << endl;
}

}
