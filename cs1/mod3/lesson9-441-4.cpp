// Section CSC160 - Computer Science I: C++
// File Name: lesson9-441-4.cpp
// Student: Chris Scarola
// Homework Number: 9, ch7 proj 4
// Description:
/*
  The standard deviation of a list of numbers is a measure of how much the
numbers deviate from the average. If the standard deviation is small, the
numbers are clustered close to the average. If the standard deviation is large,
the numbers are scattered far from the average. The standard deviation, S, of
a list of N numbers x is defined as follows:
S = root(sum(x-mean)^2/N)
where x is the average of the N numbers x1, x2, . . . . Define a function
that takes a partially filled array of numbers as its arguments and returns
the standard deviation of the numbers in the partially filled array. Since
a partially filled array requires two arguments, the function will actually
have two formal parameters: an array parameter and a formal parameter
of type int that gives the number of array positions used. The numbers
in the array will be of type double. Embed your function in a suitable test
program.
 */
// Last Changed: 10/31/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson9_441_4 {

//define constant size for array
const int size = 10;

void input_array(double a[], int& count);
//receive data for array and update the count

double calc_mean(double a[], int count);
//calculates average of count number of values in array

double std_deviation(double a[], int count);
//calculates standard deviation of count number of values in an array

void output_array(double a[], int count);
//output the information needed for array

void run()
{    
    do
    {
        clear_screen();

        std::cout << "Average and standard deviation will be calculated\n";
        //declare the array and reset count each iteration
        double scores[size];
        int count = 0;

        input_array(scores,count);

        output_array(scores,count);
    }
    while(prompt());
    

    keep_window_open("~~");
}

void input_array(double a[], int& count)
{
    std::cout << "\nEnter up to 10 values, separated by white space"
              << "\nTerminate input with '-1': ";

    //get data from input
    for(int i = 0; i < size; ++i)
    {
        std::cin >> a[i];
        if(a[i] == -1) break;

        count = i + 1;
    }
}

double calc_mean(double a[], int count)
{
    double total = 0.0;
    for(int i = 0; i < count; ++i)
    {
        if (a[i] == -1) break;

        total += a[i];
    }
    return (total / count);
}

double std_deviation(double a[], int count)
{
    double sum = 0.0;
    double mean = calc_mean(a,count);
    for(int i = 0; i < count; ++i)
    {
        sum += ((a[i] - mean) * (a[i] - mean));
    }

    return (std::sqrt((sum/count)));
}

void output_array(double a[], int count)
{
    std::cout << "\nAverage is: " << calc_mean(a,count)
              << "\nStandard Deviation is: " << std_deviation(a,count);
}

}
