/*
 *  Train.h
 *  Harry Lynch
 *  9/24/2024
 *
 *  Interface for Train class.
 *
 */

#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <vector>

class Train {
  public:
    Train();
    Train(int numStations);
    void print(std::ostream &output);
    void boardPassenger(Passenger pass);

    // Get and set currStation
    int getCurrentStation();
    void setCurrentStation(int station);
    void makeQueues(int numStations);

    PassengerQueue dropOff();

  private:
    int currStation;
    std::vector<PassengerQueue> trainQueues;
};

#endif
