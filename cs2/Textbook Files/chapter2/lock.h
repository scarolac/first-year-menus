// FILE: lock.h
// Written by: Michael Main (main@colorado.edu) on Aug 13, 2004
// CLASS PROVIDED: lock (part of the namespace main_savitch_2)
// A lock object simulates a lock with a spin combination.
// The lock has lock::SIZE numbers which range from 0 to lock::SIZE-1.
// These numbers are printed on a spin dial.  If 0 is at the top of the
// dial, then the numbers 1, 2, 3... appear in order going clockwise
// around the dial.
//
// STATIC MEMBER CONSTANTS for the lock class:
//   static const int SIZE = 40;
//     SIZE is the number of numbers on the dial, starting at 0.
//   static const int MAX_NUMBER = SIZE-1;
//     MAX_NUMBER is the highest number on the dial.
//
// CONSTRUCTOR for the lock class:
//   lock(int combo1, int combo2, int combo3);
//   PRECONDITION: Each of the three parameters is from the range
//   [0..MAX_NUMBER].
//   POSTCONDITION: This lock has been initialized with the specified
//   combination.  It's state is as if a person has just made four complete
//   spins: clockwise stopping at 0, counterclockwise stopping at 0,
//   clockwise stopping at 0, and finally counterclockwise stopping at 0.
//   This lock is closed.  In order to open this lock, the user must:
//   A. Spin the dial at least one full turn clockwise, stopping when the
//      the combo1 is at the top of the dial.
//   B. Spin the dial counterclockwise one full turn and then keep going,
//      stopping the next time combo2 reaches the top.
//   C. Spin the dial clockwise again, stopping the next time combo3
//      reaches the top of the dial
//   D. Pull on this lock, trying to open it.
//
// MODIFICATION MEMBER FUNCTIONS for the lock class:
//   void setcombo(int combo1, int combo2, int combo3);
//   PRECONDITION: Each of the three parameters is from the range
//   [0..MAX_NUMBER].
//   POSTCONDITION: This lock has had its combination changed to the specified
//   combination.  Otherwise, it's state is unchanged.
//
//   void turn(int number, bool is_clockwise, int t);
//   PRECONDITION: number is in the range [0..MAX_NUMBER], and turns >= 0;
//   POSTCONDITION: The state of this lock has changed as if a person
//   spun this lock t full spins and then kept going until the next
//   time that number is at the top of the dial.  If is_clockwise is true,
//   then the direction of the spin is clockwise; otherwise, the direction
//   is counterclockwise.
//
//    void close( );
//    POSTCONDITION: This lock is now closed.
//
//    void try_to_open( );
//    POSTCONDITION: If this lock was already open, then it is still open.
//    If it was closed and the correct sequence of actions to open the
//    lock has occured, then it is now open.  Otherwise, it remains closed.
//
// CONST MEMBER FUNCTIONS for the lock class:
//    bool is_open( ) const;
//    POSTCONDITION: The return value is true if and only if this lock is
//    currently open.
//
//    int top( ) const;
//    POSTCONDITION: The return value is the number that's currently on
//    top of the dial.

#ifndef LOCK_H
#define LOCK_H

namespace main_savitch_2
{
    class lock
    {
    public:
	// STATIC MEMBER CONSTANT
	static const int SIZE = 40;
	static const int MAX_NUMBER = SIZE-1;
	// CONSTRUCTOR
	lock(int combo1, int combo2, int combo3);
	// MODIFICATION MEMBER FUNCTIONS
	void setcombo(int combo1, int combo2, int combo3);
	void turn(int number, bool is_clockwise, int turns);
	void close( );
	void try_to_open( );
	// CONST MEMBER FUNCTIONS
	bool is_open( ) const;
	int top( ) const;
    private:
	// PRIVATE MEMBER VARIABLES
	int combo1, combo2, combo3;
	int recent_number, middle_number, oldest_number;
	bool recent_is_clockwise;
	int recent_spinlen, middle_spinlen, oldest_spinlen;
	bool open;
	// PRIVATE HELPER FUNCTIONS
	int spinlen(int start, int stop, bool is_clockwise, int turns);
    };
}
#endif
	
