// FILE: shortHomeworkFour.cxx
// Simple Test Program for grading and evaluating the
//  Sequence class


#include <iostream>     // Provides cout.
#include <cstdlib>      // Provides size_t.
#include <string>
#include "sequence3.h"  // Provides a double type sequence class implemented by a linked list
using namespace std;
using namespace main_savitch_5;

void keep_window_open(std::string s)
{
    using namespace std;
    cout << endl;

    if (s=="") return;
    cin.clear();
    for (;;)
        {
            cout << "Please enter " << s << " to exit\n";
            string ss;
            while (cin >> ss && ss!=s)
                cout << "Please enter " << s << " to exit\n";
            return;
        }
}

void printSequence(sequence);
int main( )
{
    cout << "****************************************" << endl;
    cout << "Homework Four Basic Test Program" << endl;
   
 // Start by creating a new Sequence object
 // And testing its initial values
    cout << "****************************************" << endl;
    cout << "Creating first sequence object" << endl;
    sequence testOne;
    printSequence(testOne);
 // Add some items to the sequence using insert
    cout << "****************************************" << endl;
    cout << "Add three values using Insert" << endl;
    testOne.insert(100.0);
    testOne.insert(200.0);
    testOne.insert(300.0);
    printSequence(testOne);
 // Add some items to the sequence using attach
    cout << "****************************************" << endl;
    cout << "Add three values using Attach/Insert" << endl;
    testOne.attach(210.0);
    testOne.insert(220.0);
    testOne.insert(230.0);
    printSequence(testOne);
 // Remove two items 
    cout << "****************************************" << endl;
    cout << "Remove two values using Remove_current" << endl;
    testOne.remove_current();
    testOne.remove_current();
    printSequence(testOne);
 // Test the copy constructor
    cout << "****************************************" << endl;
    cout << "Testing the copy constructor" << endl;
    sequence testTwo(testOne);
    printSequence(testTwo);
 
    keep_window_open("~~");
    return 0;

}

void printSequence(sequence thisSequence)
{
     // Displays the current state of a sequence object
    cout << "Current Size: " << thisSequence.size() << endl;
    if (thisSequence.is_item())
    {
       cout << "Current value of is_item is True" << endl;
       cout << "Current value: " << thisSequence.current() << endl;
    }
    else
       cout << "Current value of is_item is False" << endl;
    if (thisSequence.size() > 0)
    {
       cout << "Sequence values:" << endl;
       for (thisSequence.start(); thisSequence.is_item(); thisSequence.advance())
           cout << thisSequence.current() << endl;
    }
       
}
     
