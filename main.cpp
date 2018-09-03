//#include <stdlib.h>
#include "menus.h"

int main()
{
    base_menu* current = new main_menu; //create the main menu
    bool is_quit = false;

    while(!is_quit)
    {
        current->print();

        int option = 0;
        std::cin >> option;

        //only take ints
        while(std::cin.fail())
        {
            std::cout << "Input an integer: ";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> option;
        }

        //use the option selected to determine the next menu to display
        base_menu* next_menu = current->get_next(option,is_quit);

        if(next_menu)
        {
            delete current;
            current = next_menu;
        }

        clear_screen();
    }
    //when the loop ends, quit was selected, delete the current pointer
    delete current;

    //More useful in windows systems
    //pause();
    clear_screen();

    return EXIT_SUCCESS;
}
