/* Section CSC 160 Comp Sci I : C++
** Name:
** Student ID:
** File name: Lesson9-5-431.cpp
** Last Updated :

** Array program that reads a file and counts
the occurances of the numbers in the array and sorts them.

*/
#include "cs1/mod3/cs1mod3.h"

namespace lesson9_441_5 {

using namespace std;

void check_input(ifstream& iPut);
void set_array(ifstream& iPut, int test[29]);
void sort_array(int test[29]);
void check_repeats(int test[29]);

void run()
{
    clear_screen();

    ifstream iPut;
    int test[29];

    cout << "Homework 9: Solution to Chapter 7 Project 5" << endl;
    cout << "\n";

    iPut.open("hw10input.txt");

    check_input(iPut);

    set_array(iPut, test);

    check_repeats(test);

    iPut.close();

    keep_window_open("~~");
}

void check_input(ifstream& iPut)
{
    if(iPut.fail())
    {
        cout << "Input file opening failed. \n";
        exit(1);
    }
}

void set_array(ifstream& iPut, int test[29])
{
    for (int i = 0; i < 29; i++)
    {
        iPut >> test[i];
    }

    sort_array(test); // Call to selecting sort to sort array before output.

}

void sort_array(int test[29]) // Decending selection sort borrowed from a java program from CSC 116
{
    int i, j, first, temp;
    for (i = 28; i > 0; i --)
    {
        first = 0;
        for (j =1; j <= i; j++)
        {
            if (test[j] < test[first])
                first = j;
        }
        temp = test[first];
        test[first] = test[i];
        test[i] = temp;
    }
}

void check_repeats(int test[29])
{
    for(int i = 0; i < 29; i++)
    {
        int count = 0;
        int flag = 1;
        for ( int j = 0; j < i; j++) // First pass through array
        {
            if (test[i] == test[j])
                flag += 1;
        }
        if ( flag == 1 ) // Flag to do a second pass
        {
            for(int k = 0; k < 29; k++)
            {
                if (test[i] == test[k])
                    count += 1;
            }

            cout << test[i] << " " << count <<endl;
        }
    }
}

}


