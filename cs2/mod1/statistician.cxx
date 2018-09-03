// Section CSC161 - Computer Science II: C++
// File Name: statistician.cxx
// Student: Chris Scarola
// Homework Number: 1
// Last Changed: 01/25/2017
// CLASS IMPLEMENTED: statistician

#include "statistician.h"

namespace main_savitch_2C
{
    void statistician::reset()
    //resets the statistician object to 0's
    //uses cfloat for the min and max for double
    //largest set to smallest possible value so any value larger becomes the next largest
    //smallest set to largest possible value so any value smaller becomes the next smallest
    {
        size = 0;
        previous = 0.0;
        total = 0.0;
        average = 0.0;
        smallest = DBL_MAX;
        largest = -DBL_MAX;
    }

    statistician::statistician()
    {
        reset();
    }

    statistician::statistician(int s, double p, double t, double a, double sm, double l)
        : size(s),previous(p),total(t),average(a),smallest(sm),largest(l)
    {}

    void statistician::next_number(double n)
    {
        previous = n;                  //n is now the last number entered;
        if(n < smallest) smallest = n; //if n is the new smallest, update smallest
        if(n > largest) largest = n;   //if n is the new largest, update largest
        total += n;                    //add n to the running sum
        ++size;                        //increment length by 1
        average = total / size;        //recalculate mean
    }

    statistician multiply(double d, const statistician& s1)
    //create a new statistician object with 
    //values that are equal to the double value times the statistician object values
    //private to only be used by operator*
    {
        int s = s1.size;
        double p = s1.previous * d;
        double t = s1.total * d;
        double a = t / s;
        double sm = s1.smallest * d;
        double l = s1.largest * d;

        if(sm > l) //for when signs flip
            {
                int i = sm; //store smallest
                sm = l;     //set smallest
                l = i;      //used stored smallest
            }

        statistician temp(s,p,t,a,sm,l);

        return temp;
    }

    //number first, object second
    statistician operator*(int d, const statistician& s1)
    {
        return multiply(d,s1);
    }

    statistician operator*(double d, const statistician& s1)
    {
        return multiply(d,s1);
    }

    //object first, number second
    statistician operator*(const statistician& s1, int d)
    {
        return multiply(d,s1);
    }

    statistician operator*(const statistician& s1, double d)
    {
        return multiply(d,s1);
    }

    statistician operator+(const statistician& s1, const statistician& s2)
    //add two statistician objects, combine lengths and sums, recalculate mean, keep second object last value
    //redetermine new smallest and largest values
    {
        int s = s1.size + s2.length();
        double p = s2.last();
        double t = s1.total + s2.sum();
        double a = t / s;
        double sm = (s1.smallest < s2.minimum()) ? s1.smallest : s2.minimum();
        double l = (s1.largest > s2.maximum()) ? s1.largest : s2.maximum();

        statistician temp(s,p,t,a,sm,l);

        return temp;        
    }

    bool operator==(const statistician& s1, const statistician& s2)
    {
        return (s1.size == s2.length() &&
                s1.total == s2.sum() &&
                s1.average == s2.mean() &&
                s1.smallest == s2.minimum() &&
                s1.largest == s2.maximum());
    }
}
