// Section CSC160 - Computer Science I: C++
// File Name: lesson1-105.5.cpp
// Student: Chris Scarola
// Homework Number: 1
// Description:
/* The following is a short program that computes the volume of a sphere
given the radius. It will compile and run, but it does not adhere to the
program style recommended in Section 2.5. Rewrite the program using
the style described in the chapter for indentation, adding comments, and
appropriately named constants.
#include <iostream>
using namespace std;
int main()
{
double radius, vm;
cout << Enter radius of a sphere. << endl; cin >> radius;
vm = (4.0 / 3.0) * 3.1415 * radius * radius * radius;
cout <<  The volume is  << vm << endl;
return 0;
}
*/
// Last Changed: 8/24/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson1_105_5 {

using namespace std;

void run()
{
    do
    {
        clear_screen();

        cout << "Calculate the volume of a sphere\n\n";

        const double PI = 3.141592654;    //set the constant for pi
        double radius, vm;

        //Get the radius
        cout << "Enter radius of a sphere: ";
        cin >> radius;

        //Calculate the volume
        vm = (4.0 / 3.0) * PI * radius * radius * radius;

        //Output he answer
        cout << "The volume is " << vm << endl;

    }while(prompt());
}

}
