#include <iostream>
#include "ShoppingCart.h"
using namespace std;
const int ALLOCATE_SIZE = 10;

// Implementation of the ShoppingCartException class
ShoppingCartException::ShoppingCartException(): ApplicationException()
{    message = "Error Detected in Shopping Cart Class";  }

ShoppingCartException::ShoppingCartException(string errorMsg): ApplicationException()
{    message = errorMsg;  }

ShoppingCartException::ShoppingCartException(char errorMsg[]): ApplicationException()
{    message = errorMsg; }


// Implementation of the ShoppingCart class
ShoppingCart::ShoppingCart()
{
    cartItems = new string[ALLOCATE_SIZE];
    numItems = 0;
    allocatedItems = ALLOCATE_SIZE;
}
void ShoppingCart::addToCart(string item)
{
    if (numItems == allocatedItems)
        increaseCartAllocation(ALLOCATE_SIZE);
    numItems++;
    cartItems[numItems - 1] = item;
}

void ShoppingCart::addToCart(char item[])
{
    if (numItems == allocatedItems)
        increaseCartAllocation(ALLOCATE_SIZE);
    numItems++;
    cartItems[numItems - 1] = item;
}

string ShoppingCart::getItem(string itemDesc)
{
    for (int i = 0; i < numItems; i++)
        if (cartItems[i] == itemDesc)
            return cartItems[i];
    throw ShoppingCartException("Item " + itemDesc + " is not in Shopping Cart");
}
string ShoppingCart::getItem(char itemDesc[])
{
    string temp = itemDesc;
    string errorMsg = "Item is not in Shopping Cart";
    for (int i = 0; i < numItems; i++)
	if (cartItems[i] == temp)
            return cartItems[i];
    throw ShoppingCartException(errorMsg);
}
string ShoppingCart::getItem(int itemNumber)
{
    string errorMsg = "Item number is too large";
    if (itemNumber > numItems - 1)
	{
            ShoppingCartException temp(errorMsg);
            throw temp;
	}
    else
        return cartItems[itemNumber];
}

void ShoppingCart::increaseCartAllocation(int count)
{
    allocatedItems += count;
    string *temp = new string[allocatedItems];
    for (int i = 0; i < numItems; i++)
        temp[i] = cartItems[i];
    cartItems = temp;
}
