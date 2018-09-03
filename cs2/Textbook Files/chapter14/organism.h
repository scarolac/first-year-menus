// FILE: organism.h (part of the namespace main_savitch_14)
// CLASSES PROVIDED: organism, plant, animal, herbivore
//
//
// DOCUMENTATION for the organism class:
//   The organism class can simulate any growing organism, such as a plant or
//   animal.
//
// CONSTRUCTOR for the organism class:
//   organism(double init_size = 1, double init_rate = 0)
//     Precondition: init_size >= 0. Also, if init_size = 0, then init_rate is
//     also zero.
//     Postcondition: The organism being simulated has been initialized. The
//     value returned from get_size( ) is now init_size (measured in ounces),
//     and the value returned from get_rate( ) is now init_rate (measured in
//     ounces per week).
//
// MODIFICATION MEMBER FUNCTIONS for the organism class:
//   void simulate_week( )
//     Postcondition: The size of the organism has been changed by its current
//     growth rate. If the new size is less than zero, then the actual size is
//     set to zero rather than to a negative value, and the growth rate is also
//     set to zero.
//
//   void assign_rate(double new_rate)
//     Postcondition: The organism's growth rate has been changed to new_rate
//     (measured in ounces per week).
//
//   void alter_size(double amount)
//     Postcondition: The given amount (in ounces) has been added to the
//     organism's current size. If this results in a new size less than zero,
//     then the actual size is set to zero rather than to a negative value, and
//     the growth rate is also set to zero.
//
//   void death( )
//      Postcondition: The organism's current size and growth rate have been
//      set to zero.
//
// CONSTANT MEMBER FUNCTIONS for the organism class:
//   double get_size( ) const
//     Postcondition: The value returned is the organism's current size
//     (in ounces).
//
//   double get_rate( ) const
//     Postcondition: The value returned is the organism's current growth rate
//     (in oz/week).
//
//   bool is_alive( ) const
//     Postcondition: If the current size is greater than zero, then the return
//     value is true; otherwise the return value is false.
//
//
// DOCUMENTATION for the plant class:
//   plant is a derived class of the organism class. All the organism public
//   member functions are inherited by a plant. In addition, a plant has
//   these extra member functions:
//
// CONSTRUCTOR for the plant class:
//   plant(double init_size=0, double init_rate=0)
//     Same as the organism constructor.
//
// MODIFICATION MEMBER FUNCTIONS for the plant class:
//   void nibbled_on(double amount)
//     Precondition: 0 <= amount <= get_size( ).
//     Postcondition: The size of the plant has been reduced by amount.
//     If this reduces the size to zero, then death is activated.
//
//
// DOCUMENTATION for the animal class:
//   animal is a derived class of the organism class. All the organism public
//   member functions are inherited by an animal. In addition, an animal has
//   these extra member functions:
//
// CONSTRUCTOR for the animal class:
//   animal(double init_size=0, double init_rate=0, double init_need=0)
//     Precondition: init_size >= 0, and init_need >= 0. Also, if
//     init_size = 0, then init_rate is also zero.
//     Postcondition: The organism being simulated has been initialized. The
//     value returned from get_size( ) is now init_size (measured in ounces),
//     the value returned from get_rate( ) is now init_rate (measured in ounces
//     per week), and the animal must eat at least init_need ounces of food
//     each week to survive.
//
// MODIFICATION MEMBER FUNCTIONS for the animal class:
//   void assign_need(double new_need)
//     Precondition: new_need >= 0.
//     Postcondition: The animal's weekly food requirement has been changed to
//     new_need (measured in ounces per week).
//
//   void eat(double amount)
//     Precondition: amount >= 0.
//     Postcondition: The given amount (in ounces) has been added to the amount
//     of food that the animal has eaten this week.
//
//   void simulate_week( ) -- overriden from the organism class
//     Postcondition: The size of the organism has been changed by its current
//     growth rate. If the new size is less than zero, then the actual size is
//     set to zero rather than to a negative value, and the growth rate is also
//     set to zero. Also, if the animal has eaten less than its required need
//     over the past week, then death has been activated.
//
// CONSTANT MEMBER FUNCTIONS for the animal class:
//   double still_need( ) const
//     Postcondition: The return value is the ounces of food that the animal
//     still needs to survive the current week (i.e., its total weekly need
//     minus the amount that it has already eaten this week.)
//
//   double total_need( ) const
//     Postcondition: The return value is the total amount of food that the
//     animal needs to survive one week (measured in ounces).
//   
//
// DOCUMENTATION for the herbivore class:
//   plant is a derived class of the animal class. All the animal public
//   member functions are inherited by a herbivore. In addition, a herbivore has
//   this extra member function:
//
// CONSTRUCTOR for the herbivore class:
//   herbivore(double init_size=0, double init_rate=0, double init_need=0)
//     Same as the animal constructor.
//
// MODIFICATION MEMBER FUNCTIONS for the herbivore class:
//   void nibble(plant& meal)
//   Postcondition: eat(amount) and meal.nibbled_on(amount) have both been
//   activated. The amount is usually half of the plant, but it will never be
//   more than 10% of the herbivore's weekly need, nor more than the amount that
//   the animal still needs to eat to survive this week.
//
//
// VALUE SEMANTICS for the organism class and its derived classes:
//    Assignments and the copy constructor may be used with all objects.

#ifndef ORGANISM_H // Prevent duplicate definition
#define ORGANISM_H

namespace main_savitch_14
{
    class organism
    {
    public:
        // CONSTRUCTOR
        organism(double init_size = 1, double init_rate = 0);
        // MODIFICATION FUNCTIONS
        void simulate_week( ) { alter_size(rate); }
        void assign_rate(double new_rate) { rate = new_rate; }
        void alter_size(double amount);
        void death( );
        // CONSTANT FUNCTIONS
        double get_size( ) const { return size; } 
        double get_rate( ) const { return rate; }
        bool is_alive( ) const { return (size > 0); }
    private:
        double size;
        double rate;
    };

    class plant : public organism
    {
    public:
        // CONSTRUCTOR
        plant(double init_size = 1, double init_rate = 0);
        // MODIFICATION FUNCTIONS
        void nibbled_on(double amount);
    };
    
    class animal : public organism
    {
    public:
        // CONSTRUCTOR
        animal(double init_size = 1, double init_rate = 0, double init_need = 0);
        // MODIFICATION FUNCTIONS
        void assign_need(double new_need);
        void eat(double amount);
        void simulate_week( ); // Overriden from the organism class
        // CONSTANT FUNCTIONS
        double still_need( ) const;
        double total_need( ) const { return need_each_week; }
    private:
        double need_each_week;
        double eaten_this_week;
    };

    class herbivore : public animal
    {
    public:
        // CONSTRUCTOR
        herbivore(double init_size = 1, double init_rate = 0, double init_need = 0);
        // MODIFICATION FUNCTIONS
        void nibble(plant& meal);
    };
}

#endif
