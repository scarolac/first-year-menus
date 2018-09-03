#ifndef PASSWORD_H
#define PASSWORD_H

namespace
{
    std::string password;

    bool isValid();
    //checks valid password (at least 8 characters and at least 1 non letter)
}

namespace Authenticate
{
    void inputPassword();
    //waits for username input

    std::string getPassword();
    //returns username
}

#endif
