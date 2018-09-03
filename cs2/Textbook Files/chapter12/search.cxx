// FILE: search.cxx
// Demonstration program for the binary search function

#include <cstdlib>    // Provides EXIT_SUCCESS, size_t
#include <iostream>   // Provides cin, cout
using namespace std;

// PROTOTYPE for function used in demonstration program:
void search(
    const int a[ ],
    size_t first,
    size_t size,
    int target,
    bool& found,
    size_t& location
);


int main( )
{
    const size_t MANY = 10;
    int fibonacci[MANY] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    int target;
    bool found;
    size_t location;

    do
    {
        cout << "Please type an integer from 0 to 100: ";
        cin >> target;
    }
    while ((target < 0) || (target > 100));
    search(fibonacci, 0, MANY, target, found, location);

    if (found)
        cout << target << " is a Fibonacci number at ["
             << location << "] in my array." << endl;
    else
        cout << target << " is not a Fibonacci number." << endl;

    return EXIT_SUCCESS;
}
    
void search(
    const int a[ ],
    size_t first,
    size_t size,
    int target,
    bool& found,
    size_t& location
)
// Precondition: The array segment starting at a[first] and containing size
// elements is sorted from smallest to largest.
// Postcondition: The array segment starting at a[first] and containing size
// elements has been searched for the target. If the target was present, then
// found is true, and location is set so that target == a[location]; 
// Otherwise, found is set to false.
// Library facilities used: stdlib.h (provides size_t).
{
    size_t middle;

    if (size == 0)
        found = false;
    else
    {
        middle = first + size/2;
        if (target == a[middle])
        {
            location = middle;
            found = true;
        }
        else if (target < a[middle])
            // The target is less than a[middle], so search before the middle
            search(a, first, size/2, target, found, location);
        else 
            // The target must be greater than a[middle], so search after the middle
            search(a, middle+1, (size-1)/2, target, found, location);
    } 
}
