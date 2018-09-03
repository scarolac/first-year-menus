#include "list.h"

List::List() : size(0) {}

bool List::full() const
{
    return (size == MAX_LIST_SIZE);
}

bool List::bounded(int index) const
{
    return (0 <= index || index < MAX_LIST_SIZE);
}

void List::add_value(double val)
{
    if(full())
        std::cout << "\nCannot add to full array\n";
    else
        {
            list[size] = val;
            size++;
        }
}

void List::add_value_sort(double val)
{
    if(full())
        std::cout << "\nCannot add to full array\n";
    else
        {
            if(list[size - 1] <= val) //if it is larger than previous then add it
                list[size] = val;
            else                      //look for an item that is larger then add it
                {
                    for(int i = 0; i <= size; ++i)
                        {
                            if(list[i] > val)
                                //once item is found larger than val
                                //move the whole array back one
                                //break out of loop
                                {
                                    for(int j = size; j > i; --j)
                                        list[j] = list[j-1];
                                    list[i] = val;
                                    break;
                                }
                        }
                }
            
            ++size;
        } 
}

double List::get_value(int index)
{
    if(bounded(index))
        {
            return (list[index]);
        }
    else
        {
            std::cout << "\nOut of bounds for array, index should be 0 - "
                      << MAX_LIST_SIZE << std::endl;
        }
    return 0;
}

double List::get_last()
{
    if(size == 0) std::cout << "\nNothing to return, array is empty\n";
    else
        return list[size - 1];
    return 0;
}

double List::delete_last()
{
    if(size == 0) std::cout << "\nNothing deleted, array is empty\n";
    else
        {
            list[size - 1] = 0.0;
            --size;
        }
    return 0;
}

std::ostream& operator << (std::ostream& os, const List& obj)
{
    for(int i = 0; i < obj.size; ++i)
        os << obj.list[i] << " ";
    return os;
}
