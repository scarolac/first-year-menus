// Section CSC160 - Computer Science I: C++
// File Name: lesson3-300-5.cpp
// Student: Chris Scarola
// Homework Number: 3
// Description:
/*
  In cold weather, meteorologists report an index called the windchill factor,
that takes into account the wind speed and the temperature. The index
provides a measure of the chilling effect of wind at a given air temperature.
Windchill may be approximated by the formula:
W = 13.12 + (0.6215 * t) - (11.37 * v^0.16) + (0.3965 * t) * (v^0.16)
where
v = wind speed in m/sec
t = temperature in degrees Celsius: t <= 10
W = windchill index (in degrees Celsius)
Write a function that returns the windchill index. Your code should ensure
that the restriction on the temperature is not violated. Look up some
weather reports in back issues of a newspaper in your university library and
compare the windchill index you calculate with the result reported in the
newspaper.
 */
// Last Changed: 9/9/2016

#include "cs1/mod1/cs1mod1.h"

namespace lesson3_300_5 {

void intro();
//introduces the program and requirements

int get_temp();
//receives temperature in degrees C

int get_wind_speed();
//recieves windspeed in m/s

double windchill_index(int& temp, int& ws);
//calculates and returns windchill index

void output_data(double wci);
//outputs the windchill index

void run()
{
    int temperature, wind_speed;
    double windchill;

    do
    {
        clear_screen();

        intro();

        temperature = get_temp();

        wind_speed = get_wind_speed();

        windchill = windchill_index(temperature, wind_speed);

        output_data(windchill);

    }
    while(prompt());
}

void intro()
{
    using namespace std;
    cout << "Windchill Calculator\n"
         << "Calculates windchill based on temperature (C) and wind speed (m/s)\n";
}

int get_temp()
{
    int temp;
    using namespace std;
    
    cout << "\nEnter temperature in Celsius (t <= 10): ";
    while(cin >> temp)
    {
        if(temp > 10) cout << "Input temperature <= 10 C: ";
        else break;
    }
    return temp;
}

int get_wind_speed()
{
    int ws;
    using namespace std;
    
    cout << "Enter wind speed in meters/second: ";
    cin >> ws;

    return ws;
}

double windchill_index(int& temp, int& ws)
{
    return (13.12 + (0.6215 * temp) - (11.37 * pow(ws,0.16)) + (0.3965 * temp) * (pow(ws,0.16)));
}

void output_data(double wci)
{
    using namespace std;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    cout << "Windchill factor is " << wci << endl;
}

}

