#include "TrainNetwork.h"


TrainNetwork::TrainNetwork()
{

}

TrainNetwork::~TrainNetwork()
{

}


TrainLine* TrainNetwork::getTrainLine(std::string lineName)
{
	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			return &trainLines[i];
		}
	}

	InputOutput::TrainlineDoesNotExist(lineName);
	return nullptr;
}


void TrainNetwork::removeStationFromMasterline(std::string stationName)
{
	int index = FindStationInMasterLine(0, masterLine.size() - 1, stationName);

	auto itPos = masterLine.begin() + index;
	masterLine.erase(itPos);
}


void TrainNetwork::createTrainLine(std::string lineName)
{
	if (checkTrainlineExists(lineName))
	{
		std::cout << lineName << " line already exists!\n";
		return;
	}

	trainLines.push_back(*(new TrainLine(lineName)));
}


void TrainNetwork::printLine(std::string lineName)
{
	if (!checkTrainlineExists(lineName))
	{
		return;
	}

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			trainLines[i].printStations();
		}
	}

	std::cout << '\n';
}


void TrainNetwork::printAllLines()
{
	for (size_t i = 0; i < trainLines.size(); i++)
	{
		printLine(trainLines[i].getName());
	}
}


bool TrainNetwork::checkTrainlineExists(std::string lineName)
{

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			return true;
		}
	}

	InputOutput::TrainlineDoesNotExist(lineName);
	return false;
}


bool TrainNetwork::deleteTrainLine(std::string lineName)
{
	if (checkTrainlineExists(lineName))
	{
		TrainLine* trainLine = getTrainLine(lineName);
		std::vector<TrainStation*>* trainStations = trainLine->getStations();

		while (trainStations->size() > 0)
		{
			trainLine->removeStation(*(*trainStations)[0]);
		}

		for (size_t i = 0; i < trainLines.size(); i++)
		{
			if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
			{
				auto itPos = trainLines.begin() + i;
				trainLines.erase(itPos);
			}
		}

		std::cout << lineName << " line successfully deleted\n";
		return true;
	}
	else
	{
		std::cout << lineName << " line does not exist \n";
		return false;
	}
}


bool TrainNetwork::addStation(std::string lineName, std::string newStationName, std::string previousStationName)
{
	if (!checkTrainlineExists(lineName))
	{
		return false;
	}
	if (!checkTrainStationExists(previousStationName))
	{
		return false;
	}

	TrainStation& trainStation = *getTrainStation(newStationName);

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			trainLines[i].addStation(trainStation, previousStationName);
			std::cout << newStationName << " station added to " << lineName << " line\n";
			return true;
		}
	}

	return false;
}


bool TrainNetwork::prependStation(std::string lineName, std::string stationName)
{
	if (!checkTrainlineExists(lineName))
	{
		return false;
	}

	TrainStation& trainStation = *getTrainStation(stationName);

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			trainLines[i].prependStation(trainStation);
			std::cout << stationName << " station added to " << lineName << " line.\n";
			return true;
		}
	}

	return false;
}


bool TrainNetwork::appendStation(std::string lineName, std::string stationName)
{
	if (!checkTrainlineExists(lineName))
	{
		return false;
	}

	TrainStation& trainStation = *getTrainStation(stationName);

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		if (StringManipulation::compareStrings(trainLines[i].getName(), lineName))
		{
			trainLines[i].appendStation(trainStation);
			std::cout << stationName << " station added to " << lineName << " line\n";
			return true;
		}
	}

	return false;
}


void TrainNetwork::moveStationOnLine(std::string lineName, std::string stationToMove, std::string previousStationName)
{
	if (!checkTrainlineExists(lineName))
	{
		return;
	}
	else if (!checkTrainStationExists(stationToMove))
	{
		return;
	}
	else if (!checkTrainStationExists(previousStationName))
	{
		return;
	}
	else if (stationToMove == previousStationName)
	{
		std::cout << "Station names can't be the same.\n";
		return;
	}

	getTrainLine(lineName)->moveStation(*getTrainStation(stationToMove), previousStationName);
}


void TrainNetwork::printAllStations()
{
	std::cout << '\n' << "All stations: ";

	for (size_t i = 0; i < masterLine.size(); i++)
	{
		masterLine[i]->printName();

		// -1 so it doesn't print a comma after the last station
		if (i < masterLine.size() - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << '\n';
		}
	}
}


