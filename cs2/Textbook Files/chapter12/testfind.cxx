#include <algorithm> // Provides the find function
#include <iostream> // Provides getline and cout
#include <string> // Provides the string class
using namespace std;

int main( )
{
    string line;
    string:: iterator i, where_is_e;
    cout << "Please enter a line of text: ";
    getline(cin, line);
    where_is_e = find(line.begin(), line.end(), 'e');
    cout << "You entered the following before entering an e: ";
    for (i = line.begin(); i != where_is_e; ++i)
	cout << *i;
    cout << endl;
    cout << "The rest of your input was: ";
    for (i = where_is_e; i != line.end(); ++i)
	cout << *i;
    cout << endl;
    return 0;
}
