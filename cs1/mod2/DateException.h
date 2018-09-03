//---------------------------------------------------------------------------
// CSC160 Exam Two - DateException.h
//---------------------------------------------------------------------------
#ifndef DATEEXCEPTION_H
#define DATEEXCEPTION_H
#include <string>
using namespace std;
namespace ExamTwo
{
    class DateException
    {
    public:
        DateException();
        DateException(string thisErrorMessage);
        string errorMessage();
    private:
        string message;
    };
}
#endif
