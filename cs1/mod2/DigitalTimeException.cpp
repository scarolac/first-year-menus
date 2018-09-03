// Section CSC160 - Computer Science I: C++
// File Name: DigitalTimeException.cpp
// Student: Chris Scarola
// Homework Number: 8
// Description: Homework 8 create exception class for digital time class
// Last Changed: 10/20/2016

#include "DigitalTimeException.h"

DigitalTimeException::DigitalTimeException(int errorNum, string thisErrorMessage)
{
    message = thisErrorMessage;
    error = errorNum;
}

string DigitalTimeException::errorMessage()
{
    return message;
}

int DigitalTimeException::errorNumber()
{
    return error;
}
