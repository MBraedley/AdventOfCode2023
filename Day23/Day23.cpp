// Day23.cpp : Source file for your target.
//

#include "Day23.h"
#include "Utils.h"

#include <stack>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();
	auto input = utils::ReadInput("input.txt");

	std::stack<utils::Pos> dfs;
	dfs.emplace(1, 0);

	std::stack<std::set<utils::Pos>> paths;
	paths.emplace();

	std::size_t longestPath = 0;
	utils::Pos end(input[0].size() - 2, input.size() - 1);

	auto TakeSteps = [&](bool part2)
		{
			utils::Pos p = dfs.top();
			dfs.pop();

			int neighbours = 0;
			paths.top().insert(p);

			if (auto np = p.GetNeighbour(utils::Direction::East, input);
				np.has_value() && !paths.top().contains(*np)
				&& (part2 ? input[np->Y][np->X] != '#' : (input[np->Y][np->X] == '.' || input[np->Y][np->X] == '>')))
			{
				dfs.push(*np);
				neighbours++;
			}

			if (auto np = p.GetNeighbour(utils::Direction::South, input);
				np.has_value() && !paths.top().contains(*np)
				&& (part2 ? input[np->Y][np->X] != '#' : (input[np->Y][np->X] == '.' || input[np->Y][np->X] == 'v')))
			{
				if (np.value() == end)
				{
					if (paths.top().size() >= longestPath)
					{
						longestPath = paths.top().size();
						paths.pop();
						neighbours++;
					}
				}
				else
				{
					dfs.push(*np);
					neighbours++;
				}
			}
			if (auto np = p.GetNeighbour(utils::Direction::West, input);
				np.has_value() && !paths.top().contains(*np)
				&& (part2 ? input[np->Y][np->X] != '#' : (input[np->Y][np->X] == '.' || input[np->Y][np->X] == '<')))
			{
				dfs.push(*np);
				neighbours++;
			}

			if (auto np = p.GetNeighbour(utils::Direction::North, input);
				np.has_value() && !paths.top().contains(*np)
				&& (part2 ? input[np->Y][np->X] != '#' : (input[np->Y][np->X] == '.' || input[np->Y][np->X] == '^')))
			{
				dfs.push(*np);
				neighbours++;
			}

			if (neighbours == 0)
			{
				paths.pop();
			}

			while (neighbours > 1)
			{
				paths.push(paths.top());
				neighbours--;
			}
		};

	while (!dfs.empty())
	{
		TakeSteps(false);
	}

	utils::PrintResult(longestPath, startTime);

	longestPath = 0;
	assert(paths.empty());
	paths.emplace();
	dfs.emplace(1, 0);

	while (!dfs.empty())
	{
		TakeSteps(true);
	}

	utils::PrintResult(longestPath, startTime);

	return 0;
}
