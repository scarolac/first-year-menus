// Section CSC160 - Computer Science I: C++
// File Name: lesson3-246-6.cpp
// Student: Chris Scarola
// Homework Number: 3
// Description:
/*
  Write a function declaration for a function that computes interest on a credit
card account balance. The function takes arguments for the initial balance,
the monthly interest rate, and the number of months for which interest must
be paid. The value returned is the interest due. Do not forget to compound
the interest that is, to charge interest on the interest due. The interest due
is added into the balance due, and the interest for the next month is computed
using this larger balance. Use a while loop that is similar to (but need
not be identical to) the one shown in Display 2.14. Embed the function in
a program that reads the values for the interest rate, initial account balance,
and number of months, then outputs the interest due. Embed your function
definition in a program that lets the user compute interest due on a credit
account balance. The program should allow the user to repeat the calculation
until the user says he or she wants to end the program.
 */
// Last Changed: 9/9/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson3_246_6 {

void intro();
//introduces the program

void get_data(double& bal, double& rate, int& m);
//precondition: balance, months(m) are real and rate > 0
//post: sets variables from user input

double interest_cost(double& bal, double rate, int& m);
//precondition: uses values from get_data() function
//returns the total interest accumulated

void output_data(double& bal, double& rate, int& m, double cost);
//outputs to user the calculated data

void run()
{
    double balance, interest_rate;
    int months;
    
    do
    {
        clear_screen();

        intro();

        get_data(balance, interest_rate, months);

        output_data(balance, interest_rate, months,
                    interest_cost(balance, interest_rate, months));
    }
    while(prompt());
}

void intro()
{
    using namespace std;
    cout << "Credit card interest calculator\n"
         << "Calculates interest owed based on balance and duration in months\n";
}

void get_data(double& bal, double& rate, int& m)
{
    using namespace std;
    cout << "\nInput credit card balance: $";
    cin >> bal;
    cout << "Input monthly interest rate in %: ";
    while(cin >> rate)
    {
        if(rate < 0) cout << "Interest must be greater than 0%: ";
        else break;
    }
    cout << "Duration bill has run in months: ";
    cin >> m;
}

double interest_cost(double& bal, double rate, int& m)
{
    double cost = bal;
    rate /= 100;    //input is in normal % and must be converted
    
    for(int i = 0; i < m; ++i)
        cost *= (1 + rate);
    cost -= bal;
    
    return cost;
}

void output_data(double& bal, double& rate, int& m, double cost)
{
    using namespace std;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "\nAfter " << m << " months, with card balance $"
         << bal << " and interest rate " << rate
         << "%, \nInterest accumulated is: $" << cost << endl;
}

}
