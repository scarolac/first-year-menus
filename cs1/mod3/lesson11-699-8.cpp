// Section CSC160 - Computer Science I: C++
// File Name: lesson11-699-8.cpp
// Student: Chris Scarola
// Homework Number: 11
// Description:
/*
  Define a class called List that can hold a list of values of type double.
  Model your class definition after the class TemperatureList given in
  Display 11.10, but your class List will make no reference to temperatures
  when it outputs values. The values may represent any sort of data items as
  long as they are of type double. Include the additional features specified in
  Self-Test Exercises 21 and 22. Change the member function names so that
  they do not refer to temperature.
  Add a member function called get_last that takes no arguments and
  returns the last item on the list. The member function get_last does not
  change the list, and it should not be called if the list is empty. Add another
  member function called delete_last that deletes the last element on the
  list. The member function delete_last is a void function. Note that
  when the last element is deleted, the member variable size must be
  adjusted. If delete_last is called with an empty list as the calling object,
  the function call has no effect. Design a program to thoroughly test your
  definition for the class List.
*/
// Last Changed: 11/16/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson11_699_8 {

using namespace std;

class ListDynamic
{
private:
    int size;
    int max_list_size;
    double *list;

    void expand_array();  //double the max_list_size, create new array, delete old array

    ListDynamic(const ListDynamic& l);    //prevent copying
    void operator=(const ListDynamic& l); //prevent assignment

public:
    ListDynamic();
    ~ListDynamic() { delete[] list; }

    void add_value(double val);
    void add_value_sort(double val); //sort data as it is input

    int get_size() { return size; }
    double get_value(int index);

    double get_last();
    double delete_last();

    friend std::ostream& operator << (std::ostream& os, const ListDynamic& obj);
};

void test_list();
//test the listdynamic class

void run()
{
    clear_screen();

    test_list();
    
    keep_window_open("~~");
}

void test_list()
{
    ListDynamic testList, t2;

    double temp;
    
    cout << "Input values, terminate with '0'\n";

    cout << "Enter value: ";
    while(cin >> temp)
        {
            if(temp == 0) break;
            testList.add_value(temp);
            t2.add_value_sort(temp);
            cout << "Enter value: ";
        }
      
    cout << "\nThere are " << testList.get_size() << " values on the list";
    cout << "\nThe first value is " << testList.get_value(0);
    cout << "\nThe last value is " << testList.get_last();
    testList.delete_last();
    cout << "\nAfter deleting last value, there are " << testList.get_size() << " values left";
    cout << "\nThe new list is:\n" << testList << endl;
    cout << "\nSorted original list:\n" << t2 << endl;

    /* From previous homework, but the ListDynamic cannot get full
    while(!testList.full())
        {
            testList.add_value(100.0);
        }

    cout << "\nList filled up at size equal to " << testList.get_size() << endl;   
    cout << "The new list is:\n" << testList << endl;
    */
}

ListDynamic::ListDynamic() : size(0), max_list_size(10),list(new double[10])
{}

void ListDynamic::expand_array()
{
    max_list_size *= 2;                           //double the space
    double *p = new double[max_list_size];        //create new array
    for(int i = 0; i < size; ++i) p[i] = list[i]; //move the data
    delete[] list;                                //get rid of old data
    list = p;                                     //move list pointer to new data
}

void ListDynamic::add_value(double val)
{
    if(size == max_list_size) //if full make larger array
        expand_array();
    list[size++] = val; //add data to list
}

void ListDynamic::add_value_sort(double val)
{
    if(size == max_list_size) //if full make larger array
        expand_array();
    else
        {
            if(list[size - 1] <= val) //if it is larger than previous then add it
                list[size] = val;
            else                      //look for an item that is larger then add it
                {
                    for(int i = 0; i <= size; ++i)
                        {
                            if(list[i] > val)
                                //once item is found larger than val
                                //move the whole array back one
                                //break out of loop
                                {
                                    for(int j = size; j > i; --j)
                                        list[j] = list[j-1];
                                    list[i] = val;
                                    break;
                                }
                        }
                }
            
            ++size;
        } 
}

double ListDynamic::get_value(int index)
{
    if(0 < index || index < size)
        return (list[index]);
    else
        cout << "\nget_value call out of bounds, index should be 0 - " << size << endl;

    return 0;
}

double ListDynamic::get_last()
{
    if(size == 0) cout << "\nArray empty, no last value\n";
    else
        return list[size - 1];

    return 0;
}

double ListDynamic::delete_last()
{
    if(size == 0) cout << "\nNothing deleted, array is empty\n";
    else
        {
            list[size - 1] = 0.0;
            --size;
        }

    return 0;
}

ostream& operator << (ostream& os, const ListDynamic& obj)
{
    for(int i = 0; i < obj.size; ++i)
        os << obj.list[i] << " ";
    return os;
}

}
