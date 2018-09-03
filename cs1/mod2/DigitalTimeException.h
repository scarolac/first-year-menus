// Section CSC160 - Computer Science I: C++
// File Name: DigitalTimeException.h
// Student: Chris Scarola
// Homework Number: 8
// Description: Homework 8 create exception class for digital time class
// Last Changed: 10/20/2016

#ifndef DIGITALTIMEEXCEPTION_H
#define DIGITALTIMEEXCEPTION_H
#include <string>
using namespace std;

class DigitalTimeException
{
public:
    DigitalTimeException(int errorNum, string thisErrorMessage);
    string errorMessage();
    int errorNumber();
private:
    string message;
    int error;
};
#endif
