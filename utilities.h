#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <sstream>
#include <cfloat>

void clear_screen();
//clear the screen

void pause();
//prompt to exit

bool prompt();
//prompts the user to continue

void keep_window_open(std::string s);
//holds the window open until the string "~~" is entered

#endif // UTILITIES_H
