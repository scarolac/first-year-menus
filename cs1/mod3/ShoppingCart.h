using namespace std;
#ifndef CART_H
#define CART_H
#include <string>
#include "ApplicationException.h"

class ShoppingCartException : public ApplicationException
{
public:
    ShoppingCartException();
    ShoppingCartException(string errorMsg);
    ShoppingCartException(char errorMsg[]);
};

class ShoppingCart
{
public:
    ShoppingCart();
    void addToCart(string itemDesc);
    void addToCart(char itemDesc[]);
    string getItem(string itemDesc);
    string getItem(char itemDesc[]);
    string getItem(int itemNumber);

private:
    string *cartItems;
    int numItems;
    int allocatedItems;
    void increaseCartAllocation(int count);
};

#endif
