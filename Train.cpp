/*
 *  Train.cpp
 *  Harry Lynch
 *  9/24/2024
 *
 *  Implementation of Train class.
 *
 */

#include "Train.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/*
 * name:      Train( )
 * purpose:   Default contstructor
 * arguments: none
 * returns:   none
 * effects:   creates a new Train object setting starting station to 0
 *            note that this doesn't instantiate queues for stations, user must
 *            run makeQueues() once they've aggregated the total # of stations.
 */
Train::Train() { this->currStation = 0; }

/*
 * name:      Train( )
 * purpose:   Contstructor with queues
 * arguments: total # of stations in the sim
 * returns:   none
 * effects:   creates a new Train object setting starting station to 0
 *            and creates a queue for each station to hold passengers.
 */
Train::Train(int numStations) {
    makeQueues(numStations);
    this->currStation = 0;
}

/*
 * name:      makeQueues( )
 * purpose:   Default contstructor
 * arguments: none
 * returns:   none
 * effects:   creates a new Train object setting starting station to 0
 *            note that this doesn't instantiate queues for stations, user must
 *            run makeQueues() once they've aggregated the total # of stations.
 */
void Train::makeQueues(int numStations) {
    for (int i = 0; i < numStations; i++) {
        this->trainQueues.push_back(PassengerQueue());
    }
}

/*
 * name:      print( )
 * purpose:   create formatted output for all passengers currently on train
 * arguments: output stream to print to
 * returns:   none
 * effects:   adds formatted output to the provided stream
 */
void Train::print(std::ostream &output) {
    output << "{";
    for (int i = 0; i < int(this->trainQueues.size()); i++) {
        PassengerQueue &currQueue = this->trainQueues.at(i);
        currQueue.print(output);
    }
    output << "}";
}

/*
 * name:      boardPassenger( )
 * purpose:   add a passenger to the proper train "car" (queue of dep station)
 *            this ensures that train is properly ordered in UI
 * arguments: passenger to board
 * returns:   none
 * effects:   adds a passenger to the respective queue in the train with
 *            respect to the passenger's departure station
 */
void Train::boardPassenger(Passenger pass) {
    // find the queue of the passenger's departure and enqueue the passenger
    this->trainQueues.at(pass.getEndingStation()).enqueue(pass);
}

/*
 * name:      getCurrentStation( )
 * purpose:   return value of private member currStation
 * arguments: none
 * returns:   integer of station train is at
 * effects:   none
 */
int Train::getCurrentStation() { return this->currStation; }

/*
 * name:      setCurrentStation( )
 * purpose:   set the position of a train to a given station
 * arguments: integer index of station to move train to
 * returns:   nothing
 * effects:   changes the current station of the train
 */
void Train::setCurrentStation(int station) { this->currStation = station; }

/*
 * name:      dropOff( )
 * purpose:   Once arriving to a station, remove passengers departing at that
 *            station and return the queue of those passengers.
 * arguments: none
 * returns:   the queue of passengers departing so they can be logged by
 * MetroSim effects:   dequeues all passengers in the queue directly related to
 * the current station.
 */
PassengerQueue Train::dropOff() {
    PassengerQueue &exitingPassengers = this->trainQueues.at(this->currStation);
    // Create a copy to return to MetroSim
    PassengerQueue exitCpy = this->trainQueues.at(this->currStation);
    // remove Passengers from the train
    while (exitingPassengers.size() != 0) {
        exitingPassengers.dequeue();
    }
    return exitCpy;
}