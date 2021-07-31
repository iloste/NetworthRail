#pragma once
#include <iostream>
#include <string>

class InputOutput
{

public:

	// gets user input as an int. Prints error and tries again if input is invalid
	static int getUserInputInt();

	// gets user input as an int. Prints error and tries again if input is invalid
	static std::string getUserInputStr();

	static void TrainlineDoesNotExist(std::string lineName);
	static void TrainStationDoesNotExist(std::string stationName);
};

