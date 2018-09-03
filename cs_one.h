#ifndef CS_ONE_H
#define CS_ONE_H

#include "menus.h"
#include "cs1/mod1/cs1mod1.h"
#include "cs1/mod2/cs1mod2.h"
#include "cs1/mod3/cs1mod3.h"

class cs_one_menu : public base_menu
{
public:
    cs_one_menu();

    base_menu* get_next(int choice, bool& is_quit);
};

class one_mod_one : public base_menu
{
public:
    one_mod_one();

    base_menu* get_next(int choice, bool& is_quit);
};

class one_mod_two : public base_menu
{
public:
    one_mod_two();

    base_menu* get_next(int choice, bool& is_quit);
};

class one_mod_three : public base_menu
{
public:
    one_mod_three();

    base_menu* get_next(int choice, bool& is_quit);
};

#endif // CS_ONE_H
