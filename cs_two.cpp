#include "cs_two.h"

cs_two_menu::cs_two_menu()
{
    menu_text = "Computer Science 2 - Data Structures and Algorithms\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - Module 1: Abstract data types, containers, pointers, dynamic arrays\n";
    menu_text += "2 - Module 2: Linked lists, stacks/queues, recursion, trees\n";
    menu_text += "3 - Module 3: Searching, sorting\n\n";
    menu_text += "0 - Return to main menu\n";
    menu_text += "Selection: ";
}

base_menu* cs_two_menu::get_next(int choice, bool& is_quit)
{
    is_quit = false;

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new main_menu;
        break;

    case 1:
        temp = new two_mod_one;
        break;
        /*
    case 2:
        temp = new two_mod_two;
        break;
    case 3:
        temp = new two_mod_three;
        break;
        */
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}

two_mod_one::two_mod_one()
{
    menu_text = "CS 2 Module 1: Abstract data types, containers, pointers, dynamic arrays\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - lesson 1 - Statistician class tester\n";
    menu_text += "2 - lesson 1 - Statistician class full exam\n";
    menu_text += "3 - lesson 2 - Sequence class - simple bag type class of any item type\n";
    menu_text += "4 - lesson 3 - Sequence class version 2 - dynamic bag class: tester\n";
    menu_text += "5 - lesson 3 - Sequence class version 2 - dynamic bag class: full exam\n\n";
    menu_text += "0 - Return to CS 1 menu\n";
    menu_text += "Selection: ";
}

base_menu* two_mod_one::get_next(int choice, bool &is_quit)
{
    is_quit = false;

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new cs_two_menu;
        break;
    case 1:
        cs2hw1::run_test();
        break;
    case 2:
        cs2hw1::run_exam();
        break;
    case 3:
        cs2hw2::run();
        break;
    case 4:
        cs2hw3::run_test();
        break;
    case 5:
        cs2hw3::run_exam();
        break;
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}
