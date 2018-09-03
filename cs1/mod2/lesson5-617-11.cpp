// Section CSC160 - Computer Science I: C++
// File Name: lesson5-617-11.cpp
// Student: Chris Scarola
// Homework Number: 5
// Description:
/*
  Consider a class Movie that contains information about a movie. The class
has the following attributes:
* The movie name
* The MPAA rating (for example, G, PG, PG-13, R)
* The number of people that have rated this movie as a 1 (Terrible)
* The number of people that have rated this movie as a 2 (Bad)
* The number of people that have rated this movie as a 3 (OK)
* The number of people that have rated this movie as a 4 (Good)
* The number of people that have rated this movie as a 5 (Great)
Implement the class with accessor and mutator functions for the movie
name and MPAA rating. Write a function addRating that takes an integer
as an input parameter. The function should verify that the parameter is
a number between 1 and 5, and if so, increment the number of people
rating the movie that match the input parameter. For example, if 3 is
the input parameter, then the number of people that rated the movie as
a 3 should be incremented by 1. Write another function, getAverage,
that returns the average value for all of the movie ratings. Finally, add
a constructor that allows the programmer to create the object with a
specified name and MPAA rating. The number of people rating the movie
should be set to 0 in the constructor.
Test the class by writing a main function that creates at least two movie
objects, adds at least five ratings for each movie, and outputs the movie
name, MPAA rating, and average rating for each movie object.
 */
// Last Changed: 10/2/2016

#include "cs1/mod2/cs1mod2.h"

namespace lesson5_617_11 {

using namespace std;

class Movie
{
private:
    string name;
    string rating;
    int num_rated_1,
        num_rated_2,
        num_rated_3,
        num_rated_4,
        num_rated_5;

public:
    Movie(string n, string r);
    //constructor with name and rating

    void setName(string n) { name = n; }
    string getName() { return name; }
    //access and mutate name

    void setRating(string r) { rating = r; }
    string getRating() { return rating; }
    //access and mutate rating

    void addRating(int rate);
    //increments the rating between 1-5

    double getAverage();
    //returns average of all movie ratings  

};

void run()
{
    clear_screen();

    Movie movie1("Star Wars", "PG");
    Movie movie2("Die Hard", "R");

    movie1.addRating(3);
    movie1.addRating(4);
    movie1.addRating(5);
    movie1.addRating(5);
    movie1.addRating(2);

    movie2.addRating(1);
    movie2.addRating(4);
    movie2.addRating(2);
    movie2.addRating(1);
    movie2.addRating(2);

    cout << movie1.getName() << " has a rating of " << movie1.getRating()
         << " with an average score of " << movie1.getAverage() << endl;

    cout << movie2.getName() << " has a rating of " << movie2.getRating()
         << " with an average score of " << movie2.getAverage() << endl;
    

    keep_window_open("~~");
}

Movie::Movie(string n, string r)
    :name(n),rating(r),
     num_rated_1(0),
     num_rated_2(0),
     num_rated_3(0),
     num_rated_4(0),
     num_rated_5(0)
{}

void Movie::addRating(int rate)
{
    if(rate < 0 || 6 < rate)
        {
            cout << "Rating out of range\n";
            return;
        }

    switch(rate)
        {
        case 1:
            {
                num_rated_1++;
                break;
            }
        case 2:
            {
                num_rated_2++;
                break;
            }
        case 3:
            {
                num_rated_3++;
                break;
            }
        case 4:
            {
                num_rated_4++;
                break;
            }
        case 5:
            {
                num_rated_5++;
                break;
            }
        }
}

double Movie::getAverage()
{
    double sum = num_rated_1 + num_rated_2 + num_rated_3 + num_rated_4 + num_rated_5;
    double rating_power = (num_rated_1 * 1) + (num_rated_2 * 2)
        + (num_rated_3 * 3) + (num_rated_4 * 4) + (num_rated_5 * 5);
    return rating_power / sum;    
}

}
