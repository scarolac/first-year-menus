// Section CSC161 - Computer Science II: C++
// File Name: Postfixer.cxx
// Student: Chris Scarola
// Homework Number: 6
// Last Changed: 03/5/2017

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "stack2.h"
using namespace std;
using namespace main_savitch_7B;

double post_fix_operation(string& s);
//opens a file to perform post fix operations

double perform_operation(char ch, double left, double right);
//performs the given operation for the postfix expression

void print_result(string& s, double& amount);
//prints the stack containing results

void keep_window_open(std::string s);
//holds the window open until the string "~~" is entered

int main()
{
    //open the file
    ifstream ifs;
    char file_name[] = "HomeworkSixInput.txt";
    ifs.open(file_name);
    if (ifs.fail())
	{
            cout << "Input file failed to open";
            keep_window_open("~~");
            return -1;
	}

    //read the file
    while (!ifs.eof())
	{
            string line;
            getline(ifs, line);		
            if (line.size() > 0)
		{
                    double result = post_fix_operation(line);
                    print_result(line, result);
		}
	}

    keep_window_open("~~");
    return 0;
}

double post_fix_operation(string& s)
{
    stack<double> values;	

    for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == ' ') continue;
            if (isdigit(s[i]))
                {
                    int digit = 0;
                    while (i < s.size() && isdigit(s[i]))
                        {
                            digit = (digit * 10) + (s[i] - '0'); //character math
                            ++i;
                        }
                    --i;                //go back when the right value is found otherwise it goes up twice
                    values.push(digit);
                }
            else
                {
                    if (s[i] != ' ')
                        {
                            double right = values.top(); values.pop();
                            double left = values.top(); values.pop();
                            values.push(perform_operation(s[i],left,right));
                        }
					
                }
        }
    
    return values.top();
}

double perform_operation(char ch, double left, double right)
{
    if (ch == '+') return (left + right);
    if (ch == '-') return (left - right);
    if (ch == '*') return (left * right);
    if (ch == '/') return (left / right);
    else cout << "Invalid operation\n";
    return -1;
}

void print_result(string& s, double& amount)
{
    cout << s << " = " << amount << endl;
}

void keep_window_open(std::string s)
{
    using namespace std;
    cout << endl;

    if (s=="") return;
    cin.clear();
    for (;;)
        {
            cout << "Please enter " << s << " to exit\n";
            string ss;
            while (cin >> ss && ss!=s)
                cout << "Please enter " << s << " to exit\n";
            return;
        }
}
