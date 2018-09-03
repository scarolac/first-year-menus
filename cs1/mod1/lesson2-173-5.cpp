// Section CSC160 - Computer Science I: C++
// File Name: lesson2-173-5.cpp
// Student: Chris Scarola
// Homework Number: 2
// Description:
/*
  Write a program that finds and prints all of the prime numbers between 3
and 100. A prime number is a number such that 1 and itself are the only
numbers that evenly divide it (for example, 3, 5, 7, 11, 13, 17,...).
One way to solve this problem is to use a doubly nested loop. The
outer loop can iterate from 3 to 100 while the inner loop checks to see
if the counter value for the outer loop is prime. One way to see if number
n is prime is to loop from 2 to n-1 and if any of these numbers
evenly divides n, then n cannot be prime. If none of the values from 2
to n 21 evenly divides n, then n must be prime. (Note that there are
several easy ways to make this algorithm more efficient.)
 */
// Last Changed: 8/29/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson2_173_5 {

using namespace std;

void run()
{
    clear_screen();

    int prime = 3;
    int last_prime = 100;
    
    cout << "Show primes between " << prime << " and " << last_prime <<"\n\n";
    
    /*
      check primes by % to see if == 0, meaning non prime
      if it is a prime, print it
    */
    bool is_prime = true;
    for(int i = prime; i <= last_prime; ++i)
        {
            for(int j = 2; j < i; ++j)
                {
                    if(i % j == 0)
                        {
                            is_prime = false;
                        }
                }
            if(is_prime)
                {
                    prime = i;
                    cout << prime << " ";
                }
            is_prime = true;
        }

    keep_window_open("~~");
}

}
