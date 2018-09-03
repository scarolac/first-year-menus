// FILE: pqtest2.cpp
// An interactive test program for the Priority Queue class
#include <cctype>     // Provides toupper
#include <iostream>  // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS and size_t
#include "pqueue2.h"   // Implemented using a heap
using namespace std;

// PROTOTYPES for functions used by this test program:
void print_menu( );
char get_user_command( );
int get_number(const char message[ ]);
void add_multiple_entries(PriorityQueue &q);

int main( )
{
    PriorityQueue test;
    char choice;
    cout << "CSC-161 Lesson Ten Test Program" << endl << endl;
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
            case 'M':
                add_multiple_entries(test);
                break;
            case 'P':
                test.print_tree("Contents of heap:");
                break;
            case 'S': 
				cout << "The size is " << test.size( ) << endl;
				break;
            case 'X': 
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
    cout << " M   Add multiple items with varying priorities " << endl;
    cout << " P   Print the internal heap using the print_tree(...) function" << endl;
    cout << " S   Print the result from the size( ) function" << endl;
    cout << " X   Extract and print values in priority order" << endl;
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
void add_multiple_entries(PriorityQueue &thisQueue)
{
    thisQueue.insert(100, 10);
    thisQueue.insert(200, 10);
    thisQueue.insert(300, 5);
    thisQueue.insert(400, 5);
    thisQueue.insert(500, 20);
    thisQueue.insert(600, 20);
    thisQueue.insert(700, 20);
    thisQueue.insert(800, 10);
    thisQueue.insert(900, 10);
    return;
}
