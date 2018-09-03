// Section CSC160 - Computer Science I: C++
// File Name: lesson4-373-10.cpp
// Student: Chris Scarola
// Homework Number: 4
// Description:
/*
  The text file babynames2012.txt, which is included in the source code for
this book and is available online from the book's Web site, contains a list
of the 1000 most popular boy and girl names in the United States for the
year 2012 as compiled by the Social Security Administration.
This is a space-delimited file of 1000 entries in which the rank is listed
first, followed by the corresponding boy name and girl name. The most
popular names are listed first and the least popular names are listed last.
For example, the file begins with
1 Jacob Sophia
2 Mason Emma
3 Ethan Isabella

This indicates that Jacob is the most popular boy name and Sophia is the
most popular girl name. Mason is the second most popular boy name and
Emma is the second most popular girl name.
Write a program that allows the user to input a name. The program
should then read from the file and search for a matching name among the
girls and boys. If a match is found, it should output the rank of the name.
The program should also indicate if there is no match.
For example, if the user enters the name "Justice," then the program
should output:
Justice is ranked 519 in popularity among boys.
Justice is ranked 518 in popularity among girls.
If the user enters the name "Walter," then the program should output:
Walter is ranked 376 in popularity among boys.
Walter is not ranked among the top 1000 girl names.

 */
// Last Changed: 9/14/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson4_373_10 {

void search_names();
//searches names based on user input

void run()
{    
    clear_screen();

    search_names();    

    keep_window_open("~~");
}

void search_names()
{
    using namespace std;

    cout << "Enter name: ";
    string name_input;
    cin >> name_input;

    //ignores the case of the input by user
    string no_case_name = "";
    for(uint i = 0; i < name_input.size(); ++i)
        no_case_name += tolower(name_input[i]);

    //open the file to check the name
    ifstream in_stream;
    in_stream.open("babynames2012.txt");
    if(in_stream.fail())
        {
            cout << "Input file opening failed.\n";
            return;
        }

    //search the names
    int position;
    bool is_boy = false;
    bool is_girl = false;
    string boy_name;
    string girl_name;

    //strings to hold lower case
    string boy_no_case = "";
    string girl_no_case = "";
    while(in_stream >> position >> boy_name >> girl_name)
        {
            for(uint i = 0; i < boy_name.size(); ++i)    //make lower case boys
                boy_no_case += tolower(boy_name[i]);

            for(uint j = 0; j < girl_name.size(); ++j)   //make lower case girls
                girl_no_case += tolower(girl_name[j]);
            
            if(no_case_name == boy_no_case)
                {
                    cout << name_input << " is ranked " << position
                         << " among boys.\n";
                    is_boy = true;
                        
                }
            if(no_case_name == girl_no_case)
                {
                    cout << name_input << " is ranked " << position
                         << " among girls.\n";
                    is_girl = true;
                }

            //have to reset the no cases each time otherwise it is a long string
            boy_no_case = "";
            girl_no_case = "";
        }
    if(!is_boy) cout << name_input << " is not ranked among the top 1000 names for boys.\n";
    if(!is_girl) cout << name_input << " is not ranked among the top 1000 names for girls.\n";

    in_stream.close();    
}

}
