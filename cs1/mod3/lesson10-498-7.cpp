// Section CSC160 - Computer Science I: C++
// File Name: lesson10-498-7.cpp
// Student: Chris Scarola
// Homework Number: 10
// Description:
/*
  Write a program that inputs two string variables, first and last, each of
which the user should enter with his or her name. First, convert both strings
to all lowercase. Your program should then create a new string that contains
the full name in Pig Latin with the first letter capitalized for the first and last
name. The rules to convert a word into Pig Latin are as follows:
If the first letter is a consonant, move it to the end and add "ay" to the end.
If the first letter is a vowel, add "way" to the end.
For example, if the user inputs "Erin" for the first name and "Jones" for
the last name, then the program should create a new string with the text
"Erinway Onesjay" and print it.
 */
// Last Changed: 11/9/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson10_498_7 {

using namespace std;

string make_lower(const string& s);
//return the lower case of a string

string capitalize(const string& s);
//capitalize the first letter of a string

string pig_latinize(const string& s);
//converts word into pig latin version with the rules:
//If the first letter is a consonant, move it to the end and add "ay" to the end
//If the first letter is a vowel, add "way" to the end

void run()
{
    do
    {
        clear_screen();

        string first, last, full_name;

        cout << "Enter your first name.\n";
        cin >> first;
        first = make_lower(first);
        first = pig_latinize(first);

        cout << "Enter your last name.\n";
        cin >> last;
        last = make_lower(last);
        last = pig_latinize(last);

        full_name = capitalize(first) + " " + capitalize(last);

        cout << "Your name in pig latin is: " << full_name << endl;

    }
    while(prompt());

    keep_window_open("~~");
}

string make_lower(const string& s)
{
    string temp(s);
    for(uint i = 0; i < s.length(); ++i)
        temp[i] = tolower(s[i]);
    return temp;
}

string capitalize(const string& s)
{
    string temp(s);
    temp[0] = toupper(s[0]);
    return temp;
}

string pig_latinize(const string& s)
{
    //in this program, the strings are lower case before this call, only lowers need to be checked
    bool is_leading_vowel = (s[0] == 'a' || s[0] == 'e' ||
            s[0] == 'i' || s[0] == 'o' || s[0] == 'u' || s[0] == 'y');
    string temp(s);
    char first_letter = s[0];
    
    if(is_leading_vowel)
    {
        temp += "way";
    }
    else
    {
        for(uint i = 0; i < temp.length(); ++i)
        {
            temp[i] = temp[i+1];
        }
        temp[temp.length() - 1] = first_letter;
        temp += "ay";
    }

    return temp;
}

}
