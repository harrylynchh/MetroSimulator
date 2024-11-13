/*
 *  PassengerQueue.h
 *  Harry Lynch
 *  9/24/2024
 *
 *  Interface for PassengerQueue class.
 *
 */

#ifndef __PASSENGER_QUEUE_H__
#define __PASSENGER_QUEUE_H__

#include "Passenger.h"
#include <iostream>
#include <list>

class PassengerQueue {
  public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

  private:
    std::list<Passenger> PassengerList;
    void runtimeExceptionHelper(std::string attemptedAction);
};

#endif
