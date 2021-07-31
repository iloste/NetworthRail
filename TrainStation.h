#pragma once
#include "StringManipulation.h"
#include <iostream>
#include <vector>

class TrainLine;

class TrainStation
{
	std::string stationName{"Default"};
	std::vector<std::string> trainLines{};

public:
	TrainStation(std::string name);
	~TrainStation();

	// prints the station's name to the console.
	void printName();

	// Overwrites the station's current name with the new name
	void changeName(std::string newName);

	// Adds the trainline to the list of trainlines this station appears on
	void addStationToTrainLine(std::string newTrainLine);
	
	// Removes the trainline from the list of trainlines this station appears on
	void removeStationFromTrainLine(std::string trainLine);

	// prints to console all of the trainlines this station appears on
	void printLines();


	std::vector<std::string> getTrainLines() { return trainLines; }
	std::string getStationName() { return stationName; }



	//####################################################This overload may not be needed
	// prints station's name to the console with a comma at the end unless it is the last station.
	//void printName(int lineNumber);

};

