//---------------------------------------------------------------------------
// CSC160 Exam Two - DateException.cpp
//---------------------------------------------------------------------------
#include <string>
#include "DateException.h"
using namespace std;
namespace ExamTwo
{
    DateException::DateException()
    {
        message = "Error in Date Occurred: No Additional Information";
    }
    DateException::DateException(string thisErrorMessage)
    {
        message = "Date Exception" + thisErrorMessage;
    }
    string DateException::errorMessage()
    {
        return message;
    }
}
