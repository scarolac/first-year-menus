#include "cs_one.h"

cs_one_menu::cs_one_menu()
{
    menu_text = "Computer Science 1 - C++ language\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - Module 1: C++ Basics, flow control, functions, and I/O\n";
    menu_text += "2 - Module 2: Classes, overloaded operators, separate compilation & namespaces\n";
    menu_text += "3 - Module 3: Arrays, vectors, inheritance\n\n";
    menu_text += "0 - Return to main menu\n";
    menu_text += "Selection: ";
}

base_menu* cs_one_menu::get_next(int choice, bool &is_quit)
{
    is_quit = false; //not used

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new main_menu;
        break;
    case 1:
        temp = new one_mod_one;
        break;

    case 2:
        temp = new one_mod_two;
        break;

    case 3:
        temp = new one_mod_three;
        break;   
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}

one_mod_one::one_mod_one()
{
    menu_text = "CS 1 Module 1: C++ Basics, flow control, functions, and I/O\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - lesson 1 - Babylonian square root algorithm\n";
    menu_text += "2 - lesson 1 - Volume of a sphere\n";
    menu_text += "3 - lesson 1 - Loan calculation\n";
    menu_text += "4 - lesson 2 - Rock, paper, scissors\n";
    menu_text += "5 - lesson 2 - Primes between 3-100\n";
    menu_text += "6 - lesson 2 - \"crud\" population growth with fibonacci\n";
    menu_text += "7 - lesson 3 - Fraction to decimal\n";
    menu_text += "8 - lesson 3 - Interest calculation and payoff time\n";
    menu_text += "9 - lesson 3 - Windchill factor calculation\n";
    menu_text += "10 - lesson 4 - Calculate average from file I/O\n";
    menu_text += "11 - lesson 4 - File I/O \"advice\"\n";
    menu_text += "12 - lesson 4 - Find name in file list of baby names\n\n";
    menu_text += "0 - Return to CS 1 menu\n";
    menu_text += "Selection: ";
}

base_menu* one_mod_one::get_next(int choice, bool &is_quit)
{
    is_quit = false;

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new cs_one_menu;
        break;
    case 1:
        lesson1_104_2::run();
        break;
    case 2:
        lesson1_105_5::run();
        break;
    case 3:
        lesson1_106_4::run();
        break;
    case 4:
        lesson2_172_1::run();
        break;
    case 5:
        lesson2_173_5::run();
        break;
    case 6:
        lesson2_176_6::run();
        break;
    case 7:
        lesson3_245_3::run();
        break;
    case 8:
        lesson3_246_6::run();
        break;
    case 9:
        lesson3_300_5::run();
        break;
    case 10:
        lesson4_368_2::run();
        break;
    case 11:
        lesson4_369_5::run();
        break;
    case 12:
        lesson4_373_10::run();
        break;
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}

one_mod_two::one_mod_two()
{
    menu_text = "CS 1 Module 2: Classes, overloaded operators, separate compilation & namespaces\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - lesson 5 - Class usage - accounting example\n";
    menu_text += "2 - lesson 5 - Rational number math with classes\n";
    menu_text += "3 - lesson 5 - Movie class - information\n";
    menu_text += "4 - lesson 6 - Rational class round 2\n";
    menu_text += "5 - lesson 7 - Unnamed namespace usage\n";
    menu_text += "6 - lesson 7 - Rational class, separate files\n";
    menu_text += "7 - lesson 8 - Student Exception classes\n\n";
    menu_text += "0 - Return to CS 1 menu\n";
    menu_text += "Selection: ";
}

base_menu* one_mod_two::get_next(int choice, bool &is_quit)
{
    is_quit = false;

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new cs_one_menu;
        break;
    case 1:
        lesson5_611_1::run();
        break;
    case 2:
        lesson5_614_7::run();
        break;
    case 3:
        lesson5_617_11::run();
        break;
    case 4:
        lesson6_695_2::run();
        break;
    case 5:
        lesson7_737_5::run();
        break;
    case 6:
        lesson7_738_2::run();
        break;
    case 7:
        lesson8_students::run();
        break;
    case 12:
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}

one_mod_three::one_mod_three()
{
    menu_text = "CS 1 Module 3: Arrays, vectors, inheritance\n";
    menu_text += "Please make your selection\n";
    menu_text += "1 - lesson 9 - Arrays: std deviation, mean\n";
    menu_text += "2 - lesson 9 - Arrays with file I/O\n";
    menu_text += "3 - lesson 9 - List class, with array\n";
    menu_text += "4 - lesson 10 - Pig latin converter\n";
    menu_text += "5 - lesson 10 - Vector with File I/O\n";
    menu_text += "6 - lesson 11 - Vector class for doubles\n";
    menu_text += "7 - lesson 11 - Dynamic list of doubles\n";
    menu_text += "8 - lesson 12 - Inheritance practice\n";
    menu_text += "9 - pointer practice - tracking pointers and addresses\n\n";
    menu_text += "0 - Return to CS 1 menu\n";
    menu_text += "Selection: ";
}

base_menu* one_mod_three::get_next(int choice, bool &is_quit)
{
    is_quit = false;

    base_menu* temp = 0;
    switch(choice)
    {
    case 0:
        temp = new cs_one_menu;
        break;
    case 1:
        lesson9_441_4::run();
        break;
    case 2:
        lesson9_441_5::run();
        break;
    case 3:
        lesson9_699_8::run();
        break;
    case 4:
        lesson10_498_7::run();
        break;
    case 5:
        lesson10_502_10::run();
        break;
    case 6:
        lesson11_694_1::run();
        break;
    case 7:
        lesson11_699_8::run();
        break;
    case 8:
        lesson12_887_8::run();
        break;
    case 9:
        pointer_practice::run();
        break;
    default:
    {
        //intentionally blank
    }

    }

    return temp;
}
