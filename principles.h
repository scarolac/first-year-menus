#ifndef PRINCIPLES_H
#define PRINCIPLES_H
#include "menus.h"

class principles_menu : public base_menu
{
public:
    principles_menu();

    base_menu* get_next(int choice, bool& is_quit);
};

#endif // PRINCIPLES_H
