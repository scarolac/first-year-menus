//---------------------------------------------------------------------------
// CSC160 Exam Two - Date.cpp
//---------------------------------------------------------------------------

#include <iostream>
#include "Date.h"

using namespace std;
namespace ExamTwo
{
    Date::Date()
    {
        internalDate = 0.0;
    }
    Date::Date(int m, int d, int y)
    {
        internalDate = numDays(m, d, y);
    }
    Date::Date(int days)
    {
        internalDate = static_cast<double>(days);
    }
    void Date::setDate(int month, int day, int year) throw(DateException)
    {
        if (year > 0)
            if (month >= 1 && month <= 12)
                if (day >= 1)
                    {
                        switch (month)
                            {
                            case 2:
                                if (isLeapYear(year))
                                    if (day > 29)
                                        throw DateException("Invalid Day Value: " + day);
                                    else
                                        if (day > 28)
                                            throw DateException("Invalid Day Value: " + day);
                                break;
                            case 4:
                            case 6:
                            case 9:
                            case 11:
                                if (day > 30)
                                    throw DateException("Invalid Day Value: " + day);
                                break;
                            default:
                                if (day > 31)
                                    throw DateException("Invalid Day Value: " + day);
                            }
                    }
                else
                    throw DateException("Invalid Day Value: " + day);
            else
                throw DateException("Invalid Month Value: " + month);
        else
            throw DateException("Invalid Year Value: " + year);
        internalDate = numDays(month, day, year);
    }

    double Date::numDays(int month, int day, int year)
    {

        // Code for numDays not shown to save space:
        //you can assume that it works and does not throw any exceptions

        //return dayCount;
    }
    void Date::getDetails(const int& month, const int& day, const int& year) const
    {

        //  Code for getDetails not shown to save space:
        //you can assume that it works and does not throw any exceptions
    }


    bool Date::isLeapYear(int year)
    {

        // Code for isLeapYear not shown to save space:
        //you can assume that it works and does not throw any exceptions
    }

    Date operator +(const Date& first, const Date& second)
    {
        Date temp;
        temp.internalDate = first.internalDate + second.internalDate;
        return temp;
    }

    Date operator -(const Date& first, const Date& second)
    {
        Date temp;
        temp.internalDate = first.internalDate - second.internalDate;
        return temp;
    }

    istream& operator >>(istream& in, Date& thisDate)
    {
        int month, day, year;
        char temp;
        in >> month >> temp >> day >> temp >> year;
        thisDate.internalDate = thisDate.numDays(month, day, year);
        return in;
    }

    ostream& operator <<(ostream& out, const Date& thisDate)
    {
        int month, day, year;
        thisDate.getDetails(month, day, year);
        out << month << '/' << day << '/' << year;
        return out;
    }
}
