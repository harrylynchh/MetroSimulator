/*
 *  unit_tests.h
 *  Harry Lynch
 *  9/18/2024
 *
 *  Implementation of tests for methods associated with the Passenger and
 *  PassengerQueue classes
 *  NOTE: Use Autumn-Moon.unit_test vscode extension to run
 */
#include "Passenger.h"
#include "PassengerQueue.h"
#include <cassert>
#include <iostream>
using namespace std;

// Verify that the implementation of the Passenger print() method correctly
// outputs to the output stream specified.
void P_passengerPrint_test() {
    Passenger test = Passenger(1, 1, 2);
    Passenger test2 = Passenger(2, 5, 2);

    // print to cout and verify in the test output that the proper string is
    // printed and to the correct stream
    test.print(cout);
    test2.print(cout);
    // test for cerr
    test.print(cerr);
    test2.print(cerr);
}

// Verify that the implementation of the PassengerQueue print() method correctly
// iterates through each element and prints to the correct ostream.
void PQ_queuePrint_test() {
    Passenger test = Passenger(1, 1, 2);
    Passenger test2 = Passenger(2, 1, 2);
    Passenger test3 = Passenger(3, 2, 1);
    Passenger test4 = Passenger(4, 3, 2);
    Passenger test5 = Passenger(5, 1, 4);

    PassengerQueue queue;
    // Add each passenger to queue
    queue.enqueue(test);
    queue.enqueue(test2);
    queue.enqueue(test3);
    queue.enqueue(test4);
    queue.enqueue(test5);

    // test for cerr and cout output
    queue.print(cout);
    queue.print(cerr);
}

// Tests that the front method throws the correct exception when trying to
// access
//  front element of an empty queue
void PQ_front_exception_test() {
    bool thrown = false;

    PassengerQueue queue;
    assert(queue.size() == 0);
    try {
        queue.front();
    } catch (const std::exception &e) {
        thrown = true;
        cerr << e.what();
    }
    // Ensure exception is thrown
    assert(thrown);
}

// Test the front() method and ensure that adding new passengers to the queue
// results in the front being held constant
void PQ_queueFront_test() {
    Passenger test = Passenger(1, 1, 2);
    Passenger test2 = Passenger(2, 1, 2);
    Passenger test3 = Passenger(3, 2, 1);
    Passenger test4 = Passenger(4, 3, 2);
    Passenger test5 = Passenger(5, 1, 4);

    PassengerQueue queue;
    queue.enqueue(test);
    queue.print(cout);
    // Add each passenger to queue
    queue.enqueue(test);
    assert(queue.front().getId() == test.getId());
    queue.enqueue(test2);
    queue.enqueue(test3);
    queue.enqueue(test4);
    queue.enqueue(test5);
    assert(queue.front().getId() == test.getId());
}

// Test adding Passengers to a queue with the enqueue
void PQ_enqueue_test() {
    Passenger test = Passenger(1, 1, 2);
    Passenger test2 = Passenger(2, 1, 2);
    Passenger test3 = Passenger(3, 2, 1);
    Passenger test4 = Passenger(4, 3, 2);
    Passenger test5 = Passenger(5, 1, 4);

    PassengerQueue queue;
    queue.enqueue(test);
    queue.enqueue(test2);
    queue.enqueue(test3);
    queue.enqueue(test4);
    queue.enqueue(test5);

    assert(queue.size() == 5);
    assert(queue.front().getId() == test.getId());
    queue.print(cerr);
}

// Test the case where one tries to dequeue from an empty queue.
void PQ_dequeue_exception_test() {
    bool thrown = false;

    PassengerQueue queue;
    assert(queue.size() == 0);
    try {
        queue.dequeue();
    } catch (const std::exception &e) {
        thrown = true;
        cerr << e.what();
    }
    // Ensure exception is thrown
    assert(thrown);
}

// Test the dequeue method from a full queue to empty.
void PQ_dequeue_test() {
    Passenger test = Passenger(1, 1, 2);
    Passenger test2 = Passenger(2, 1, 2);
    Passenger test3 = Passenger(3, 2, 1);
    Passenger test4 = Passenger(4, 3, 2);
    Passenger test5 = Passenger(5, 1, 4);

    PassengerQueue queue;
    queue.enqueue(test);
    queue.enqueue(test2);
    queue.enqueue(test3);
    queue.enqueue(test4);
    queue.enqueue(test5);

    assert(queue.size() == 5);

    queue.dequeue();
    assert(queue.front().getId() == 2);
    assert(queue.size() == 4);
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    assert(queue.front().getId() == 5);
    assert(queue.size() == 1);

    queue.dequeue();
    assert(queue.size() == 0);
}

// Tests the size method of PassengerQueue to ensure it works for empty,
// singleton and filled queues.
void PQ_size_test() {
    // Empty
    PassengerQueue queue;
    assert(queue.size() == 0);
    // Singleton
    queue.enqueue(Passenger(1, 1, 2));
    assert(queue.size() == 1);
    // Multiple
    queue.enqueue(Passenger(1, 1, 2));
    queue.enqueue(Passenger(1, 1, 2));
    queue.enqueue(Passenger(1, 1, 2));
    queue.enqueue(Passenger(1, 1, 2));
    queue.enqueue(Passenger(1, 1, 2));
    assert(queue.size() == 6);
}