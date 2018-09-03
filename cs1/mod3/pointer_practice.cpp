#include "cs1/mod3/cs1mod3.h"

namespace pointer_practice {

void run()
{
    clear_screen();

    int **p = new int*[3];

    p[0] = new int;
    p[1] = new int;
    p[2] = new int;
    *p[1] = 3;

    std::cout << "Addresses\n";
    for(int i = 0; i < 3; ++i)
        std::cout << &p[i] << std::endl;

    std::cout << "\nAddresses of next level\n";
    
    for (int i = 0; i < 3; ++i)
        std::cout << p[i] << std::endl;

    std::cout << "\nValues\n";
    for (int i = 0; i < 3; ++i)
        std::cout << *p[i] << std::endl;

    for(int i = 0; i < 3; ++i)
        delete p[i];
    delete p;
    

    keep_window_open("~~");
}

}
