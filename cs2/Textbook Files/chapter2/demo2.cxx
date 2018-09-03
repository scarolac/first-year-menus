// FILE: demo2.cxx
// This small demonstration shows how the revised throttle class is used.
#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "throttle.h"   // Provides the throttle class
using namespace std;    // Allows all Standard Library items to be used
using main_savitch_2A::throttle;

const int DEMO_SIZE = 5;  // Number of positions in a demonstration throttle

int main( )
{
    throttle sample(DEMO_SIZE);  // A throttle to use for our demonstration
    int user_input;              // The position that we set the throttle to
    
    // Set the sample throttle to a position indicated by the user.
    cout << "I have a throttle with " << DEMO_SIZE << " positions." << endl;
    cout << "Where would you like to set the throttle?" << endl;
    cout << "Please type a number from 0 to " << DEMO_SIZE << ": ";
    cin >> user_input;
    sample.shift(user_input);

    // Shift the throttle down to zero, printing the flow along the way.
    while (sample.is_on( ))
    {
        cout << "The flow is now " << sample.flow( ) << endl;
        sample.shift(-1);
    }
    cout << "The flow is now off" << endl;
    return EXIT_SUCCESS;
}
