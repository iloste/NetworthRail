#include "TrainLine.h"
#include "TrainNetwork.h"
#include "InputOutput.h"
#include "StringManipulation.h"
#include <iostream>


enum class TrainTasks
{
	defaultTask,
	newTrainLine,
	deleteTrainLine,
	newTrainStation,
	removeTrainStation,
	deleteTrainStation,
	printTrainLine,
	printAllTrainLines,
	printMasterLine,
	printLinesOfTrainStation,
	saveAndExit,
	changeStationName,
	moveStation,
};


void gameLoop(TrainNetwork& trainNetwork);
void printMenu();

bool executeTask(TrainTasks task, TrainNetwork& trainNetwork);
void addNewTrainLine(TrainNetwork& trainNetwork);
void deleteTrainLine(TrainNetwork& trainNetwork);
void addNewTrainStation(TrainNetwork& trainNetwork);
void removeTrainStationFromLine(TrainNetwork& trainNetwork);
void deleteTrainStation(TrainNetwork& trainNetwork);
void printAllTrainLines(TrainNetwork& trainNetwork);
void printTrainLine(TrainNetwork& trainNetwork);
void printMasterLine(TrainNetwork& trainNetwork);
void printTrainLinesOfTrainStation(TrainNetwork& trainNetwork);
void saveAndExit(TrainNetwork& trainNetwork);
void changeStationName(TrainNetwork& trainNetwork);
void moveStationOnLine(TrainNetwork& trainNetwork);


int main()
{
	TrainNetwork trainNetwork{};
	trainNetwork.loadNetworkFromFile("Train Network.txt");
	gameLoop(trainNetwork);
	return 0;
}


void gameLoop(TrainNetwork& trainNetwork)
{
	bool running{ true };
	int userInput{};

	while (running)
	{
		printMenu();
		userInput = InputOutput::getUserInputInt();
		TrainTasks task = static_cast<TrainTasks>(userInput);
		running = executeTask(task, trainNetwork);
	}
}


void printMenu()
{
	std::cout << "Please select an option:\n\n"
		<< "1: Create a new trainline.\n"
		<< "2: Delete an existing trainline.\n"
		<< "3: Add a train station to a trainline.\n"
		<< "4: Remove a train station from a trainline.\n"
		<< "5: Delete a train station.\n"
		<< "6: Print a trainline.\n"
		<< "7: Print all trainlines.\n"
		<< "8: Print all train stations.\n"
		<< "9: Print all trainlines a train station is on.\n"
		<< "10: Save and exit.\n"
		<< "11: Change the name of a train station.\n"
		<< "12: Move a train station on a trainline.\n"
		<< '\n';
}


bool executeTask(TrainTasks task, TrainNetwork& trainNetwork)
{
	switch (task)
	{
	case TrainTasks::newTrainLine:
		addNewTrainLine(trainNetwork);
		return true;
	case TrainTasks::deleteTrainLine:
		deleteTrainLine(trainNetwork);
		return true;
	case TrainTasks::newTrainStation:
		addNewTrainStation(trainNetwork);
		return true;
	case TrainTasks::removeTrainStation:
		removeTrainStationFromLine(trainNetwork);
		return true;
	case TrainTasks::deleteTrainStation:
		deleteTrainStation(trainNetwork);
		return true;
	case TrainTasks::printTrainLine:
		printTrainLine(trainNetwork);
		return true;
	case TrainTasks::printAllTrainLines:
		printAllTrainLines(trainNetwork);
		return true;
	case TrainTasks::printMasterLine:
		printMasterLine(trainNetwork);
		return true;
	case TrainTasks::printLinesOfTrainStation:
		printTrainLinesOfTrainStation(trainNetwork);
		return true;
	case TrainTasks::saveAndExit:
		saveAndExit(trainNetwork);
		return false;
	case TrainTasks::changeStationName:
		changeStationName(trainNetwork);
		return true;
	case TrainTasks::moveStation:
		moveStationOnLine(trainNetwork);
	default:
		return true;
	}

}


void addNewTrainLine(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the new trainline's name:\n";
	std::string name = InputOutput::getUserInputStr();
	trainNetwork.createTrainLine(name);
	std::cout << "Created trainline " << "'" << name << "'" << '\n';
}


void deleteTrainLine(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the trainline to be deleted:\n";
	std::string lineName = InputOutput::getUserInputStr();
	trainNetwork.deleteTrainLine(lineName);
}


void addNewTrainStation(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the train station:\n";
	std::string stationName = InputOutput::getUserInputStr();

	std::cout << "Please enter the name of the trainline " << stationName << " station will appear on:\n";
	std::string lineName = InputOutput::getUserInputStr();

	std::cout << "Please enter start, end, or the name of the station that " << stationName << " will appear after.\n";
	std::string previousStationName = InputOutput::getUserInputStr();

	if (StringManipulation::toLower(previousStationName) == "start")
	{
		trainNetwork.prependStation(lineName, stationName);
	}
	else if (StringManipulation::toLower(previousStationName) == "end")
	{
		trainNetwork.appendStation(lineName, stationName);
	}
	else
	{
		trainNetwork.addStation(lineName, stationName, previousStationName);
	}

	trainNetwork.printLine(lineName);
}

void removeTrainStationFromLine(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the train station:\n";
	std::string stationName = InputOutput::getUserInputStr();

	std::cout << "Please enter the name of the trainline " << stationName << " station will be removed from:\n";
	std::string lineName = InputOutput::getUserInputStr();

	trainNetwork.removeStationFromLine(lineName, stationName);
	trainNetwork.printLine(lineName);
}


void deleteTrainStation(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the train station that you want to delete:\n";
	std::string stationName = InputOutput::getUserInputStr();
	trainNetwork.deleteStation(stationName);
}


void printTrainLine(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the trainline you want to print:\n";
	std::string trainLine = InputOutput::getUserInputStr();

	if (trainNetwork.checkTrainlineExists(trainLine))
	{
		trainNetwork.printLine(trainLine);
	}
	else
	{
		InputOutput::TrainlineDoesNotExist(trainLine);
	}
}

void printTrainLinesOfTrainStation(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the train station:\n";
	std::string stationName = InputOutput::getUserInputStr();

	if (trainNetwork.checkTrainStationExists(stationName))
	{
		trainNetwork.getTrainStation(stationName)->printLines();
	}
	else
	{
		InputOutput::TrainStationDoesNotExist(stationName);
	}
}


void saveAndExit(TrainNetwork& trainNetwork)
{
	trainNetwork.saveToFile("Train Network.txt");
}


void printMasterLine(TrainNetwork& trainNetwork)
{
	trainNetwork.printAllStations();
}

void printAllTrainLines(TrainNetwork& trainNetwork)
{
	trainNetwork.printAllLines();
}


void changeStationName(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the train station you want to change:\n";
	std::string currentName = InputOutput::getUserInputStr();

	std::cout << "Please enter the new name:\n";
	std::string newName = InputOutput::getUserInputStr();

	trainNetwork.changeStationName(currentName, newName);
}


void moveStationOnLine(TrainNetwork& trainNetwork)
{
	std::cout << "Please enter the name of the trainline the station is on:\n";
	std::string lineName = InputOutput::getUserInputStr();

	std::cout << "Please enter the name of the train station you want to move:\n";
	std::string stationToMove = InputOutput::getUserInputStr();

	std::cout << "Please enter start, end, or the name of the station that " << stationToMove << " will appear after.\n";
	std::string previousStationName = InputOutput::getUserInputStr();

	trainNetwork.moveStationOnLine(lineName, stationToMove, previousStationName);
}
