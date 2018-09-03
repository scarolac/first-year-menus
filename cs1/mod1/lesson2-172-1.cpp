// Section CSC160 - Computer Science I: C++
// File Name: lesson2-172-1.cpp
// Student: Chris Scarola
// Homework Number: 2
// Description: 
/*
  Write a program to score the paper-rock-scissor game. Each of two users
types in either P, R, or S. The program then announces the winner as well
as the basis for determining the winner: Paper covers rock, Rock breaks
scissors, Scissors cut paper, or Nobody wins. Be sure to allow the users
to use lowercase as well as uppercase letters. Your program should include
a loop that lets the user play again until the user says she or he is done.
 */
// Last Changed: 8/29/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson2_172_1 {

using namespace std;

void run()
{
    char player_one, player_two;

    do
    {

        clear_screen();

        cout << "Rock, paper scissors\n\n";


        //get player one data
        cout << "Player one input R, P, or S: ";
        while(cin >> player_one)
        {
            if(player_one == 'R' || player_one == 'r'
                    || player_one == 'P' || player_one == 'p'
                    || player_one == 'S' || player_one == 's')
            {
                break;
            }
            else
            {
                cin.clear();
                cout << "Player one please input R, P, or S: ";
            }
        }

        //get player two data
        cout << "Player two input R, P, or S: ";
        while(cin >> player_two)
        {
            if(player_two == 'R' || player_two == 'r'
                    || player_two == 'P' || player_two == 'p'
                    || player_two == 'S' || player_two == 's')
            {
                break;
            }
            else
            {
                cin.clear();
                cout << "Player two please input R, P, or S: ";
            }
        }

        //separator
        cout << endl;

        //check the data for a winner
        if(tolower(player_one) == tolower(player_two)) cout << "Nobody wins\n";
        else if(tolower(player_one) == 'r')
        {
            if(tolower(player_two) == 'p') cout << "Paper covers rock, Player two wins.\n";
            if(tolower(player_two) == 's') cout << "Rock breaks scissors, Player one wins.\n";
        }
        else if(tolower(player_one) == 'p')
        {
            if(tolower(player_two) == 's') cout << "Scissors cuts paper, Player two wins.\n";
            if(tolower(player_two) == 'r') cout << "Rock covers paper, Player one wins.\n";
        }
        else if(tolower(player_one) == 's')
        {
            if(tolower(player_two) == 'r') cout << "Rock breaks scissors, Player two wins.\n";
            if(tolower(player_two) == 'p') cout << "Scissors cuts paper, Player one wins.\n";
        }

    }
    while(prompt());
}

}
