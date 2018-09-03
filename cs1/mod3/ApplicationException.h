#ifndef APPLERROR_H
#define APPLERROR_H
#include <string>
using namespace std;

class ApplicationException
{
public:
    ApplicationException() { message = "";}
    ApplicationException(string thisErrorMessage) : message(thisErrorMessage) {}

    string errorMessage() { return message; }
    void setErrorMessage(string thisErrorMessage)
    { message = thisErrorMessage; }

protected:
    string message;
};

#endif
