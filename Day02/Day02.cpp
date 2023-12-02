// Day02.cpp : Source file for your target.
//

#include "Day02.h"
#include "Utils.h"

int main()
{
	std::regex re(R"(Game (\d+): (.+))");
	auto input = utils::ReadFormattedInput("input.txt", re);

	const int maxRed = 12;
	const int maxGreen = 13;
	const int maxBlue = 14;

	int sum = 0;

	std::regex redRe(R"((\d+) red)");
	std::regex greenRe(R"((\d+) green)");
	std::regex blueRe(R"((\d+) blue)");

	for (auto game : input)
	{
		int id = std::stoi(game[1]);
		bool valid = true;
		for (auto hand : utils::Tokenize(game[2], ';'))
		{
			std::smatch m;
			if (std::regex_search(hand, m, redRe) && std::stoi(m[1]) > maxRed)
			{
				valid = false;
			}
			else if (std::regex_search(hand, m, greenRe) && std::stoi(m[1]) > maxGreen)
			{
				valid = false;
			}
			else if(std::regex_search(hand, m, blueRe) && std::stoi(m[1]) > maxBlue)
			{
				valid = false;
			}
		}

		if (valid)
		{
			sum += id;
		}
	}

	std::cout << sum << "\n";

	//part 2

	sum = 0;

	for (auto game : input)
	{
		int minRed = 0;
		int minGreen = 0;
		int minBlue = 0;
		
		for (auto hand : utils::Tokenize(game[2], ';'))
		{
			std::smatch m;
			if (std::regex_search(hand, m, redRe) && std::stoi(m[1]) > minRed)
			{
				minRed = std::stoi(m[1]);
			}
			
			if (std::regex_search(hand, m, greenRe) && std::stoi(m[1]) > minGreen)
			{
				minGreen = std::stoi(m[1]);
			}
			
			if (std::regex_search(hand, m, blueRe) && std::stoi(m[1]) > minBlue)
			{
				minBlue = std::stoi(m[1]);
			}
		}

		sum += (minRed * minGreen * minBlue);
	}

	std::cout << sum << "\n";

	return 0;
}
