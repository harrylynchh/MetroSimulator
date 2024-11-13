
Metro Simulator\
Harry Lynch  9/24/24

**Summary**:
---------------
To create a simulation of the Green Line of the T where the user can add
passengers and move the train from station to station with the passengers
boarding and departing at their respective stations.

**Compile and Run**:
---------------
- Compile using
  
            make MetroSim

- run executable with ./MetroSim stationsFile outputFile [commands]
- NOTE: For included files, use:
  
            ./MetroSim stations.txt output.txt

**Commands**:
---------------
p [arrival] [departure]: Insert a passenger into the simulation at a given\
station index ([arrival]) where that passenger will depart at the [departure] index.

m m: Move the train up a station, handling the passengers in transit.

m f: end the program.

**Provided Files**:
---------------

main.cpp: Main driver file for the simulation, responsible for creating MetroSim\
          obj.
          
MetroSim.cpp: Simulation implementation that is a compilation of the below\
classes and handles the core logic of the sim.

MetroSim.h:  Interface for the MetroSim class.

Train.cpp: Implementation of the Train object of the simulation, allows for 
picking up passengers, dropping them off, and moving train.

Train.h: Interface for Train.cpp

PassengerQueue.cpp: Implementation of a queue that holds type Passenger

PassengerQueue.h: Interface for PassengerQueue.cpp

Passenger.cpp: Implementation of Passenger Class, holds an ID and passenger's
travel plans.

Passenger.h: Interface for Passenger.cpp

stations.txt: an example file containing a list of stations.

output.txt: a given output file to pass to the program, will collect a log of
passenger motion

Makefile: File to build the program.
