// FILE: tableTest.cxx
// Written by: Steve Kaminski
// A general test program to exercise implementations of the table class

#include <iostream>
#include <fstream>
#include <string>
#include "table2.h"    // Provides the chained hash table class

using namespace std;
using namespace main_savitch_12B;

// **************************************************************************
// TableRecord type
//   Each table will use the following data type for its entries, with
//   keys ranging from 0 through MAX_KEY.
// **************************************************************************
struct TableRecord
{
    int key;
    double data;
};
const int MAX_KEY = 5000;
const int TABLE_SIZE = 811; // Knowing how table2 was implemented

int main()
{
    cout << "*************************************";
    cout << "\nCSC-161 Homework Eleven Solution\n";
    cout << "*************************************";
    // Create a table and add some values to it
    Table<TableRecord> testTable;
    TableRecord testRecord;
    // Add 100 records to our table to get started
    for (int index = 0; index < 100; index++)
    {
        // Calculate a data value and a key for the record
        testRecord.data = (double) index * 50;
        testRecord.key = index * 50;
        testTable.insert(testRecord);
    }
    // Add a record that has the same key as existing: shouldn't affect count
    testRecord.data = 99.0;
    testRecord.key = 300;
    testTable.insert(testRecord);
    
    // Add some records that should generate collisions, knowing how we calculate
    //  the hash code as key % TABLE_SIZE, with size set to 811
    testRecord.data = 99.0;
    testRecord.key = TABLE_SIZE;
    testTable.insert(testRecord);
    testRecord.data = 99.0;
    testRecord.key = TABLE_SIZE * 2;
    testTable.insert(testRecord);
    testRecord.data = 99.0;
    testRecord.key = TABLE_SIZE * 10;
    testTable.insert(testRecord);
   
    
    // Show the results of our insertions
    cout << "\nAdded " << testTable.size() << " records to the test table" << endl;
    cout << "*************************************";
    // Try to remove some known key values, including some duplicates and some that collided
    testTable.remove(100);
    testTable.remove(150);
    testTable.remove(1500);
    testTable.remove(250);
    testTable.remove(250);
    testTable.remove(3750);
    testTable.remove(4900);
    testTable.remove(TABLE_SIZE * 2);
    testTable.remove(TABLE_SIZE);
    // Show the results after our removals
    cout << "\nAfter removals there are " << testTable.size() << " records in the test table" << endl;
    cout << "*************************************";
    // Search for some values that should and should not be there
    cout << "\nTry some searches for key values\n";
    bool found = false;
    for (int index = 0; index < MAX_KEY; index = index + 150)
    { 
        testTable.find(index, found, testRecord);
        if (found)
            cout << "Found record with key value " << index << ", data = " << testRecord.data << endl;
        else
            cout << "Did not find record with key value " << index << endl;
    }
    // Find the collision record that should still be there using is_present
    if (testTable.is_present(TABLE_SIZE * 10))
        cout << "\nSuccessfully found record with key equal to " << TABLE_SIZE * 10 << endl;
    else
        cout << "\n?? Failed to find record with key equal to " << TABLE_SIZE * 10 << endl;


    
    cout << "*************************************"<< endl;
    cout << "End of Homework Eleven Solution" << endl;
    cout << "*************************************" << endl;
    return EXIT_SUCCESS;
}

