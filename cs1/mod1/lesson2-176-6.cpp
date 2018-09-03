// Section CSC160 - Computer Science I: C++
// File Name: lesson2-176-6.cpp
// Student: Chris Scarola
// Homework Number: 2
// Description: 
/*
  The Fibonacci numbers Fn are defined as follows. F0 is 1, F1 is 1, and
Fi+2 = Fi + Fi+1
i = 0, 1, 2,... In other words, each number is the sum of the previous
two numbers. The first few Fibonacci numbers are 1, 1, 2, 3, 5, and 8. One
place that these numbers occur is as certain population growth rates. If a
population has no deaths, then the series shows the size of the population
after each time period. It takes an organism two time periods to mature to
reproducing age, and then the organism reproduces once every time period.
The formula applies most straightforwardly to asexual reproduction
at a rate of one offspring per time period.
Assume that the green crud population grows at this rate and has a time period
of 5 days. Hence, if a green crud population starts out as 10 pounds of
crud, then in 5 days there is still 10 pounds of crud; in 10 days there is 20
pounds of crud, in 15 days 30 pounds, in 20 days 50 pounds, and so forth.
Write a program that takes both the initial size of a green crud population
(in pounds) and a number of days as input, and that outputs the number
of pounds of green crud after that many days. Assume that the population
size is the same for 4 days and then increases every fifth day. Your program
should allow the user to repeat this calculation as often as desired.
 */
// Last Changed: 8/29/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson2_176_6 {

using namespace std;

void run()
{
    do
    {
        int pounds_crud, days_alive, time_periods, F_0, F_1, final_pounds;    //F0 and 1 are first in fib sequence

        clear_screen();

        cout << "Fibonacci sequence with green crud\n";

        //get the data
        cout << "\nHow much crud to start, in pounds? ";
        cin >> pounds_crud;
        cout << "How many days has the crud been alive? ";
        cin >> days_alive;
        time_periods = days_alive / 5;

        F_0 = pounds_crud;    //"It takes an organism two time periods to mature to reproducing age"
        F_1 = pounds_crud;
        final_pounds = pounds_crud;

        for(int i = 0; i < time_periods; ++i)
        {
            /*
                      fib = fib[i-1] + fib[i-2];
                    */
            if(i == 0)
            {
                final_pounds = F_1; //since both F0 and 1 are the initial
                //and it has to wait 1 iteration before multiplying
            }
            else
            {
                final_pounds = F_1 + F_0;
                F_0 = F_1;
                F_1 = final_pounds;    //for the next iteration, the original F0 and 1 increment
            }
        }

        //output response
        cout << "After " << days_alive << " days, the green crud will be "
             << final_pounds << " pounds\n";

    }
    while(prompt());
}

}
