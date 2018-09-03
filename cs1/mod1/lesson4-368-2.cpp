// Section CSC160 - Computer Science I: C++
// File Name: lesson4-368-2.cpp
// Student: Chris Scarola
// Homework Number: 4
// Description:
/*
  Write a program that takes its input from a file of numbers of type double
and outputs the average of the numbers in the file to the screen. The file
contains nothing but numbers of type double separated by blanks and/or
line breaks. If this is being done as a class assignment, obtain the file name
from your instructor.
 */
// Last Changed: 9/14/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson4_368_2 {

void read_file_average();
//reads from the given file of doubles, calculates and returns the average and count of values

void run()
{
    clear_screen();

    read_file_average();
    
    keep_window_open("~~");
}

void read_file_average()
{
    
    using namespace std;
    
    ifstream in_stream;    //holds the input stream, the file that is opened
    double sum = 0;        //will be used to calculate the average
    double value;          //the actual value in the file, pulls one at a time
    int count = 0;         //counts how many values, to calculate the average
    //char file_name[17];

    //cout << "Enter the file name(16 char max): ";
    //cin >> file_name;

    in_stream.open("hw4pr01input.txt");
    if(in_stream.fail())   //if the file fails to open, leave the program with no average
        {
            cout << "Input file opening failed\n";
            return;
        }
    
    while(in_stream >> value)
        {
            sum = sum + value;
            count++;
        }
    if(count == 0) cout << "No values to average\n";
    else
        cout << "Average of " << count << " numbers is " << sum/count << endl; 
    
}

}
