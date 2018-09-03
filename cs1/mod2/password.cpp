#include <iostream>
#include "Authenticate.h"
using namespace std;

namespace
{
    std::string password;
    
    bool isValid()
    {
       
        
        if(password.size() >= 8)
            {
                for(uint i = 0; i < password.size(); ++i)
                    {
                        if(!isalpha(password[i])) return true;
                    }
                return false;
            }
        else
            return false;
    }
}

namespace Authenticate
{
    void inputPassword()
    {
        do
            {
                cout << "Enter your password (at least 8 characters "
                     << "and at least one nonletter)" << endl;
                cin >> password;
            } while (!isValid());
    }
    string getPassword()
    {
        return password;
    }
}
