// File: lock.cxx
// Written by: Michael Main (main@colorado.edu) on Jan 13, 2004
//
// CLASS PROVIDED: lock (part of the namespace main_savitch_2)
// A lock object simulates a lock with a spin combination.
// The lock has lock::SIZE numbers which range from 0 to lock::SIZE-1.
// These numbers are printed on a spin dial.  If 0 is at the top of the
// dial, then the numbers 1, 2, 3... appear in order going clockwise
// around the dial.
//
// In order to open a lock, the user must:
//  A. Spin the dial at least one full turn clockwise, stopping when the
//     the the first combinatioin number is at the top of the dial.
//  B. Spin the dial counterclockwise one full turn and then keep going,
//     stopping the next time the second combination number reaches the top.
//  C. Spin the dial clockwise again, stopping the next time the third
//     combination number reaches the top of the dial
//  D. Pull on the lock, trying to open it.

// INVARIANT of the lock class:
// 1. The three combination numbers are combo1 (the first number),
//    combo2 (the second number) and combo3 (the final number).
// 2. The stopping numbers of the three most recent spins are
//    recent_number (the most recent spin), middle_number (the next
//    most recent spin) and oldest_number (the oldest of the three spins).
// 3. The lengths of these three most recent spins are measured by
//    counting how many numbers came to the top of the dial.
//    A spin that doesn't move at all would have the length zero.
//    A spin that moves from one number to the very next number
//    would have a length of one.  The lengths of the three most
//    recent spins are stored in recent_spinlen, middle_spinlen and
//    oldest_spinlen.
// 4. The member variable recent_is_clockwise is true if and only if
//    the most recent spin was in a clockwise direction.
// 5. The member variable open is true if and only if the lock is
//    currently open.

#include <cassert>
#include "lock.h"
using namespace std;

namespace main_savitch_2
{
    /////////////////////////////////////////////////////////////////////////
    // Static member constants
    const int lock::SIZE;
    const int lock::MAX_NUMBER;
    /////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR for the lock
    //  PRECONDITION: Each of the three parameters is from the range
    //  [0..MAX_NUMBER].
    //  POSTCONDITION: This lock has been initialized with the specified
    //  combination.  It's state is as if a person has just made four 
    //  spins: clockwise stopping at 0, counterclockwise stopping at 0,
    //  clockwise stopping at 0, and finally counterclockwise stopping at 0.
    //  This lock is closed. 
    lock::lock(int combo1, int combo2, int combo3)
    {
	open = false;
	recent_number = middle_number = oldest_number = 0;
	recent_spinlen = middle_spinlen = oldest_spinlen = SIZE;
	recent_is_clockwise = false;
	setcombo(combo1, combo2, combo3);
    }
    /////////////////////////////////////////////////////////////////////////

    
    /////////////////////////////////////////////////////////////////////////
    // void lock::setcombo(int combo1, int combo2, int combo3)
    //  PRECONDITION: Each of the three parameters is from the range
    //  [0..MAX_NUMBER].
    //  POSTCONDITION: This lock has had its combination changed to the
    //  specified combination.  Otherwise, it's state is unchanged.
    void lock::setcombo(int combo1, int combo2, int combo3)
    {
	assert(0 <= combo1 && combo1 <= MAX_NUMBER);    
	assert(0 <= combo2 && combo2 <= MAX_NUMBER);    
	assert(0 <= combo3 && combo3 <= MAX_NUMBER);    

	this->combo1 = combo1;    
	this->combo2 = combo2;    
	this->combo3 = combo3;
    }
    /////////////////////////////////////////////////////////////////////////

    
    /////////////////////////////////////////////////////////////////////////
    // void lock::turn(int number, bool is_clockwise, int turns)
    //  PRECONDITION: number is in the range [0..MAX_NUMBER], and turns >= 0;
    //  POSTCONDITION: The state of this lock has changed as if a person
    //  spun this lock t full spins and then kept going until the next
    //  time that number is at the top of the dial.  If isClockwise is true,
    //  then the direction of the spin is clockwise; otherwise, the direction
    //  is counterclockwise.
    void lock::turn(int number, bool is_clockwise, int turns)
    {
	assert(0 <= number && number <= MAX_NUMBER);
        assert(turns >= 0);

	if (is_clockwise != recent_is_clockwise)
	{   // This spin is in a new direction
	    oldest_spinlen = middle_spinlen;
	    middle_spinlen = recent_spinlen;
	    recent_spinlen
		= spinlen(recent_number, number, is_clockwise, turns);
	    oldest_number = middle_number;
	    middle_number = recent_number;
	    recent_number = number;
	    recent_is_clockwise = is_clockwise;
	}
	else
	{   // This spin and the most recent one are same direction
	    recent_spinlen
		+= spinlen(recent_number, number, is_clockwise, turns);
	    recent_number = number;
	}
    }
    /////////////////////////////////////////////////////////////////////////

    
    /////////////////////////////////////////////////////////////////////////
    // void lock::close( )
    //  POSTCONDITION: This lock is now closed.
    void lock::close( )
    {
	open = false;
    }
    /////////////////////////////////////////////////////////////////////////
    

    /////////////////////////////////////////////////////////////////////////
    // void lock::try_to_open( )
    //  POSTCONDITION: If this lock was already open, then it is still open.
    //  If it was closed and the correct sequence of actions to open the
    //  lock has occured, then it is now open.  Otherwise, it remains closed.
    void lock::try_to_open( )
    {
	if ((recent_is_clockwise)
	    &&
	    (oldest_spinlen >= SIZE)
	    &&
	    (middle_spinlen > SIZE)
	    &&
	    (middle_spinlen <= 2*SIZE)
	    &&
	    (recent_spinlen > 0)
	    &&
	    (recent_spinlen <= SIZE)
	    &&
	    (oldest_number == combo1)
	    &&
	    (middle_number == combo2)
	    &&
	    (recent_number == combo3)
	   )
	   open = true;
    }
    /////////////////////////////////////////////////////////////////////////
    

    /////////////////////////////////////////////////////////////////////////
    // bool lock::is_open( ) const
    //  POSTCONDITION: The return value is true if and only if this lock is
    //  currently open.
    bool lock::is_open( ) const
    {
	return open;
    }
    /////////////////////////////////////////////////////////////////////////
    

    /////////////////////////////////////////////////////////////////////////
    // int lock::top( ) const
    //  POSTCONDITION: The return value is the number that's currently on
    //  top of the dial.
    int lock::top( ) const
    {
	return recent_number;
    }
    /////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////
    // int lock::spinlen(int start, int stop, bool is_clockwise, int turns)
    // PRECONDITION: start and stop are both in the range [0..MAX_NUMBER],
    // and turns >= 0.
    // POSTCONDITION: The return value is the length of a spin in which
    // a person starts with the start number at the top of the dial, makes
    // t full turns, then continues until the stop number next appears
    // at the top of the dial. If is_clockwise is true, then the direction
    // of this turn is clockwise; otherwise it is counterclockwise.
    int lock::spinlen(int start, int stop, bool is_clockwise, int turns)
    {
	int answer = SIZE*turns;
	
	if (is_clockwise)
	{   // Adjust the answer for a clockwise spin
	    if (stop >= start)
		answer += (stop - start);
	    else
		answer += SIZE - (start - stop);
	}
        else
	{   // Adjust the answer for a counter-clockwise spin
	    if (stop <= start)
		answer += -(stop - start);
	    else
		answer += SIZE + (start - stop);
	}
	return answer;
    }
    /////////////////////////////////////////////////////////////////////////

}
