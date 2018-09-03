// Section CSC160 - Computer Science I: C++
// File Name: lesson9-699-8.cpp
// Student: Chris Scarola
// Homework Number: 9, ch 11 proj 8
// Description:
/*
  Define a class called List that can hold a list of values of type double.
Model your class definition after the class TemperatureList given in
Display 11.10, but your class List will make no reference to temperatures
when it outputs values. The values may represent any sort of data items as
long as they are of type double. Include the additional features specified in
Self-Test Exercises 21 and 22. Change the member function names so that
they do not refer to temperature.
Add a member function called get_last that takes no arguments and
returns the last item on the list. The member function get_last does not
change the list, and it should not be called if the list is empty. Add another
member function called delete_last that deletes the last element on the
list. The member function delete_last is a void function. Note that
when the last element is deleted, the member variable size must be
adjusted. If delete_last is called with an empty list as the calling object,
the function call has no effect. Design a program to thoroughly test your
definition for the class List.
 */
// Last Changed: 11/2/2016

#include "list.h"

namespace lesson9_699_8 {

using namespace std;

void run()
{
    clear_screen();

    List testList, t2;

    double temp;
    int TEST_COUNT = 50;
    
    cout << "Enter values (up to 50, or terminate with '0':\n";
    
    for(int i = 0; i < TEST_COUNT; ++i)
        {
            cin >> temp;
            if(temp == 0) break;
            testList.add_value(temp);
            t2.add_value_sort(temp);
        }

    cout << "\nThere are " << testList.get_size() << " values on the list";
    cout << "\nThe first value is " << testList.get_value(0);
    cout << "\nThe last value is " << testList.get_last();
    testList.delete_last();
    cout << "\nAfter deleting last value, there are " << testList.get_size() << " values left";
    cout << "\nThe new list is:\n" << testList << endl;
    cout << "\nSorted original list:\n" << t2 << endl;

    while(!testList.full())
        {
            testList.add_value(100.0);
        }

    cout << "\nList filled up at size equal to " << testList.get_size() << endl;   
    cout << "The new list is:\n" << testList << endl;
    
    keep_window_open("~~");
}

}
