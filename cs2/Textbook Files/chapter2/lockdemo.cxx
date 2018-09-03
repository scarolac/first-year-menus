// File: lockdemo.cxx
// This program demonstrates using the lock class from lecture.
// It illustrates material from Chapter 2 of the text.

#include <iostream>  // Provides cin and cout
#include <cstdlib>   // Provides EXIT_SUCCESS
#include "lock.h"    // Provides the lock class
using namespace std;
using namespace main_savitch_2;

int main( )
{
    lock my_bike_lock(14, 36, 10);
    int number[3];
    
    cout << "Guess the 3 numbers of the combination: "
	 << endl;
    cin >> number[0] >> number[1] >> number[2];

    my_bike_lock.turn(number[0], true, 1);
    my_bike_lock.turn(number[1], false, 1);
    my_bike_lock.turn(number[2], true, 0);

    my_bike_lock.try_to_open( );

    if (my_bike_lock.is_open( ))
	cout << "Right!" << endl;
    else
	cout << "Wrong!" << endl;

    return EXIT_SUCCESS;
}
