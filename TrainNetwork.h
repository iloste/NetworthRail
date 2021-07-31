#pragma once
#include "TrainLine.h"
#include "TrainStation.h"
#include "StringManipulation.h"
#include "InputOutput.h"
#include <vector>
#include <fstream>
#include <ostream>
#include <memory>


class TrainNetwork
{
	std::vector<TrainLine> trainLines{};
	std::vector<TrainStation*> masterLine{};


	TrainLine* getTrainLine(std::string lineName);

	void removeStationFromMasterline(std::string stationName);

	// returns the index of the station in the master line or -1 if it doesn't exist
	int FindStationInMasterLine(int l, int r, std::string x);

public:
	TrainNetwork();
	~TrainNetwork();

	// TrainLines:

	// adds a new line to trainlines with the given name
	void createTrainLine(std::string name);

	// prints the names of the stations on the given line to the console
	void printLine(std::string lineName);

	// prints the name of all lines, each followed by their stations
	void printAllLines();

	bool checkTrainlineExists(std::string lineName);

	// removes each station from the trainline, then deletes the trainline
	bool deleteTrainLine(std::string lineName);




	// Train stations:

	// insert the new station after the previous station on the given trainline
	bool addStation(std::string lineName, std::string newStationName, std::string previousStationName);

	// adds the station to the start of the given line
	bool prependStation(std::string lineName, std::string stationName);

	// adds the station to the end of the given line
	bool appendStation(std::string lineName, std::string stationName);

	// move the given station after the previousStation on the given line. 
	// If previous station == "start", moves station to the start of the line
	void moveStationOnLine(std::string lineName, std::string stationToMove, std::string previousStationName);

	// prints all existing stations to the console
	void printAllStations();

	// changes the name of the station and repositions it in the masterline
	void changeStationName(std::string currentName, std::string newName);

	bool checkTrainStationExists(std::string stationName);

	// removes the given station from the given line. If the station isn't on any other lines, the station is deleted
	void removeStationFromLine(std::string lineName, std::string stationName);

	// removes the station from all lines it appears on, including the master line. Then deletes the station
	void deleteStation(std::string stationName);

	// returns a pointer to the given station. If it doesn't already exist, a new one is created and added to the master line
	TrainStation* getTrainStation(std::string stationName);


	// save/load

	// loads all of the trainlines and their stations from the given file
	void loadNetworkFromFile(std::string fileName);

	// saves the trainlines and their stations to the given file
	void saveToFile(std::string fileName);




	std::string cutString(std::string* str, char identifier);

	void InsertToMasterLine(TrainStation& station);


};

