// Day03.cpp : Source file for your target.
//

#include "Day03.h"
#include "Utils.h"

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::set<utils::Pos> symbols;

	std::string nonSymbols = "0123456789.";

	for (int y = 0; y < input.size(); y++)
	{
		for (int x = 0; x < input[y].size(); x++)
		{
			if (nonSymbols.find(input[y][x]) == nonSymbols.npos)
			{
				symbols.emplace(x, y);
			}
		}
	}

	auto isNum = [&](const utils::Pos& point) -> bool
		{
			char c = input[point.Y][point.X];
			return c >= '0' && c <= '9';
		};

	auto isGear = [&](const utils::Pos& point) -> bool
		{
			return input[point.Y][point.X] == '*';
		};

	auto getStartPos = [&](const utils::Pos& point)->utils::Pos
		{
			utils::Pos ret = point;
			while (ret.X > 0 && isNum( ret + utils::Pos(-1, 0)))
			{
				ret.X -= 1;
			}

			return ret;
		};

	std::set<utils::Pos> validNumPoints;
	std::map<utils::Pos, std::set<utils::Pos>> gears;

	for (auto point : symbols)
	{
		for (auto n : point.GetNeighbours(input))
		{
			if (isNum(n))
			{
				validNumPoints.insert(getStartPos(n));

				if (isGear(point))
				{
					gears[point].insert(getStartPos(n));
				}
			}
		}
	}

	auto getNum = [&](const utils::Pos& n) -> int
		{
			std::string line = input[n.Y];
			std::string numStr = line.substr(n.X, line.find_first_not_of("0123456789", n.X) - n.X);
			return std::stoi(numStr);
		};

	//part 1
	int sum = 0;

	for (auto n : validNumPoints)
	{
		sum += getNum(n);
	}

	std::cout << sum << "\n";

	//part 2
	sum = 0;
	for (auto& [gear, nums] : gears)
	{
		if (nums.size() == 2)
		{
			int ratio = 1;
			for (auto n : nums)
			{
				ratio *= getNum(n);
			}
			sum += ratio;
		}
	}

	std::cout << sum << "\n";
	
	return 0;
}
