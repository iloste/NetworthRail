#pragma once
#include <string>

class StringManipulation
{
public:

	static std::string toLower(std::string str);
	static bool compareStrings(std::string a, std::string b);

	// trim from start (in place)
	static inline void leftTrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
			{
				return !std::isspace(ch);
			}));
	}

	// trim from end (in place)
	static inline void rightTrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
			{
				return !std::isspace(ch);
			}).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string& s)
	{
		leftTrim(s);
		rightTrim(s);
	}

	

};

