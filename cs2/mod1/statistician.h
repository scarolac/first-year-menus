// Section CSC161 - Computer Science II: C++
// File Name: statistician.h
// Student: Chris Scarola
// Homework Number: 1
// Last Changed: 01/25/2017
/* CLASS PROVIDED: statistician

   CONSTRUCTOR:
     statistician()
       Postcondition: creates statistician object to be used

   MODIFICATION MEMBER FUNCTIONS:
     void next_number(double n)
       Postcondition: statistician increments the length, stores the double as the last number,
        adds to the sum, recalculates mean, checks if smallest and largest need to update and if needed updates
        
     void reset()
       Postcondition: statistician resets all values to start over

   CONSTANT MEMBER FUNCTIONS:
     int length() const
       Postcondition: value returned is the length or number of values put into statistician
       
     double get_last_number() const
       Postcondition: value returned is last number put into statistician
       
     double sum() const
       Postcondition: value returned is the sum of all values put into statistician
       
     double mean() const
       Postcondition: value returned is the arithmetic mean of all values input
       
     double minimum() const
       Postcondition: value returned is the smallest value put into statistician
       
     double maximum() const
       Postcondition: value returned is the largest value put into statistician

   FRIEND FUNCTIONS:
     statistician operator+ (const statistician& s1, const statistician& s2)
       Postcondition: adds length and sum of two statistician objects, recalculates mean,
        compares smallest and largest from both objects and updates,
        keeps second objects last value
       
     statistician operator*(const statistician& s, double d)
       Postcondition: statistican returned is multiplied by double given
       
     bool operator==(const statistician& s1, const statistician& s2)
       Postcondition: value returned is true if s1 and s2 are equal

   VALUE SEMANTICS:
     Assignments and the copy constructor may be used with the class provided.

 */


#ifndef STATISTICIAN_H
#define STATISTICIAN_H
#include "cs1/mod3/cs1mod3.h"

namespace main_savitch_2C
{
    class statistician
    {
    private:
        int size;
        double previous;
        double total;
        double average;
        double smallest;
        double largest;

        friend statistician multiply(double d, const statistician& s1);
        
    public:
        //CONSTRUCTORS
        statistician();
        statistician(int s, double p, double t, double a, double sm, double l);

        //MODIFICATION MEMBER FUNCTIONS
        void next_number(double n);
        void reset();

        //CONSTANT MEMBER FUNCTIONS
        int length() const { return size; }
        double last() const { return previous; }
        double sum() const { return total; }
        double mean() const { return average; }
        double minimum() const { return smallest; }
        double maximum() const { return largest; }

        //FRIEND FUNCTIONS
        friend statistician operator+(const statistician& s1, const statistician& s2);
        friend statistician operator*(int d, const statistician& s1);
        friend statistician operator*(double d, const statistician& s1);
        friend statistician operator*(const statistician& s1, int d);
        friend statistician operator*(const statistician& s1, double d);
        friend bool operator==(const statistician& s1, const statistician& s2);

    };    
}
#endif
