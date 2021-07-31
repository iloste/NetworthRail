#include "InputOutput.h"



int InputOutput::getUserInputInt()
{
	int x{};
	
	do
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}

		std::cin >> x;

	} while (!std::cin);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return x;
}


std::string InputOutput::getUserInputStr()
{
	std::string input{};

	do
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid input, please enter a whole number.\n";
		}

		std::getline(std::cin, input);

	} while (!std::cin);

	return input;
}


void InputOutput::TrainlineDoesNotExist(std::string lineName)
{
	std::cout << lineName << " line does not exist\n";
}


void InputOutput::TrainStationDoesNotExist(std::string stationName)
{
	std::cout << stationName << " station does not exist\n";
}



