/*
 *  MetroSim.h
 *  Harry Lynch
 *  9/24/2024
 *
 *  Interface for MetroSim class.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include "Train.h"
#include <fstream>
#include <vector>
class MetroSim {

  public:
    MetroSim(std::string stationFile, std::string outputFile,
             std::string commandFile);
    ~MetroSim();

    void beginSimulation();

  private:
    // Station definition
    struct Station {
        PassengerQueue queue;
        int index;
        std::string name;
        // Constructor for PassengerQueue
        Station(PassengerQueue q, int idx, std::string n)
            : queue(q), index(idx), name(n) {}
    };
    // Class members
    Train train;
    std::vector<Station> stations;
    int passengerInd;
    std::ifstream commandStream;
    std::ofstream outputStream;

    // reads commmands
    void readCmd(std::istream &input);
    // command-related core functions
    void moveTrain();
    void pickUp(int station);
    void addPassenger(int arrival, int departure);
    void endSim();

    // pure helpers
    void printSim(std::ostream &other);
    void readStations(std::string stationFile);
    void logPassengers(std::ostream &output, PassengerQueue &exit);
    template <typename streamtype>
    void open_or_die(streamtype &stream, std::string filename);
};

#endif
