#include "statistician.h"
#include <iostream>
using namespace main_savitch_2C;

namespace cs2hw1 {

void print(statistician s);
//print the statistician values

void run_test()
{ 
    clear_screen();

    using namespace std;
    
    statistician s;
    s.next_number(5);
    s.next_number(-15);
    s.next_number(3.4);
    cout << "Statistician s: " << endl;
    print(s);

    statistician t;
    t.next_number(4);
    t.next_number(93);
    t.next_number(-9);
    cout << "Statistician t: " << endl;
    print(t);
    
    statistician u;
    u = s + t;
    cout << "Statistician u: " << endl;
    print(u);

    t = 2 * t;
    cout << "Statistician t: " << endl;
    print(t);

    t.reset();

    statistician v;
    v = t;
    cout << "Statistician v: " << endl;
    print(v);
    

    cout << "is t == v" << endl;
    if(t == v) cout << "yes" << endl;
    else cout << "no" << endl;

    keep_window_open("~~");
}

}
