#ifndef USER_H
#define USER_H

namespace
{
    std::string username;

    bool isValid();
    //checks if username is valid (contains exactly 8 letters)
}

namespace Authenticate
{
    void inputUserName();
    //waits for username input

    std::string getUserName();
    //returns username
}

#endif
