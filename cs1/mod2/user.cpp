#include <iostream>
#include "Authenticate.h"
using namespace std;

namespace
{
    std::string username;
    
    bool isValid()
    {
        if(username.size() == 8)
            {
                for(uint i = 0; i < username.size(); ++i)
                    {
                        if(!isalpha(username[i])) return false;
                    }
                return true;
            }
        else
            return false;
    }
}

namespace Authenticate
{
    
    void inputUserName()
    {        
        do
            {
                cout << "Enter your username (8 letters only)" << endl;
                cin >> username;
            } while (!isValid());
    }
    string getUserName()
    {
        return username;
    }
}
