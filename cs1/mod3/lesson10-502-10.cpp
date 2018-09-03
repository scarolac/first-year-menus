// Section CSC160 - Computer Science I: C++
// File Name: lesson10-502-10.cpp
// Student: Chris Scarola
// Homework Number: 10
// Description:
/*
 pg 441 ch 7, proj 5:
 Write a program that reads in a list of integers into an array with base
type int. Provide the facility to either read this array from the keyboard or
from a file, at the user's option. If the user chooses file input, the program
should request a file name. You may assume that there are fewer than
50 entries in the array. Your program determines how many entries there
are. The output is to be a two-column list. The first column is a list of the
distinct array elements; the second column is the count of the number of
occurrences of each element. The list should be sorted on entries in the first
column, largest to smallest.
For example, for the input
-12 3 -12 4 1 1 -12 1 -1 1 2 3 4 2 3 -12
the output should be
N Count
4 2
3 3
2 2
1 4
-1 1
-12 4
  Redo Programming Project 5 from Chapter 7, but this time use vectors
instead of arrays. You should do either Programming Project 8 or 9 before
doing this one. However, you will need to write your own (similar) sorting
code for this project rather than using the sorting function from Programming
Project 7 or 8 with no changes.
 */
// Last Changed: 11/9/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson10_502_10 {

using namespace std;

void check_input(ifstream& iPut); //throw (int);
//check the input file can open

void set_vector(ifstream& iPut, vector<int>& v);
//add data to vector from input and call sort function

void sort_vector(vector<int>& v);
//sort the vector elements

void check_repeats(vector<int>& v);
//check for repeated elements and count them

void run()
{
    try
    {
        clear_screen();

        cout << "Homework 10: Solution to Chapter 7 project 5, with vectors\n" << endl;
        ifstream ifs;
        vector<int> test;

        ifs.open("hw10input.txt");
        check_input(ifs);

        set_vector(ifs,test);

        check_repeats(test);

        ifs.close();

    }
    catch(int e)
    {
        //Error output from function, intentionally blank
    }
    catch(...)
    {
        cout << "Unknown error\n";
    }
    

    keep_window_open("~~");
}

void check_input(ifstream& iPut) //throw (int)
{
    if(iPut.fail())
    {
        cout << "Input file opening failed. \n";
        throw 1;
    }
}

void set_vector(ifstream& iPut, vector<int>& v)
{
    int temp;
    
    while(iPut >> temp)
    {
        v.push_back(temp);
    }

    sort_vector(v); //Call to selecting sort to sort vector before output.
}

void sort_vector(vector<int>& v) //Decending selection sort borrowed from a the given .cpp file
{
    int i, j, first, temp;
    for (i = v.size(); i > 0; --i)
    {
        first = 0;
        for (j = 1; j <= i; j++)
        {
            if (v[j] < v[first])
                first = j;
        }
        temp = v[first];
        v[first] = v[i];
        v[i] = temp;
    }
}

void check_repeats(vector<int>& v)
{
    cout << "N  count\n";
    
    for(uint i = 0; i < v.size(); i++)
    {
        int count = 0;
        int flag = 1;
        for (uint j = 0; j < i; j++) // First pass through array
        {
            if (v[i] == v[j])
                flag += 1;
        }
        if ( flag == 1 ) // Flag to do a second pass
        {
            for(int k = 0; k < 29; k++)
            {
                if (v[i] == v[k])
                    count += 1;
            }

            cout << v[i] << " " << count <<endl;
        }
    }
}

}


