// Section CSC160 - Computer Science I: C++
// File Name: lesson12-887-5.cpp
// Student: Chris Scarola
// Homework Number: 12
// Description: ShippingContainer parent class with derived
//    RFID and manual shipping container classes
// Last Changed: 11/30/2016

#include "cs1/mod3/cs1mod3.h"

namespace lesson12_887_8 {

using namespace std;

template<class T> string to_string(T t);
//converts objects to string for non c++11

class ShippingContainer
{
private:
    int ID_number;
    
public:
    ShippingContainer() : ID_number(0) {}

    //copy, assignment, destructor trio
    ShippingContainer(const ShippingContainer& s) : ID_number(s.ID()) {}
    void operator=(const ShippingContainer& s) { ID_number = s.ID(); }
    ~ShippingContainer() {}
    
    int ID() const { return ID_number; }
    void ID(int n) { ID_number = n; }

    virtual string getManifest() const { return ""; }

    //does nothing in this class, used in derived classes, for polymorphism
    virtual void setManifest(string s){}
    virtual void add(string s){}
};

class ManualShippingContainer : public ShippingContainer
{
private:
    string manifest;

public:
    ManualShippingContainer() : ShippingContainer(), manifest("") {}

    //copy, assignment, destructor trio
    ManualShippingContainer(const ManualShippingContainer& ms)
        : ShippingContainer(ms), manifest(ms.getManifest()) {}
    ManualShippingContainer& operator=(const ManualShippingContainer& ms)
    {
        ShippingContainer::operator=(ms);
        manifest = ms.getManifest();
    }          
    ~ManualShippingContainer() {}
    
    void setManifest(string s) { manifest = s; }
    string getManifest() const { return manifest; }
};

class RFIDShippingContainer : public ShippingContainer
{
private:
    vector<string> items;
    vector<int> counts;

public:
    RFIDShippingContainer() : ShippingContainer() {}

    //copy, assignment, destructor trio
    RFIDShippingContainer(const RFIDShippingContainer& rfs)
        : ShippingContainer(rfs), items(rfs.items), counts(rfs.counts)
    {}
    RFIDShippingContainer& operator=(const RFIDShippingContainer& rfs)
    {
        ShippingContainer::operator=(rfs);
        items = rfs.items;
        counts = rfs.counts;
    }
    ~RFIDShippingContainer() {}

    string getManifest() const;
    void add(string s);
    
};

string RFIDShippingContainer::getManifest() const
{
    string s;
    for(int i = 0; i < items.size(); ++i)
        {
            s += to_string(counts[i]) + " " + items[i] + ". ";
        }
    return s;
}

void RFIDShippingContainer::add(string s)
{
    for(int i = 0; i < items.size(); ++i)
        {
            if(s == items[i])
                {
                    ++counts[i]; //if a duplicate is found, increment the counter
                    return;      //then exit the function
                }    
        }
    //if not found add item and make another count index
    items.push_back(s);
    counts.push_back(1);
}

void test_inheritance();
//various lines to test inheritance with shipping container classes

void run()
{
    clear_screen();

    test_inheritance();    

    keep_window_open("~~");
}

void test_inheritance()
{
    
    ShippingContainer *t[6];
	
    //set 3 manual and 3 rfid containers
    for(int i = 0; i < 3; ++i)
        t[i] = new ManualShippingContainer;
    for(int i = 3; i < 6; ++i)
        t[i] = new RFIDShippingContainer;
    
     for(int i = 0; i < 6; ++i)
        t[i]->ID((i + 1) * 100);
    
    t[0]->setManifest("1000 diapers");
    t[1]->setManifest("1000 candy bars. 500 toilet paper rolls.");
    t[2]->setManifest("500 books");

    t[3]->add("apples");
    t[3]->add("apples");
    t[3]->add("cookies");
    
    t[4]->add("pineapples");
    t[4]->add("pineapples");
    t[4]->add("pears");
    t[4]->add("pears");
    
    t[5]->add("chocolate bars");
    t[5]->add("chocolate bars");
    t[5]->add("chocolate bars");
    

    ShippingContainer *SC = new ManualShippingContainer;
    SC->ID(202);
    SC->setManifest("Trains, all of them");
    
    RFIDShippingContainer test;
    test.ID(12);
    test.add("buckets");
    test.add("trees");
    test.add("buckets");
    test.add("cars");
    test.add("buckets");
    ManualShippingContainer test2;
    test2.ID(19);
    test2.setManifest("A bunch of monkeys");

    cout << "Test non array\n";
    cout << "Container ID " << test.ID() << " contains: " << test.getManifest() << endl;
    cout << "Container ID " << test2.ID() << " contains: " << test2.getManifest() << endl;
    cout << "Container ID " << SC->ID() << " contains: " << SC->getManifest() << endl;

    cout << "\nTest pointer array of base class with derived classes\n";
    for(int i = 0; i < 6; ++i)
      cout << "Container ID " << t[i]->ID() << " contains: " << t[i]->getManifest() << endl;

    //delete the objects created in the array of pointers
    for(int i = 0; i < 6; ++i)
        delete t[i];
}

template<class T> string to_string(T t)
{
    ostringstream oss;
    oss << t;
    return oss.str();
}

}
