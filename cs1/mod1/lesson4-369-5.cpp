// Section CSC160 - Computer Science I: C++
// File Name: lesson4-369-5.cpp
// Student: Chris Scarola
// Homework Number: 4
// Description:
/*
  Write a program that gives and takes advice on program writing. The program
starts by writing a piece of advice to the screen and asking the user to
type in a different piece of advice. The program then ends. The next person
to run the program receives the advice given by the person who last ran
the program. The advice is kept in a file, and the contents of the file change
after each run of the program. You can use your editor to enter the initial
piece of advice in the file so that the first person who runs the program
receives some advice. Allow the user to type in advice of any length so that
it can be any number of lines long. The user is told to end his or her advice
by pressing the Return key two times. Your program can then test to see
that it has reached the end of the input by checking to see when it reads
two consecutive occurrences of the character '\n'.
 */
// Last Changed: 9/14/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson4_369_5 {

void give_advice();
//opens the file as input to give the advice

void update_advice();
//opens the file as output to update the advice from user input

void run()
{
    clear_screen();

    give_advice();

    update_advice();

    keep_window_open("~~");
}

void give_advice()
{
    using namespace std;

    cout << "\tPROGRAMMING ORACLE\n"
         << "I will give advice on programming, you must return advice to me\n"
         << "Here is your advice: \n\n";

    //open the input file
    ifstream in_stream;
    char next;
    string advice = "";
    in_stream.open("hw4pr02input.txt");
    if(in_stream.fail())
        {
            cout << "Input file opening failed.\n";
            return;
        }

    //loop through the characters
    while(in_stream.get(next))
        {
            advice += next;
        }

    //show the input from file
    cout << advice << endl;

    in_stream.close();
}

void update_advice()
{
    using namespace std;

    cout << "Please enter your advice. Please indicate end of input by pressing <cr> twice:\n";

    //open the output file
    ofstream out_stream;
    char next, final;
    string output_advice;
    out_stream.open("hw4pr02input.txt");
    if(out_stream.fail())
        {
            cout << "Output file opening failed.\n";
            return;
        }

    //loop through the characters
    while(cin.get(next))
        {
            if(next == '\n')
                {
                    out_stream.put(next);
                    cin.get(final);
                    if(final == '\n')
                        {
                            cout << "Thank you for your advice.\n";
                            break;
                        }
                    else
                        {
                            out_stream.put(final);                     
                            continue;
                        }
                }
            
            out_stream.put(next);
        }
    
    out_stream.close();    
}

}
