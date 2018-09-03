// FILE: clocks.cxx (part of the namespace main_savitch_14)
// CLASSES IMPLEMENTED: clock, cuckoo_clock, clock24 (see clock.h)
// INVARIANT for the clock ADT:
//   1. The current hour is stored in my_hour, using 12-hour notation.
//   2. The current minute is stored in my_minute.
//   3. If the time is from midnight to 11:59 am (inclusive), then
//      my_morning is true; otherwise my_morning is false.

#include <cassert>
#include "clocks.h"

namespace main_savitch_14
{
    clock::clock( )
    {
        my_hour = 12;
        my_minute = 0;
        my_morning = true;
    }

    void clock::set_time(int hour, int minute, bool morning)
    // Library facilities used: cassert
    {
        assert(1 <= hour);
        assert(hour <= 12);
        assert(0 <= minute);
        assert(minute <= 59);

        my_hour = hour;
	my_minute = minute;
	my_morning = morning;
    }

    void clock::advance(int minutes)
    {
	const int MINUTES_IN_DAY = 24*60;
	const int MINUTES_IN_HOUR = 60;

	// Change the minutes so that 0 <= minutes < MINUTES_IN_DAY
	if (minutes < 0)
	    minutes += MINUTES_IN_DAY * (1 - minutes/MINUTES_IN_DAY);
	if (minutes >= MINUTES_IN_DAY)
	    minutes -= MINUTES_IN_DAY * (minutes/MINUTES_IN_DAY);
	
	// Advance the clock any full hours
	while (minutes > 60)
	{
	    minutes -= MINUTES_IN_HOUR;
	    my_hour++;
	    if (my_hour == 12)
		my_morning = !my_morning;
	    if (my_hour == 13)
		my_hour = 1;
	}
	
	// Advance any remaining minutes
	my_minute += minutes;
	if (my_minute >= MINUTES_IN_HOUR)
	{
	    my_minute -= MINUTES_IN_HOUR;
	    my_hour++;
	    if (my_hour == 12)
		my_morning = !my_morning;
	    if (my_hour == 13)
		my_hour = 1;
	}
    }

    int clock::get_hour( ) const
    {
	return my_hour;
    }
    
    int clock::get_minute( ) const
    {
	return my_minute;
    }

    bool clock::is_morning( ) const
    {
	return my_morning;
    }

    bool cuckoo_clock::is_cuckooing( ) const
    {
	return (get_minute( ) == 0);
    }

    bool operator <(const clock& c1, const clock& c2)
    {
	// Check whether one is morning and the other is not
	if (c1.is_morning( ) && !c2.is_morning( ))
	    return true;
	else if (c2.is_morning( ) && !c1.is_morning( ))
	    return false;
	
	// Check whether one is 12 o'clock and the other is not
	else if ((c1.get_hour( ) == 12) && (c2.get_hour( ) != 12))
	    return true;
	else if ((c2.get_hour( ) == 12) && (c1.get_hour( ) != 12))
	    return false;
	
	// Check whether the hours are different from each other
	else if (c1.get_hour( ) < c2.get_hour( ))
	    return true;
	else if (c2.get_hour( ) < c1.get_hour( ))
	    return false;

	// The hours are the same, so check the minutes
	else if (c1.get_minute( ) < c2.get_minute( ))
	    return true;
	else 
	    return false;
    }

    int clock24::get_hour( ) const
    {
	int ordinary_hour;
	
	ordinary_hour = clock::get_hour( );
	if (is_morning( ))
	{
	    if (ordinary_hour == 12)
		return 0;
	    else
		return ordinary_hour;
	}
	else
	{
	    if (ordinary_hour == 12)
		return 12;
	    else
		return ordinary_hour + 12;
	}
    }

}
