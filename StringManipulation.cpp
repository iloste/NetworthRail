#include "StringManipulation.h"


std::string StringManipulation::toLower(std::string str)
{
	std::string strLower{};

	for (size_t i = 0; i < str.size(); i++)
	{
		strLower.push_back(std::tolower(str[i]));
	}

	return strLower;
}


bool StringManipulation::compareStrings(std::string a, std::string b)
{
	if (toLower(a) == toLower(b))
	{
		return true;
	}
	else
	{
		return false;
	}
}
