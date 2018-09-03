// FILE: linear.h
// CLASS PROVIDED:
//   class linear_function (in the namespace main_savitch_2)
//     A linear function (of one variable) is a function of the form
//     f(x) = m*x + b
//     where m and b are real numbers, and x is a real number variable.
//     The values of m and b are the slope and y-intercept of the 
//     function's graph.
//
// CONSTRUCTOR for the linear_function class
//   linear_function(double _b = 0, double _m = 0)
//     POSTCONDITION: This linear function has been created and set to
//     the function f(x) = _m * x + _b.
//     EXAMPLES:
//     linear_function f(1.3, -6.85); // f(x) = -6.85*x + 1.3
//     linear_function g(42);         // g(x) = 42
//     linear_function h;             // h(x) = 0
//     linear_function fahrenheit_to_celsius(-32, 5.0/9.0);
//
// MODIFICATION MEMBER FUNCTIONS for the linear_function class
//   void set(double _b = 0, double _m = 0)
//   POSTCONDITION: This linear function has been set to the function
//   f(x) = _m*x + b.
//
// CONSTANT MEMBER FUNCTIONS for the linear_function class
//   void draw(double low_x, double high_x, double low_y, double high_y) const
//     PRECONDITION: There is an open winbgi graphics window.
//     Also (low_x < high_x) && (low_y < high_y).
//     POSTCONDITION: A graph of the linear_function has been drawn in the
//     graphics window for x values in the range (low_x...high_x) and y values
//     in the range (low_y...high_y).
//
//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this linear function
//     applied to the given value for the variable x.  For example, if f is
//     the linear function f(x) = 10x + 2, then f.eval(4) returns 42.
//
//   double root( ) const
//     POSTCONDITION: The return value is the root of this linear equation
//     calculated with the formula -b/m, where b and m are the y-intercept and
//     slope.  Note: If the slope is equal to zero (or too near zero), then the
//     division -b/m results in an arithmetic error.
//
//   double slope( ) const
//     POSTCONDITION: Returns the slope of this linear function
//     (i.e., the coefficient m in f(x) = m*x + b).
//
//   double y_intersept( ) const
//     POSTCONDITION: Returns the y of this linear function
//     (i.e., the constant b in f(x) = m*x + b).
//
// CONSTANT OPERATORS for the linear_function class
//   double operator ( ) (double x) const
//     The () operator is the same as the eval member function, so that
//     for a linear function f, the notation f(x) is the same as f.eval(x).
//
// NON-MEMBER BINARY OPERATORS for the linear_function class
//   linear_function operator -
//     (const linear_function& f1, const linear_function& f2)
//     POSTCONDITION: The return value is a linear_function with each
//     coefficient equal to the difference of the coefficients of f1 and f2.
//     For example, suppose f1(x) = 10*x + 5 and f2(x) = 3*x + 2.
//     Then f1 - f2 is the linear function 7*x + 3.
//
//   linear_function operator +
//     (const linear_function& f1, const linear_function& f2)
//     POSTCONDITION: The return value is a linear_function with each
//     coefficient equal to the sum of the coefficients of f1 and f2.
//     For example, suppose f1(x) = 10*x + 5 and f2(x) = 3*x + 2.
//     Then f1 + f2 is the linear function 13*x + 7.
//
//   linear_function operator |
//     (const linear_function& f1, const linear_function& f2)
//     POSTCONDITION: The return value is the functional composition of
//     f1 and f2.
//     Note: For any linear functions f1 and f2, and any double number x:
//     (f1 | f2)(x) is always the same as f1(f2(x)).
//
// NON-MEMBER OUTPUT FUNCTIONS for the linear_function Class
//   ostream& operator << (ostream& out, const linear_function& p)
//     POSTCONDITION: The linear_function has been printed to ostream out.
//     The return value is the ostream out.
//     EXAMPLE (notice the spacing and format for negative coefficients):
//     linear_function f(1.3, -6.85), g(-1.3, 6.85), h(1.3); k(-1.3);
//     cout << f << endl;    // Prints: -6.85x + 1.3
//     cout << g << endl;    // Prints: 6.85x - 1.3
//     cout << h << endl;    // Prints: 1.3
//     cout << k << endl;    // Prints: -1.3
//

#ifndef LINEAR_H
#define LINEAR_H
#include <iostream>  // Provides ostream

namespace main_savitch_2
{
    
    class linear_function
    {
    public:
	
    private:

    };
    
    // NON-MEMBER BINARY OPERATORS
    linear_function operator +
	(const linear_function& f1, const linear_function& f2);
    linear_function operator -
	(const linear_function& f1, const linear_function& f2);
    linear_function operator |
	(const linear_function& f1, const linear_function& f2);
    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const linear_function& p);

}
#endif
