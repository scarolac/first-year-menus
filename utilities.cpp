#include "utilities.h"

void clear_screen()
{
    system("clear||cmd /c cls");
    return;
}

void pause()
{
    system("echo Press enter to continue . . . && (read x 2> nul; rm nul || pause > nul)");
    return;
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

    return false;
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
