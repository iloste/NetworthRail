#include "TrainLine.h"


TrainLine::TrainLine(std::string name)
{
	lineName = name;
}


TrainLine::~TrainLine()
{

}


void TrainLine::appendStation(TrainStation& newStation)
{
	trainStations.push_back(&newStation);
	newStation.addStationToTrainLine(lineName);
}


void TrainLine::prependStation(TrainStation& newStation)
{
	trainStations.insert(trainStations.begin(), &newStation);
	newStation.addStationToTrainLine(lineName);
}


void TrainLine::addStation(TrainStation& newStation, std::string previousStationName)
{
	for (size_t i = 0; i < trainStations.size(); i++)
	{
		if (StringManipulation::compareStrings(trainStations[i]->getStationName(), previousStationName))
		{
			auto itPos = trainStations.begin() + i + 1;
			trainStations.insert(itPos, &newStation);
			newStation.addStationToTrainLine(lineName);

			break;
		}
	}
}


void TrainLine::printStations()
{
	std::cout << lineName << " line: ";

	for (size_t i = 0; i < trainStations.size(); i++)
	{
		trainStations[i]->printName();

		// -1 so it doesn't print a comma after the last station
		if (i < trainStations.size() - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << '\n';
		}
	}
}


void TrainLine::removeStation(TrainStation& trainStation)
{
	for (size_t i = 0; i < trainStations.size(); i++)
	{
		if (trainStations[i]->getStationName() == trainStation.getStationName())
		{
			auto itPos = trainStations.begin() + i;
			trainStations[i]->removeStationFromTrainLine(lineName);
			trainStations.erase(itPos);
			return;
		}
	}
}


void TrainLine::moveStation(TrainStation& stationToMove, std::string previousStationName)
{
	removeStation(stationToMove);

	if (StringManipulation::toLower(previousStationName) == "start")
	{
		prependStation(stationToMove);
	}
	else if (StringManipulation::toLower(previousStationName) == "end")
	{
		appendStation(stationToMove);
	}
	else
	{
		addStation(stationToMove, previousStationName);
	}

	printStations();
}
