#include "TrainStation.h"


TrainStation::TrainStation(std::string name)
{
	stationName = name;
}


TrainStation::~TrainStation()
{

}


void TrainStation::printName()
{
	std::cout << stationName;
}


void TrainStation::changeName(std::string newName)
{
	stationName = newName;
}


void TrainStation::addStationToTrainLine(std::string newTrainLine)
{
	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i], newTrainLine))
		{
			std::cout << stationName << " station is already on that line." << '\n';
			return;
		}
	}

	trainLines.push_back(newTrainLine);
}


void TrainStation::removeStationFromTrainLine(std::string trainLine)
{
	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i], trainLine))
		{
			auto itPos = trainLines.begin() + i;
			trainLines.erase(itPos);
			return;
		}
	}
}


void TrainStation::printLines()
{
	std::cout << stationName << " station appears on the following lines: ";

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		std::cout << trainLines[i] << ", ";
	}
}


