#ifndef CS_TWO_H
#define CS_TWO_H

#include "menus.h"
#include "cs2/mod1/cs2mod1.h"

class cs_two_menu : public base_menu
{
public:
    cs_two_menu();

    base_menu* get_next(int choice, bool& is_quit);
};

class two_mod_one : public base_menu
{
public:
    two_mod_one();

    base_menu* get_next(int choice, bool& is_quit);
};

class two_mod_two : public base_menu
{
public:
    two_mod_two();

    base_menu* get_next(int choice, bool& is_quit);
};

class two_mod_three : public base_menu
{
public:
    two_mod_three();

    base_menu* get_next(int choice, bool& is_quit);
};

#endif // CS_TWO_H
