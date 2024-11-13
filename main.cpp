/*
 *  main.cpp
 *  Harry Lynch
 *  9/24/2024
 *
 *  Main driver function for the MetroSim.
 *
 */

#include <iostream>
#include <string>

#include "MetroSim.h"

using namespace std;

/*
 * name:      main( )
 * purpose:   check user-given parameters and instantiate and begin MetroSim
 * arguments: number of args and array of args
 * returns:   0
 * effects:   Builds and begins MetroSim
 */
int main(int argc, char *argv[]) {
    string cmdFile = "";
    // Check if the proper # of args provided
    if (argc < 3 or argc > 4) {
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile] \n";
        exit(EXIT_FAILURE);
    }
    // If the user provides a command file, save the value to pass to the Sim
    if (argc == 4) {
        cmdFile = argv[3];
    }
    // Construct the sim w/ station file, output file, and cmd file
    // The sim will determine validity of all provided files
    MetroSim metroSim = MetroSim(argv[1], argv[2], cmdFile);
    // Begin prompt loop
    metroSim.beginSimulation();
    return 0;
}
