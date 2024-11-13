#########################################################
#            MetroSim Makefile                          #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

MetroSim: main.o MetroSim.o Train.o PassengerQueue.o Passenger.o 
	${CXX} ${LDFLAGS} -o MetroSim main.o MetroSim.o Train.o PassengerQueue.o Passenger.o

main.o: main.cpp MetroSim.h Train.h PassengerQueue.h Passenger.h
	${CXX} ${CXXFLAGS} -c main.cpp

MetroSim.o: MetroSim.cpp MetroSim.h Train.h PassengerQueue.h Passenger.h
	${CXX} ${CXXFLAGS} -c MetroSim.cpp

Train.o: Train.cpp Train.h PassengerQueue.h Passenger.h
	${CXX} ${CXXFLAGS} -c Train.cpp

PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	${CXX} ${CXXFLAGS} -c PassengerQueue.cpp

Passenger.o: Passenger.cpp Passenger.h
	${CXX} ${CXXFLAGS} -c Passenger.cpp

unit_test: unit_test_driver.o PassengerQueue.o Passenger.o Train.o MetroSim.o
	${CXX} ${CXXFLAGS} unit_test_driver.o Passenger.o PassengerQueue.o Train.o MetroSim.o

clean: 
	rm MetroSim *.o *~ a.out
