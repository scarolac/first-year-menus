#include "menus.h"
#include "cs_one.h"
#include "cs_two.h"
#include "principles.h"

void base_menu::print()
{
    std::cout << menu_text;
}

main_menu::main_menu()
{
    menu_text = "Main Menu\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - Introduction and information\n";
    menu_text += "2 - CS 1 programs\n";
    menu_text += "3 - CS 2 programs\n";
    menu_text += "4 - Programming Principles and Practices programs\n\n";
    menu_text += "0 - Quit\n";
    menu_text += "Selection: ";
}

base_menu* main_menu::get_next(int choice, bool& is_quit)
{
    base_menu* temp = 0;

    switch(choice)
    {
    case 0:
        is_quit = true;
        break;
    case 1:
        temp = new intro_menu;
        break;
    case 2:
        temp = new cs_one_menu;
        break;
    case 3:
        temp = new cs_two_menu;
        break;
    /*case 4:
        temp = new principles_menu;
        break;
    */
    default:
    {
        //do nothing, pointer already null
    }

    }

    return temp;
}

intro_menu::intro_menu()
{
    menu_text = "Introduction\n";
    menu_text += "This project was my way of combining all the projects from the first year of\n";
    menu_text += "school (the C++ language, followed by data structurs and algorithms in C++)\n";
    menu_text += "and some self learning I had before school using Bjarne Stroustrup's\n";
    menu_text += "Programming Principles and Practices with C++. I wanted to have a menu system\n";
    menu_text += "where each screen is either a menu, or a program, that eventually returns to the\n";
    menu_text += "last menu when exiting.\n\n";
    menu_text += "Any integer input - Return to main menu\n";
    menu_text += "Selection: ";
}

base_menu* intro_menu::get_next(int choice, bool& is_quit)
{
    is_quit = false; //not used, no quit option from intro

    base_menu* temp = 0;

    //keeping in line with other menus, but no option matters, it all goes to main menu
    switch(choice)
    {
    default:
        temp = new main_menu;
        break;
    }

    return temp;
}
