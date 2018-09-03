#include "DigitalTime.h"
#include "DigitalTimeException.h"
#include <iostream>

bool prompt();
//prompts the user to continue

void keep_window_open(std::string s);
//holds the window open until the string "~~" is entered

int main()
{
    do
        {
            try
                {
                    DigitalTime t1,t2(15,30),t3,t4(9,48),t5(3,21);
                    cout << "Input time for t1 in time notation (eg 14:45): ";
                    cin >> t1;

                    cout << "Input time for t3: ";
                    cin >> t3;
                    
                    cout << "t1 = " << t1 << endl;
                    cout << "t2 = " << t2 << endl;
                    cout << "t3 = " << t3 << endl;
                    cout << "t4 = " << t4 << endl;
                    cout << "t5 = " << t5 << endl;
                }
           
            catch(DigitalTimeException e)
                {
                    cout << "Error: " << e.errorNumber() << " - " << e.errorMessage() << endl; 
                }
        }
    while(prompt());
    

    keep_window_open("~~");
    return 0;
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
