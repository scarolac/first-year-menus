// Section CSC161 - Computer Science II: C++
// File Name: lesson08-473-14.cxx
// Student: Chris Scarola
// Homework Number: 8
// Last Changed: 03/25/2017

#include <iostream>

using namespace std;

int string_to_int(string s);
//converts a string to an int recursively

bool prompt();
//prompts the user to continue

void keep_window_open(std::string s);
//holds the window open until the string "~~" is entered

int main()
{
    do
        {
            cout << "Enter string to convert to numbers recusively: ";
            
            string input;
            cin >> input;

            cout << "Value of \"" << input << "\" is " << string_to_int(input) << endl; 
            
        }
    while(prompt());
    

    keep_window_open("~~");
    return 0;
}

int string_to_int(string s)
{
    int number = 0;
    string last_char = s.substr(s.size() - 1);           //get last char
    string remove_last_char = s.substr(0, s.size() - 1); //string without last char
    
    if(s.size() == 0) return 0;    //handle empty string

    //handle negative, call function again, making it negative, and skip the first char
    if(s[0] == '-') return -string_to_int(s.substr(1, s.size() - 1)); 

    if(s.size() == 1) //base case for recursion
        {
            if(isdigit(s[0]))
                {
                    number = s[0] - '0';  //convert to number
                }
            else
                {
                    cout << s[0] << " not a number" << endl;
                    return 0;
                }
        }
    else
        {
            //if 2+ characters: multiply first by 10 for tens place, then add the ones place
            //if 3+: function is just called again until each individual value is found
            number = string_to_int(remove_last_char) * 10 + string_to_int(last_char);
        }
     
    return number;
}

bool prompt()
{
    using namespace std;
    char response;
    cout << "\nRun it again (y/n)? ";
    
    while(cin >> response)
        {
            if(response == 'y' || response == 'Y') return true;                        
            else if (response == 'N' || response == 'n') return false;                        
            else
                {
                    cin.clear();
                    cout << "Run it again? please input Y or N: ";
                }
        }
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
