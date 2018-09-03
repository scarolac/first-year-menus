// Section CSC160 - Computer Science I: C++
// File Name: lesson1-104-2.cpp
// Student: Chris Scarola
// Homework Number: 1
// Description:
/* The Babylonian algorithm to compute the square root of a number n is as
follows:
1. Make a guess at the answer (you can pick n/2 as your initial guess).
2. Compute r = n / guess
3. Set guess = (guess + r) / 2
4. Go back to step 2 for as many iterations as necessary. The more that
steps 2 and 3 are repeated, the closer guess will become to the square
root of n.
Write a program that inputs a double for n and iterates through the
Babylonian algorithm 100 times. For a more challenging version, iterate
until guess is within 1% of the previous guess, and outputs the answer as
a double.
*/
// Last Changed: 8/24/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson1_104_2
{

using namespace std;

void run()
{
    do
    {
        clear_screen();

        cout << "Computing the babylonian estimated sqrt of a number\n\n";
        double number;
        double guess;
        double r;

        //get the data and initial guess
        cout << "Input a number to take the sqrt of: ";
        cin >> number;
        guess = number / 2;

        //calculate the root
        double prev_guess;
        double guess_ratio = 1.0;   //ratio is stored until it is within 1% of the value
        while(guess_ratio > 0.01)
        {
            if (number == 1)    //the sqrt of 1 is 1
            {
                guess = 1;
                break;
            }

            prev_guess = guess;

            //algorithm from the text to calculate the root
            r = number / guess;
            guess = (guess + r) / 2;

            guess_ratio = (prev_guess - guess) / guess;
        }

        //show the answer
        cout << "The estimated sqrt of " << number << " is " << guess << endl;
    }while(prompt());
}

}
