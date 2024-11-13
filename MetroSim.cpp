/*
 *  MetroSim.cpp
 *  Harry Lynch
 *  9/24/2024
 *
 *  Implementation of MetroSim driver class.
 *
 */

#include "MetroSim.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
 * name:      MetroSim( )
 * purpose:   Constructor to initialize the simulation.
 * arguments: filenames of stations, output location, and optional cmds
 * returns:   nothing
 * effects:   reads the stationFile into the stations member, checks for a cmd
 *            file, initializes the train with the number of stations, and sets
 *            the passengerIndex to 1.
 */
MetroSim::MetroSim(string stationFile, string outputFile, string commandFile) {
    this->passengerInd = 1;
    readStations(stationFile);

    if (commandFile != "") {
        open_or_die(this->commandStream, commandFile);
    }

    this->train = Train(this->stations.size());
    open_or_die(this->outputStream, outputFile);
}

/*
 * name:      ~MetroSim( )
 * purpose:   destructor for MetroSim object
 * arguments: none
 * returns:   none
 * effects:   closes output streams opened on instantiation
 */
MetroSim::~MetroSim() {
    this->commandStream.close();
    this->outputStream.close();
}

/*
 * name:      beginSimulation( )
 * purpose:   Core simulation prompt loop, takes input and executes cmd
 * arguments: none
 * returns:   none
 * effects:   takes in command and begins the flow of handling user reqs.
 */
void MetroSim::beginSimulation() {
    this->printSim(cout);
    cout << "Command? ";
    // ternary operator to decide which stream to readin from
    if (this->commandStream.is_open()) {
        if (not this->commandStream.eof())
            readCmd(commandStream);
        else {
            endSim();
        }
    } else {
        readCmd(cin);
    }
}

/*
 * name:      readCmd( )
 * purpose:   take in prompt from a variable input stream (file or cin)
 * arguments: reference to stream from which to take input
 * returns:   nothing
 * effects:   reads in command and parses it for next action
 */
void MetroSim::readCmd(istream &input) {
    char cmd, subcmd;
    int arr, dep;

    input >> cmd;
    // if trying to add passenger, take in arrival and departure ints
    if (cmd == 'p') {
        input >> arr >> dep;
        this->addPassenger(arr, dep);
    }
    // if using one of the metro cmds, determine the subcmd and call correct fn
    else if (cmd == 'm') {
        input >> subcmd;
        if (subcmd == 'm')
            this->moveTrain();
        else if (subcmd == 'f')
            this->endSim();
        // else{
        //     invalidPrompt(cmd);
        // }
    } else {
        this->endSim();
    }
}

/*
* name:      moveTrain( )
* purpose:   execute the steps involved in the m m command including picking up
             passengers, moving the train to the next station, and dropping off
             and logging passengers at the next station.
* arguments: none
* returns:   none
* effects:   moves train forward by one, removes passengers departing at next
             station.
*/
void MetroSim::moveTrain() {
    // pickup passengers, move train location, drop passegners off at new
    // station
    int currStation = this->train.getCurrentStation();
    this->pickUp(currStation);
    // Move train to next station, account for wrapping first
    if (currStation == (this->stations.size() - 1)) {
        currStation = 0;
    } else {
        currStation++;
    }
    this->train.setCurrentStation(currStation);
    // dropoff passengers
    PassengerQueue exiting = this->train.dropOff();
    logPassengers(this->outputStream, exiting);
    // restart loop
    this->beginSimulation();
}

/*
* name:      addPassenger( )
* purpose:   execute p {arr} {dep} cmd
* arguments: arrival station index and departure station index
* returns:   none
* effects:   adds a new passenger at their arrival station queue and restarts
             loop.
*/
void MetroSim::addPassenger(int arrival, int departure) {
    Station &arrivalStation = this->stations.at(arrival);
    arrivalStation.queue.enqueue(Passenger(passengerInd, arrival, departure));
    this->passengerInd++;
    this->beginSimulation();
}

/*
* name:      logPassengers( )
* purpose:   write passenger activity to output file
* arguments: output stream(file stream) to write to, and the queue of exiting
             passengers
* returns:   none
* effects:   writes formatted lines to an output file
*/
void MetroSim::logPassengers(std::ostream &output, PassengerQueue &exit) {
    while (exit.size() != 0) {
        stringstream ss;
        ss << "Passenger " << exit.front().getId() << " left train at station "
           << this->stations.at(this->train.getCurrentStation()).name << '\n';
        output << ss.str();
        exit.dequeue();
    }
}

/*
 * name:      pickUp( )
 * purpose:   helper function for moveTrain() that picks up passengers from stat
 * arguments: station # to grab passengers from
 * returns:   none
 * effects:   empties passengers from a station into a train queue
 */
void MetroSim::pickUp(int station) {
    Station &currStation = this->stations.at(station);
    while (currStation.queue.size() != 0) {
        train.boardPassenger(currStation.queue.front());
        currStation.queue.dequeue();
    }
}

/*
 * name:      printSim( )
 * purpose:   function that presents the full simulation to the end user
 * arguments: output stream to print to
 * returns:   nothing
 * effects:   prints formatted output to stream of user's choice
 */
void MetroSim::printSim(ostream &output) {
    output << "Passengers on the train: ";
    this->train.print(output);
    output << endl;
    for (int i = 0; i < this->stations.size(); i++) {
        string placeholder = "       ";
        Station &currStation = this->stations.at(i);
        if (this->train.getCurrentStation() == i) {
            placeholder = "TRAIN: ";
        }
        output << placeholder << "[" << i << "] " << currStation.name << " "
               << "{";
        currStation.queue.print(output);
        output << "}" << endl;
    }
}

/*
* name:      readStations( )
* purpose:   helper function in constructor to read station file into vector of
             stations.
* arguments: name of station file
* returns:   nothing
* effects:   reads into station class member
*/
void MetroSim::readStations(string stationFile) {
    ifstream instream;
    open_or_die(instream, stationFile);
    int i = 0;
    string stationInput = "";
    while (getline(instream, stationInput)) {
        this->stations.push_back(Station(PassengerQueue(), i, stationInput));
        i++;
    }
}

/*
 * name:      endSim( )
 * purpose:   command function that executes the m m command.
 * arguments: none
 * returns:   none
 * effects:   doesn't call the beginSimulation() function so the loop ends
 */
void MetroSim::endSim() {
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
* name:      open_or_die( )
* purpose:   check that a given file is valid and can be opened, exit program
             otherwise
* arguments: streamtype to open and filename to open with.
* returns:   none
* effects:   if file can't open, exit program, else continue
*/
template <typename streamtype>
void MetroSim::open_or_die(streamtype &stream, string filename) {
    stream.open(filename);
    if (not stream.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
}