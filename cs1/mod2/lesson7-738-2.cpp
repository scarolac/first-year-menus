// Section CSC160 - Computer Science I: C++
// File Name: lesson7-738-2.cpp
// Student: Chris Scarola
// Homework Number: 7
// Description:
/*
  Redo (or do for the first time) Programming Project 2 from Chapter 11.
  Define your ADT class in separate files so that it can be compiled separately.
 */
// Last Changed: 10/8/2016

#include "rational.h"

namespace lesson7_738_2 {

using namespace std;

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

}
