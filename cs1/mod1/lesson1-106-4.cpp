// Section CSC160 - Computer Science I: C++
// File Name: lesson1-106.4.cpp
// Student: Chris Scarola
// Homework Number: 1
// Description:
/* Negotiating a consumer loan is not always straightforward. One form of
loan is the discount installment loan, which works as follows. Suppose a
loan has a face value of $1,000, the interest rate is 15%, and the duration
is 18 months. The interest is computed by multiplying the face value of
$1,000 by 0.15, to yield $150. That figure is then multiplied by the loan
period of 1.5 years to yield $225 as the total interest owed. That amount is
immediately deducted from the face value, leaving the consumer with only
$775. Repayment is made in equal monthly installments based on the face
value. So the monthly loan payment will be $1,000 divided by 18, which
is $55.56. This method of calculation may not be too bad if the consumer
needs $775 dollars, but the calculation is a bit more complicated if the
consumer needs $1,000. Write a program that will take three inputs: the
amount the consumer needs to receive, the interest rate, and the duration
of the loan in months. The program should then calculate the face value
required in order for the consumer to receive the amount needed. It should
also calculate the monthly payment. Your program should allow the calculations
to be repeated as often as the user wishes.
*/
// Last Changed: 

#include "cs1/mod1/cs1mod1.h"
namespace lesson1_106_4 {

using namespace std;

void run()
{
    double net;
    double interest_rate;
    int duration;
    double loan_amount;
    double loan_payment;

    do
    {
        clear_screen();

        cout << "Discount installment loan calculator\n\n";

        //get the data
        cout << "How much money do you need? $";
        cin >> net;
        cout << "What is the interest rate (in %)? ";
        cin >> interest_rate;
        interest_rate /= 100;
        cout << "How long in months is the payback period? ";
        cin >> duration;

        //calculate the loan amount needed to get them the money they need
        loan_amount = net / (1 - (interest_rate * (duration / 12.0)));
        loan_payment = loan_amount / duration;

        cout << "\nThe total loan is $" << loan_amount
             << "\nwith a monthly payment of $" << loan_payment << " per month\n\n";
    }
    //loop if the user wants to calculate a loan
    while(prompt());
}

}
