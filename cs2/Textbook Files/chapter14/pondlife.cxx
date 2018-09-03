// FILE: pondlife.cxx
// A simple simulation program to model the fish and weeds in a pond

#include <iostream>    // Provides cin, cout
#include <iomanip>     // Provides setw
#include <cstdlib>     // Provides EXIT_SUCCESS, rand, size_t
#include <vector>      // Provides the vector template class
#include "organism.h"  // Provides Herbivore, Plant classes
using namespace std;
using namespace main_savitch_14;

// PROGRAM CONSTANTS
const size_t MANY_WEEDS      = 2000; // Number of weeds in the pond
const double WEED_SIZE       =   15; // Initial size of each weed, in ounces
const double WEED_RATE       =  2.5; // Growth rate of weeds, in ounces/week
const size_t INIT_FISH       =  300; // Initial number of fish in the pond
const double FISH_SIZE       =   50; // Fish size, in ounces
const double FRACTION        =  0.5; // A fish must eat FRACTION times its size
                                     // during one week or it will die.
const int    AVERAGE_NIBBLES =   30; // Average number of plants nibbled by
                                     // a fish over one week.
const double BIRTH_RATE      = 0.05; // At the end of each week, some fish have
                                     // babies. The total number of new fish
                                     // born is the current number of fish times
                                     // the BIRTH_RATE (rounded down to an
                                     // integer).

// Samples weed and fish objects to copy into the vectors of the main program:
const plant SAMPLE_WEED(WEED_SIZE, WEED_RATE);
const herbivore SAMPLE_FISH(FISH_SIZE, 0, FISH_SIZE * FRACTION);

// PROTOTYPES for the functions used in the program:
void pond_week(vector<herbivore>& fish, vector<plant>& weeds);
// Precondition: weeds.size( ) > 0.
// Postcondition: On average, each fish has nibbled on AVERAGE_NIBBLES plants,
// and then simulate_week has been activated for each fish and each weed. Any
// fish that died are removed from the fish bag, and then
// BIRTH_RATE * fish.size( ) new fish have been added to the fish bag.

double total_mass(const vector<plant>& collection);
// Postcondition: The return value is the total mass of all the plants in the
// collection.

    
int main( )
{
    vector<plant> weeds(MANY_WEEDS, SAMPLE_WEED);    // A vector of weeds
    vector<herbivore> fish(INIT_FISH, SAMPLE_FISH);  // A vector of weeds
    int many_weeks;   // Number of weeks to simulate
    int i;            // Loop control variable

    // Get number of weeks, and format the output.
    cout << "How many weeks shall I simulate? ";
    cin >> many_weeks;
    cout.setf(ios::fixed);
    cout << "Week    Number    Plant Mass" << endl;
    cout << "       of Fish   (in ounces)" << endl;

    // Simulate the weeks.
    for (i = 1; i <= many_weeks; i++)
    {
        pond_week(fish, weeds);
        cout << setw(4) << i;
        cout << setw(10) << fish.size( );
        cout << setw(14) << setprecision(0) << total_mass(weeds);
        cout << endl;
    }

    return EXIT_SUCCESS;
}

double total_mass(const vector<plant>& collection)
{
    double answer;
    vector<plant>::const_iterator p;
    answer = 0;
    for (p = collection.begin( ); p != collection.end( ); ++p)
        answer += p->get_size( );

    return answer;
}

void pond_week(vector<herbivore>& fish, vector<plant>& weeds)
{
    // Variables for an index and an iterator for the weeds:
    vector<plant>::iterator      wi;
    vector<plant>::size_type     weed_index;

    // Variables for an index, an iterator, and counters for the fish:
    vector<herbivore>::iterator  fi;
    vector<herbivore>::size_type fish_index;
    vector<herbivore>::size_type new_fish_population;

    size_t many_iterations;  // How many random nibbles to simulate
    size_t i;                // Loop counter

    // Have randomly selected fish nibble on randomly selected plants.
    many_iterations = AVERAGE_NIBBLES * fish.size( );
    for (i = 0; i < many_iterations; ++i)
    {
        fish_index = rand( ) % fish.size( );  // Index of a random fish
        weed_index = rand( ) % weeds.size( ); // Index of a random weed
        fish[fish_index].nibble(weeds[weed_index]);
    }

    // Simulate the weeks for the weeds.
    for (wi = weeds.begin( ); wi != weeds.end( ); ++wi)
        wi->simulate_week( );

    // Simulate the weeks for the fish, and count how many died.
    fi = fish.begin( );
    while (fi != fish.end( ))
    {
        fi->simulate_week( );
        if (!fi->is_alive( ))
            fish.erase(fi);
	else
	    ++fi;
    }

    // Calculate the new number of fish, and reset the fish vector to this size. 
    // If this adds new fish to the vector, then those new fish will be equal to
    // the SAMPLE_FISH that is used for all our fish:
    new_fish_population = (1 + BIRTH_RATE) * fish.size( );
    fish.resize(new_fish_population, SAMPLE_FISH);
}
