// FILE: organism.cxx
// CLASSES IMPLEMENTED:
//   organism, plant, animal, herbivore (see organism.h for documentation)
//
// INVARIANT for the organism class:
//   1. The member variable size contains the organism's size, in ounces.
//   2. The member variable rate contains the organism's growth rate, in
//      ounces per week.
//
// INVARIANT for the animal class:
//   1. The member variable need_each_week contains the organism's food
//      requirement, in ounces per week.
//   2. The member variable eaten_this_week contains the number of ounces of
//      food eaten by the organism in the current week.
//
// The plant and herbivore classes have no extra member variables, so there
// is no need for an invariant.

#include <cassert>    // Provides assert
#include "organism.h"

namespace main_savitch_14
{
    organism::organism(double init_size, double init_rate)
    {
	if (init_size == 0)
	    assert(init_rate == 0);
	else
	    assert(init_size >= 0);

	size = init_size;
	rate = init_rate;
    }
        
    void organism::alter_size(double amount)
    {
	size += amount;
	if (size <= 0)
	    death( );
    }

    void organism::death( )
    {
	size = rate = 0;
    }

    plant::plant(double init_size, double init_rate)
    : organism(init_size, init_rate)
    {
	// All work is done by the organism constructor
    }

    void plant::nibbled_on(double amount)
    // Library functions used: cassert
    {
	assert(amount >= 0);
	assert(amount <= get_size( ));
	alter_size(-amount);
    }

    animal::animal(double init_size, double init_rate, double init_need)
    : organism(init_size, init_rate)
    // Library facilities used: cassert
    {
	assert(0 <= init_need);
	need_each_week = init_need;
	eaten_this_week = 0;
    }

    void animal::assign_need(double new_need)
    // Library facilities used: cassert
    {
	assert(new_need >= 0);
	need_each_week = new_need;
    }

    void animal::eat(double amount)
    // Library facilities used: cassert
    {
	assert(amount >= 0);
	eaten_this_week += amount;
    }

    void animal::simulate_week( )
    {
	organism::simulate_week( );
	if (eaten_this_week < need_each_week)
	    death( );
	eaten_this_week = 0;
    }

    double animal::still_need( ) const
    {
	if (eaten_this_week >= need_each_week)
	    return 0;
	else
	    return need_each_week - eaten_this_week;
    }
    
    herbivore::herbivore(double init_size, double init_rate, double init_need)
    : animal(init_size, init_rate, init_need)
    {
	// All work is done by the animal constructor
    }

    void herbivore::nibble(plant& meal)
    {
	const double PORTION = 0.5;  // Eat no more than this portion of plant
	const double MAX_FRACTION = 0.1; // Eat no more than this fraction of weekly need
	double amount; // How many ounces of the plant will be eaten

	// Set amount to some portion of the plant, but no more than a given
	// maximum fraction of the total weekly need, and no more than what the
	// herbivore still needs to eat this week.
	amount = PORTION * meal.get_size( );
	if (amount > MAX_FRACTION * total_need( ))
	    amount = MAX_FRACTION * total_need( );
	if (amount > still_need( ))
	    amount = still_need( );
	
	// Eat the plant
	eat(amount);
	meal.nibbled_on(amount);
    }
   
}
