// FILE: bag6demo.cxx
// Demonstration program for 6th version of bag
// (from bag6.h and bag6.template).
// Similar demonstration program as for earlier versions of the bag class
//  but explicitly exercises the bst_remove

#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "bag6.h"       // Provides the bag<Item> template class
using namespace std;
using namespace main_savitch_10;

// PROTOTYPES for functions used by this demonstration program:
void get_ages(bag<int>& ages);
// Postcondition: The user has been prompted to type in the ages of family
// members. These ages have been read and placed in the ages bag, stopping
// when the user types a negative number.

void count_ages(bag<int>& ages);
// Postcondition: The user has been prompted to type in an age
// The function tells the user whether that age has been entered
// The function stops prompting when a negative age is entered

void remove_ages(bag<int>& ages);
// Postcondition: The user has been prompted to type in an age
// The function tells the user whether that age has been removed
// The function stops prompting when a negative age is entered

int main( )
{
    bag<int> ages;

    get_ages(ages);
    cout << "You entered " << ages.size() << " ages." << endl;
    count_ages(ages);
    remove_ages(ages);
    cout << "There are " << ages.size() << " ages remaining." << endl;
    system("Pause");
    return EXIT_SUCCESS;  
}


void get_ages(bag<int>& ages)
{
    int user_input = 0; // An age from the user's family

    cout << "Type the ages in your family. " << endl;
    cout << "(Type a negative number when you are done)" << endl;
    cin >> user_input;
    while (user_input >= 0)
    {
        ages.insert(user_input);
        cin >> user_input;
    }
}

void count_ages(bag<int>& ages)
{
    int user_input = 0; // An age from the user's family
    cout << "Please enter an age to count (enter negative when done): " ;
    cin >> user_input;
    while (user_input >= 0)
    {
        if (ages.count(user_input) > 0)
            cout << "Yes, you entered " << user_input << " " << ages.count(user_input) << " time(s)" << endl;
        else
            cout << "No, that age does not occur" << endl;
        cout << "Please enter an age to count (enter negative when done): " ;
        cin >> user_input;
    }
}

void remove_ages(bag<int>& ages)
{
    int user_input = 0; // An age from the user's family
    cout << "Please enter an age to remove (enter negative when done): " ;
    cin >> user_input;
    while (user_input >= 0)
    {
        if (ages.erase_one( user_input))
           cout << "Removed one occurrence of that age" << endl;
        else
            cout << "No, that age does not occur" << endl;
        cout << "Please enter an age to remove (enter negative when done): " ;
        cin >> user_input;
    }
}