void TrainNetwork::changeStationName(std::string currentName, std::string newName)
{
	if (checkTrainStationExists(currentName))
	{
		TrainStation* station = getTrainStation(currentName);
		removeStationFromMasterline(currentName);
		station->changeName(newName);
		InsertToMasterLine(*station);
	}
}


bool TrainNetwork::checkTrainStationExists(std::string stationName)
{
	for (size_t i = 0; i < masterLine.size(); i++)
	{
		if (StringManipulation::compareStrings(masterLine[i]->getStationName(), stationName))
		{
			return true;
		}
	}

	InputOutput::TrainStationDoesNotExist(stationName);
	return false;
}


void TrainNetwork::removeStationFromLine(std::string lineName, std::string stationName)
{

	if (!checkTrainlineExists(lineName))
	{
		return;
	}
	if (!checkTrainStationExists(stationName))
	{
		return;
	}

	TrainLine* trainLine{ getTrainLine(lineName) };
	TrainStation* trainStation{ getTrainStation(stationName) };
	trainLine->removeStation(*trainStation);
	std::cout << stationName << " station removed from " << lineName << " line.\n";
}


void TrainNetwork::deleteStation(std::string stationName)
{
	if (!checkTrainStationExists(stationName))
	{
		return;
	}

	TrainStation* station = getTrainStation(stationName);

	for (size_t i = 0; i < station->getTrainLines().size(); i++)
	{
		removeStationFromLine(station->getTrainLines()[i], stationName);
		i--;
	}

	removeStationFromMasterline(stationName);
}


TrainStation* TrainNetwork::getTrainStation(std::string stationName)
{

	if (masterLine.size() > 0)
	{
		int index = FindStationInMasterLine(0, masterLine.size() - 1, stationName);

		if (index >= 0)
		{
			return masterLine[index];
		}
	}

	TrainStation* trainStation = new TrainStation(stationName);
	InsertToMasterLine(*trainStation);
	return trainStation;
}



void TrainNetwork::loadNetworkFromFile(std::string fileName)
{
	std::ifstream fileStream{};
	fileStream.open(fileName);

	if (fileStream.fail())
	{
		std::cout << "No saved data./n'";
		return;
	}

	std::string line{};
	std::string lineName{};
	std::string stationName{};

	while (std::getline(fileStream, line))
	{
		lineName = cutString(&line, ':');
		createTrainLine(lineName);

		do
		{
			stationName = cutString(&line, '#');
			if (stationName != "")
			{
				appendStation(lineName, stationName);
			}

		} while (line != "");
	}

	fileStream.close();
}


void TrainNetwork::saveToFile(std::string fileName)
{
	std::ofstream fileStream{};
	fileStream.open(fileName);

	for (size_t i = 0; i < trainLines.size(); i++)
	{
		fileStream << trainLines[i].getName() << ":";

		std::vector<TrainStation*>* trainStations = trainLines[i].getStations();

		for (size_t i = 0; i < trainStations->size(); i++)
		{
			fileStream << " " << (*trainStations)[i]->getStationName() << " #";
		}

		fileStream << '\n';
	}

	std::cout << "Saved.\n";
	fileStream.close();
}


std::string TrainNetwork::cutString(std::string* str, char identifier)
{
	int index = str->find(identifier);

	if (index == -1)
	{
		return "";
	}
	else
	{
		std::string toReturn = str->substr(0, index);
		StringManipulation::trim(toReturn);
		str->erase(0, index + 1);
		return toReturn;
	}
}


void TrainNetwork::InsertToMasterLine(TrainStation& station)
{

	for (size_t i = 0; i < masterLine.size(); i++)
	{
		if (station.getStationName() < masterLine[i]->getStationName())
		{
			auto itPos = masterLine.begin() + i;
			masterLine.insert(itPos, &station);
			return;
		}
	}

	masterLine.push_back(&station);
}


int TrainNetwork::FindStationInMasterLine(int left, int right, std::string x)
{
	if (right >= left)
	{
		int middle = left + (right - left) / 2;

		if (StringManipulation::compareStrings(masterLine[middle]->getStationName(), x))
		{
			return middle;
		}
		else if (masterLine[middle]->getStationName() > x)
		{
			return FindStationInMasterLine(left, middle - 1, x);
		}

		return FindStationInMasterLine(middle + 1, right, x);
	}

	return -1;
}