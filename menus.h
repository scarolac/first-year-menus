#ifndef MENUS_H
#define MENUS_H

#include "utilities.h"

class base_menu
{
protected:
    std::string menu_text;
    std::string intro;

public:
    base_menu() { menu_text = "If this is shown, something went wrong";}
    virtual ~base_menu() {}

    virtual base_menu* get_next(int choice, bool& is_quit) = 0;

    virtual void print();
};

class main_menu : public base_menu
{
public:
    main_menu();

    base_menu* get_next(int choice, bool& is_quit);
};

class intro_menu : public base_menu
{
public:
    intro_menu();

    base_menu* get_next(int choice, bool& is_quit);
};

#endif // MENUS_H
