/*
 *  PassengerQueue.cpp
 *  Harry Lynch
 *  9/24/2024
 *
 *  Implementation of PassengerQueue class with use of std::list.
 *
 */

#include "PassengerQueue.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/*
 * name:      front( )
 * purpose:   Get the passenger at the front of the queue.
 * arguments: none
 * returns:   The passenger at the front of the queue
 * effects:   none
 */
Passenger PassengerQueue::front() {
    runtimeExceptionHelper("get front of");
    return this->PassengerList.front();
}

/*
 * name:      dequeue( )
 * purpose:   Remove the passenger at the front of the queue.
 * arguments: none
 * returns:   none
 * effects:   Removes one passenger from the front of the queue
 */
void PassengerQueue::dequeue() {
    runtimeExceptionHelper("dequeue from an");
    this->PassengerList.pop_front();
}

/*
 * name:      enqueue( )
 * purpose:   Add a passenger at the back of the queue.
 * arguments: Passenger to add
 * returns:   none
 * effects:   Adds one passenger to the back of the queue
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    this->PassengerList.push_back(passenger);
}

/*
 * name:      size( )
 * purpose:   Get the size of the queue.
 * arguments: none
 * returns:   The number of passengers in the queue
 * effects:   none
 */
int PassengerQueue::size() { return this->PassengerList.size(); }

/*
 * name:      print( )
 * purpose:   To feed the contents of a PassengerQueue to an output stream of
 *            the end-user's choosing.
 * arguments: output stream to send the passenger info.
 * returns:   none
 * effects:   modifies the inputted output stream
 */
void PassengerQueue::print(std::ostream &output) {
    // Create an iterator to access elements of a std::list
    std::list<Passenger>::iterator it = this->PassengerList.begin();
    for (; it != this->PassengerList.end(); ++it) {
        it->print(output);
    }
}

/*
 * name:      runtimeExceptionHelper( )
 * purpose:   Private helper function to throw runtime errors for empty-access
 *            methods.
 * arguments: Attempted action to display back to user
 * returns:   none
 * effects:   throws an exception if the queue is empty.
 */
void PassengerQueue::runtimeExceptionHelper(std::string attemptedAction) {
    std::stringstream ss;
    ss << "cannot " << attemptedAction << " empty PassengerQueue";
    if (this->PassengerList.empty())
        throw std::runtime_error(ss.str());
}