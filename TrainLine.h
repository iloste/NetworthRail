#pragma once
#include "TrainStation.h"
#include "StringManipulation.h"
#include <vector>
#include <string>

//class TrainStation;

class TrainLine
{
private:
	std::string lineName{ "Default" };
	std::vector<TrainStation*> trainStations{};

public:

	TrainLine(std::string name);
	~TrainLine();

	// prints to console all the names of the stations on the trainline
	void printStations();

	// adds the given station to the end of the line
	void appendStation(TrainStation& newStation);

	// adds the given station to the beginning of the line
	void prependStation(TrainStation& newStation);

	// adds the newStation at the index after the previousStation
	void addStation(TrainStation& newStation, std::string previousStationName);

	// removes the given station from the trainline
	void removeStation(TrainStation& trainStation);

	// moves the "movingStation" to the position after the "previousStation"
	// if "previousStation" == "start" it moves the station to the start of the line 
	void moveStation(TrainStation& stationToMove, std::string previousStationName);


	std::vector<TrainStation*>* getStations() { return &trainStations; }
	std::string getName() { return lineName; }


};

