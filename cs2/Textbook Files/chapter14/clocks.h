// FILE: clocks.h (part of namespace main_savitch_14)
// CLASSES PROVIDED: 
//   clock (keeps track of a single time value)
//   cuckoo_clock (clock descendant with a cuckoo that makes noise on the hour)
//   clock24 (clock descendant for time in 24-hour version)
//
// CONSTRUCTOR for the clock class:
//   clock( )
//     Postcondition: The clock is set to 12:00 (midnight).
//
// MODIFICATION MEMBER FUNCTIONS for the clock class:
//   void set_time(int hour, int minute, bool morning)
//     Precondition: 1 <= hour <= 12, and 0 <= minute <= 59.
//     Postcondition: The clock's time has been set to the given hour and
//     minute (using usual 12-hour time notation). If the third parameter,
//     morning, is true, then this time is from 12:00 midnight to 11:59am.
//     Otherwise this time is from 12:00 noon to 11:59pm.
//
//   void advance(int minutes)
//     Postcondition: The clock has been moved forward by the indicated
//     number of minutes.
//     Note: A negative argument moves the clock backward.
//
// CONSTANT MEMBER FUNCTIONS for the clock class:
//   int get_hour( ) const
//     Postcondition: The value returned is the current hour using a 12-hour
//     clock.
//
//   int get_minute( ) const
//     Postcondition: The value returned is the current minute on the clock.
//
//   bool is_morning( ) const
//     Postcondition: If the clock's time lies from 12:00 midnight to
//     11:59am (inclusive), the function returns true; otherwise it
//     returns false. 
//
// NONMEMBER FUNCTIONS for the clock class:
//   bool operator <(const clock& c1, const clock& c2)
//     Postcondition: Returns true if the time on c1 is earlier than the time
//     on c2 over a usual day (starting at midnight); otherwise returns false.
//
// INHERITED MEMBER FUNCTIONS for the cuckoo_clock class:
//   The cuckoo_clock inherits all public members from the clock class.
//
// ADDITIONAL CONSTANT MEMBER FUNCTION for the cuckoo_clock class:
//   bool is_cuckooing( ) const;
//   Postcondition: The return value is true if the current minute is zero
//   (so that the cuckoo is making noise).
//
// INHERITED MEMBER FUNCTIONS for the clock24 class:
//   The clock24 class inherits all public members from the clock class,
//   except for get_hour, which is overriden (as described below):
//
// OVERRIDEN CONSTANT MEMBER FUNCTION for the clock24 class:
//   int get_hour( ) const
//     Postcondition: The value returned is the current hour using a 24-hour
//     clock.
//
// VALUE SEMANTICS for the clock, cuckoo_clock, and clock24 classes: 
//    Assignments and the copy constructor may be used with any of
//    these objects.

#ifndef CLOCK_H
#define CLOCK_H

namespace main_savitch_14
{
    class clock
    {
    public:
        // CONSTRUCTOR
        clock( );
        // MODIFICATION FUNCTIONS
        void set_time(int hour, int minute, bool morning);
        void advance(int minutes); 
        // CONSTANT FUNCTIONS
        int get_hour( ) const;
        int get_minute( ) const; 
        bool is_morning( ) const;
    private:
        int my_hour;
        int my_minute;
        int my_morning;
    };

    class cuckoo_clock : public clock
    {
    public:
        bool is_cuckooing( ) const;
    };

    class clock24 : public clock
    {
    public:
        int get_hour( ) const;
    };

    // NONMEMBER FUNCTION for the clock class:
    bool operator <(const clock& c1, const clock& c2);
}

#endif
