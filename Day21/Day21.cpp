// Day21.cpp : Source file for your target.
//

#include "Day21.h"
#include "Utils.h"

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("input.txt");

	utils::Pos startPos(0, 0);
	for (std::size_t i = 0; i < input.size(); i++)
	{
		if (auto pos = input[i].find('S'); pos != input[i].npos)
		{
			startPos.X = pos;
			startPos.Y = i;
			break;
		}
	}

	std::map<utils::Pos, std::size_t> stepsTaken;
	std::queue<std::pair<utils::Pos, std::size_t>> floodQ;

	floodQ.emplace(startPos, 0);
	stepsTaken.emplace(startPos, 0);
	while (!floodQ.empty())
	{
		auto [pos, steps] = floodQ.front();

		for (auto nextPos : pos.GetNeighbours(input, false))
		{
			if (!stepsTaken.contains(nextPos) && input[nextPos.Y][nextPos.X] == '.' && steps < 64)
			{
				floodQ.emplace(nextPos, steps + 1);
				stepsTaken.emplace(nextPos, steps + 1);
			}
		}

		floodQ.pop();
	}

	auto sum = std::count_if(stepsTaken.begin(), stepsTaken.end(), [&](const std::pair<utils::Pos, std::size_t>& val) -> bool
		{
			return val.second <= 64 && val.second % 2 == 0;
		});

	utils::PrintResult(sum, startTime);

	return 0;
}
