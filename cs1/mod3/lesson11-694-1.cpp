// Section CSC160 - Computer Science I: C++
// File Name: lesson11-694-1.cpp
// Student: Chris Scarola
// Homework Number: 11
// Description:
/*
  In Chapter 8 we discussed vectors, which are like arrays that can grow in
size. Suppose that vectors were not defined in C++. Define a class called
VectorDouble that is like a class for a vector with base type double. Your
class VectorDouble will have a private member variable for a dynamic
array of doubles. It will also have two member variables of type int; one
called max_count for the size of the dynamic array of doubles; and one
called count for the number of array positions currently holding values.
(max_count is the same as the capacity of a vector; count is the same as the
size of a vector.)
If you attempt to add an element (a value of type double) to the vector
object of the class VectorDouble and there is no more room, then a new
dynamic array with twice the capacity of the old dynamic array is created
and the values of the old dynamic array are copied to the new dynamic array.
Programming Projects 695
Your class should have all of the following:
* Three constructors: a default constructor that creates a dynamic array
for 50 elements, a constructor with one int argument for the number
of elements in the initial dynamic array, and a copy constructor.
* A destructor.
* A suitable overloading of the assignment operator =.
* A suitable overloading of the equality operator ==. To be equal, the
values of count and the count array elements must be equal, but the
values of max_count need not be equal.
* Member functions push_back, capacity, size, reserve, and resize
that behave the same as the member functions of the same names for
vectors.
* Two member functions to give your class the same utility as the
square brackets: value_at(i), which returns the value of the ith
element in the dynamic array; and change_value_at(d, i), which
changes the double value at the ith element of the dynamic array
to d. Enforce suitable restrictions on the arguments to value_at and
change_value_at. (Your class will not work with the square brackets.
It can be made to work with square brackets, but we have not covered
the material which tells you how to do that.)
 */
// Last Changed: 11/16/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson11_694_1 {

using namespace std;

//handle out of range errors for the custom vector class
struct vect_out_of_range
{};

class VectorDouble
{
private:
    double *elem;  //pointer for element array
    int max_count; //max number positions
    int count;     //number positions used

public:
    VectorDouble();      //default constructor
    VectorDouble(int s); //constructor taking a size

    VectorDouble(const VectorDouble& vd);   //copy constructor
    void operator=(const VectorDouble& vd); //copy assignment

    ~VectorDouble() { delete[] elem; }      //destructor

    void push_back(double d);    //add value to the end of the vector
    int capacity() const { return max_count; } //return max amount of values for vector
    int size() const { return count; }         //return current amount of values for vector
    void reserve(int n);         //add capacity, never remove capacity
    void resize(int n);          //change size

    double& operator[](int n);              //checked modification
    const double& operator[](int n) const;  //checked access

    bool operator==(const VectorDouble& vd);

    friend ostream& operator << (ostream& os, const VectorDouble& vd);
};

void vect_test();
//function to test the VectorDouble class

void run()
{
    clear_screen();

    srand(time(0));
    
    vect_test();    

    keep_window_open("~~");
}

