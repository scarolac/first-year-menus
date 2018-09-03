#ifndef LIST_H
#define LIST_H

#include "cs1/mod3/cs1mod3.h"

const int MAX_LIST_SIZE = 50;

class List
{
public:
    List();
    
    bool full() const;    //return true if list is full
    
    void add_value(double val);
    void add_value_sort(double val); //sort data as it is input

    int get_size() { return size; }
    double get_value(int index);

    double get_last();
    double delete_last();

    friend std::ostream& operator << (std::ostream& os, const List& obj);
    
private:
    double list[MAX_LIST_SIZE];
    int size;

    bool bounded(int index) const; //return true if in range 0-MAX_LIST_SIZE
};


#endif
