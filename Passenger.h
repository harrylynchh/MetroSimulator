/*
 *  Passenger.h
 *  Harry Lynch
 *  9/24/2024
 *
 *  Interface of Passenger class.
 *
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

class Passenger {
  public:
    Passenger(int id, int startingStation, int endingStation);
    int getId();
    int getStartingStation();
    int getEndingStation();
    void print(std::ostream &output);

  private:
    int id;
    int startingStation;
    int endingStation;
};

#endif
