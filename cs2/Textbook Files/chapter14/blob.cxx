// FILE: blob.cxx
// This small demonstration shows how the organism class is used.
#include <cstdlib>           // Provides EXIT_SUCCESS
#include <iostream>          // Provides cout and cin
#include "organism.h"        // Provides the organism class

int main( )
{
    main_savitch_14::organism blob(20.0, 100000.0);
    int week;

    // Untroubled by conscience or intellect, the Blob grows for three weeks.
    for (week = 1; week <= 3; ++week)
    {
        blob.simulate_week( );
        cout << "Week " << week << ":" << " the Blob is ";
        cout << blob.get_size( ) << " ounces." << endl;
    }

    // Steve McQueen reverses the growth rate to -80000 ounces per week.
    blob.assign_rate(-80000.0);
    while (blob.is_alive( ))
    {
        blob.simulate_week( );
        cout << "Week " << week << ":" << " the Blob is ";
        cout << blob.get_size( ) << " ounces." << endl;
        ++week;
    }

    cout << "The Blob (or its son) shall return." << endl;
    return EXIT_SUCCESS;
}
