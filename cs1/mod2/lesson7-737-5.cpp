// Section CSC160 - Computer Science I: C++
// File Name: lesson7-737-5.cpp
// Student: Chris Scarola
// Homework Number: 7
// Description:
/*
  This Practice Program explores how the unnamed namespace works.
Listed below are snippets from a program to perform input validation for
a username and password. The code to input and validate the username is
in a file separate from the code to input and validate the password.

Define the username variable and the isValid() function in the
unnamed namespace so the code will compile. The isValid() function
should return true if username contains exactly eight letters. Generate an
appropriate header file for this code.
Repeat the same steps for the file password.cpp, placing the password
variable and the isValid() function in the unnamed namespace. In this
case, the isValid() function should return true if the input password
has at least eight characters including at least one nonletter.

At this point you should have two functions named isValid(), each in
different unnamed namespaces. Place the following main function in an
appropriate place. The program should compile and run.

Test the program with several invalid usernames and passwords.

 */
// Last Changed: 10/13/2016

#include "cs1/mod2/cs1mod2.h"
#include "Authenticate.h"

namespace lesson7_737_5 {

using namespace std;

void run()
{
    clear_screen();

    using namespace Authenticate;
    inputUserName();
    inputPassword();
    cout << "Your username is " << getUserName()
         << " and your password is: "
         << getPassword() << endl;    

    keep_window_open("~~");
}

}