void vect_test()
{    
    try
        {
            cout << "Testing Constructors:\n";
            VectorDouble v1;
            VectorDouble v2(10);
            VectorDouble v3(v2);

            cout << "Capacity of v1 is: " << v1.capacity()
                 << "\nSize of v1 is: " << v1.size();
            cout << "\nCapacity of v2 is: " << v2.capacity()
                 << "\nSize of v2 is: " << v2.size();
            cout << "\nCapacity of v3 is: " << v3.capacity()
                 << "\nSize of v3 is: " << v3.size();

            cout << "\nv2 equals v3: ";
            if(v2 == v3) cout << "true";
            else cout << "false";

            cout << "\n\nTesting member functions:" << endl;
            v1.reserve(60);
            cout << "New capacity of v1 is: " << v1.capacity() << endl;
            cout << "v2 push_back used for 2.7 then 8.3" << endl;
            v2.push_back(2.7);
            v2.push_back(8.3);
            v3 = v2;
            cout << "v3 set to v2 values - v3:\n" << v3;
            v2[0] = 7.9;
            cout << "v2[0] changed to: " << v2[0] << endl;            
            cout << "v2 vector has the following values:\n" << v2;
            v3.resize(12);
            cout << "v3 size is now: " << v3.size()
                 << " with a new capacity of " << v3.capacity() << endl;

            cout << "\nTesting expanding array:" << endl;
            for(int i = 0; i < 37; ++i)
                v2.push_back((rand() % 20) * 1.13);

            cout << "v2 37 random values added past original capacity (10):\n" << v2
                 << "v2 capacity is now: " << v2.capacity()
                 << "\nv2 size is now: " << v2.size() << endl;


            cout << "\nv2 equals v3: ";
            if(v2 == v3) cout << "true";
            else cout << "false";
            
            cout << "\n\nBreak the array:\n";
            cout << "Access v2[-5]: ";
            cout << v2[-5];
            
        }
    catch(vect_out_of_range e)
        {
            cout << "Error: vector index out of range\n";
        }
    catch(...)
        {
            cout << "Unknown exception\n";
        }
}

VectorDouble::VectorDouble() : elem(new double[50]), max_count(50), count(0)
{}

VectorDouble::VectorDouble(int s) : elem(new double[s]), max_count(s), count(0)
{}

VectorDouble::VectorDouble(const VectorDouble& vd)
    : elem(new double[vd.capacity()]), max_count(vd.capacity()), count(vd.size())
{
    for(int i = 0; i < vd.size(); ++i) //fill the new vector
        elem[i] = vd.elem[i];
}

void VectorDouble::operator=(const VectorDouble& vd)
{
    if(max_count < vd.capacity())   //if new vector too small, make larger
        {
            delete[] elem;
            max_count = vd.capacity();
            elem = new double[max_count];
        }
    for(int i = 0; i < vd.capacity(); ++i) //copy the vector data
        elem[i] = vd.elem[i];
    count = vd.size();                     //set the size
}

void VectorDouble::push_back(double d)
{
    if(max_count == 0) reserve(50); //somehow there is an empty vector, give it space
    else if(count == max_count) reserve(max_count * 2); //if vector is full, make more room

    elem[count++] = d; //put d at elem[count] and increment it for next push_back call
}

void VectorDouble::reserve(int n)
{
    if(n > max_count)
        {
            max_count = n;                     //set new max size of vector
            double *p = new double[max_count]; //create temp space for new vector
            for(int i = 0; i < count; ++i) p[i] = elem[i]; //copy data into new vector
            delete[] elem;                     //delete old space
            elem = p;                          //assign temp space into elem name
        }
}

void VectorDouble::resize(int n)
{
    if(n > max_count) reserve(n * 1.5); //if new size too big, make room
        
    if(n < count)   //cut array from new size to old size, clearing data
        for(int i = n; i < count; ++i)
            elem[i] = 0.0;
    else if(n > count) //grow array from old size into new size, setting to 0
        for(int i = count - 1; i < n; ++i)
            elem[i] = 0.0;

    count = n; //new size is n;
        
}

double& VectorDouble::operator[](int n)
{
    if(0 > n || n > count) throw vect_out_of_range();
    return elem[n];
}

const double& VectorDouble::operator[](int n) const
{
    if(0 > n || n > count) throw vect_out_of_range();
    return elem[n];
}

bool VectorDouble::operator==(const VectorDouble& vd)
{
    if(count != vd.count) return false;
    
    for(int i = 0; i < count; ++i)
        if(elem[i] != vd.elem[i]) return false;
    return true;
}

ostream& operator << (ostream& os, const VectorDouble& vd)
{
    for(int i = 0; i < vd.count; ++i)
        os << vd.elem[i] << endl;
    return os;
}

}
