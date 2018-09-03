// FILE: pqtest.cxx
// An interactive test program for the Priority Queue class
#include <cctype>     // Provides toupper
#include <iostream>  // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS and size_t
#include "pqueue1.h"   // With Item defined as int
using namespace std;

// PROTOTYPES for functions used by this test program:
void print_menu( );
char get_user_command( );
int get_number(const char message[ ]);

int main( )
{
    PriorityQueue test;
    char choice;
    cout << "CSC-161 Exam Two Program" << endl << endl;
    do
    {
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'E':
                if (test.is_empty( ))
					cout << "The Priority Queue is empty." << endl;
                else
					cout << "The Priority Queue is not empty." << endl;
	            break;
            case 'G':
				if (!test.is_empty( ))
					cout << "Front item is: " << test.get_front( ) << endl;
				else
					cout << "There is no current item." << endl;
				break;
            case 'I':
				test.insert(get_number("Please enter the next item: "),
					(unsigned int) get_number("The item's priority: "));
				break;
            case 'S': 
				cout << "The size is " << test.size( ) << endl;
				break;
            case 'P': 
                if (test.is_empty( ))
					cout << "The Priority Queue is empty." << endl;
				else
					while(!test.is_empty())
						cout << "Value: " << test.get_front() << endl;
				break;
            case 'Q': 
				break;
            default:  
				cout << choice << " is an invalid choice." << endl;
        }
    }
    while ((choice != 'Q'));
    return EXIT_SUCCESS;
}

void print_menu( )
{
    cout << endl; 
    cout << "The following choices are available: " << endl;
    cout << " E   Print the result from the is_empty( ) function" << endl;
    cout << " G   Print the result from the get_front( ) function" << endl;
    cout << " I   Insert a new item with the insert(...) function" << endl;
    cout << " S   Print the result from the size( ) function" << endl;
    cout << " P   Extract and print values in priority order" << endl;
    cout << " Q   Quit this test program" << endl;
}

char get_user_command( )
{
    char command;
    cout << "\nEnter choice: ";
    cin >> command; 
    return command;
}

int get_number(const char message[ ])
{
    int result;
	cout << message;
    cin  >> result;
    return result;
}
