// Day10.cpp : Source file for your target.
//

#include "Day10.h"
#include "Utils.h"

#include <tuple>
#include <cassert>

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::map<utils::Pos, utils::Connections> pipes;
	utils::Pos start(0, 0);

	for (std::size_t y = 0; y < input.size(); y++)
	{
		for (std::size_t x = 0; x < input[y].size(); x++)
		{
			utils::Connections c;
			switch (input[y][x])
			{
			case 'S':
				start.X = x;
				start.Y = y;
				break;
			case '|':
				c.north = true;
				c.south = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			case '-':
				c.east = true;
				c.west = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			case 'L':
				c.north = true;
				c.east = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			case 'J':
				c.north = true;
				c.west = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			case '7':
				c.west = true;
				c.south = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			case 'F':
				c.east = true;
				c.south = true;
				pipes.emplace(utils::Pos(x, y), c);
				break;
			default:
				break;
			}
		}
	}

	utils::Pos northDir(0, -1);
	utils::Pos southDir(0, 1);
	utils::Pos eastDir(1, 0);
	utils::Pos westDir(-1, 0);

	utils::Connections startConnections;
	int connectionCount = 0;
	if (pipes.contains(start + northDir) && pipes[start + northDir].south)
	{
		startConnections.north = true;
		connectionCount++;
	}

	if (pipes.contains(start + southDir) && pipes[start + southDir].north)
	{
		startConnections.south = true;
		connectionCount++;
	}

	if (pipes.contains(start + eastDir) && pipes[start + eastDir].west)
	{
		startConnections.east = true;
		connectionCount++;
	}

	if (pipes.contains(start + westDir) && pipes[start + westDir].east)
	{
		startConnections.west = true;
		connectionCount++;
	}

	pipes.emplace(start, startConnections);

	assert(connectionCount == 2);

	std::map<utils::Pos, utils::Connections> connectedPipes;
	connectedPipes.emplace(start, startConnections);

	std::queue<std::pair<utils::Pos, utils::Connections>> pipeQueue;

	pipeQueue.push({ start, startConnections });

	while (!pipeQueue.empty())
	{
		auto [pos, cons] = pipeQueue.front();
		pipeQueue.pop();

		if (cons.north)
		{
			assert(pipes.contains(pos + northDir));
			if (!connectedPipes.contains(pos + northDir))
			{
				pipeQueue.push(std::make_pair(pos + northDir, pipes[pos + northDir]));
				connectedPipes.emplace(pos + northDir, pipes[pos + northDir]);
			}
		}

		if (cons.south)
		{
			assert(pipes.contains(pos + southDir));
			if (!connectedPipes.contains(pos + southDir))
			{
				pipeQueue.push(std::make_pair(pos + southDir, pipes[pos + southDir]));
				connectedPipes.emplace(pos + southDir, pipes[pos + southDir]);
			}
		}

		if (cons.east)
		{
			assert(pipes.contains(pos + eastDir));
			if (!connectedPipes.contains(pos + eastDir) )
			{
				pipeQueue.push(std::make_pair(pos + eastDir, pipes[pos + eastDir]));
				connectedPipes.emplace(pos + eastDir, pipes[pos + eastDir]);
			}
		}

		if (cons.west)
		{
			assert(pipes.contains(pos + westDir));
			if (!connectedPipes.contains(pos + westDir))
			{
				pipeQueue.push(std::make_pair(pos + westDir, pipes[pos + westDir]));
				connectedPipes.emplace(pos + westDir, pipes[pos + westDir]);
			}
		}
	}

	std::cout << connectedPipes.size() / 2 << "\n";

	//part 2
	std::set<utils::Pos> insidePoints;

	//start with the point that is most west and most north (points with the smallest x and then smallest y), then work your way around clockwise

	auto tagInsidePipes = [&](const utils::Pos& previousPos, const utils::Pos& currentPos)
		{
			if ((previousPos + northDir) == currentPos)
			{
				if (!connectedPipes.contains(previousPos + eastDir))
				{
					insidePoints.insert(previousPos + eastDir);
				}

				if (!connectedPipes.contains(currentPos + eastDir))
				{
					insidePoints.insert(currentPos + eastDir);
				}
			}

			if ((previousPos + eastDir) == currentPos)
			{
				if (!connectedPipes.contains(previousPos + southDir))
				{
					insidePoints.insert(previousPos + southDir);
				}

				if (!connectedPipes.contains(currentPos + southDir))
				{
					insidePoints.insert(currentPos + southDir);
				}
			}

			if ((previousPos + southDir) == currentPos)
			{
				if (!connectedPipes.contains(previousPos + westDir))
				{
					insidePoints.insert(previousPos + westDir);
				}

				if (!connectedPipes.contains(currentPos + westDir))
				{
					insidePoints.insert(currentPos + westDir);
				}
			}

			if ((previousPos + westDir) == currentPos)
			{
				if (!connectedPipes.contains(previousPos + northDir))
				{
					insidePoints.insert(previousPos + northDir);
				}

				if (!connectedPipes.contains(currentPos + northDir))
				{
					insidePoints.insert(currentPos + northDir);
				}
			}
		};

	auto getNextPipe = [&](utils::Pos previousPos, utils::Pos currentPos)->utils::Pos
		{
			if (connectedPipes[currentPos].north && previousPos != currentPos + northDir)
			{
				return currentPos + northDir;
			}
			else if (connectedPipes[currentPos].east && previousPos != currentPos + eastDir)
			{
				return currentPos + eastDir;
			}
			else if(connectedPipes[currentPos].south && previousPos != currentPos + southDir)
			{
				return currentPos + southDir;
			}
			else if(connectedPipes[currentPos].west && previousPos != currentPos + westDir)
			{
				return currentPos + westDir;
			}
			else
			{
				throw std::exception("Lost in the pipes");
			}
		};

	start = connectedPipes.begin()->first;
	utils::Pos previousPos = start;
	utils::Pos currentPos = previousPos + eastDir;

	assert(connectedPipes.contains(currentPos));

	while (currentPos != start)
	{
		tagInsidePipes(previousPos, currentPos);
		previousPos = getNextPipe(previousPos, currentPos);
		std::swap(previousPos, currentPos);
	}

	std::deque<utils::Pos> floodedNest(insidePoints.begin(), insidePoints.end());

	while (!floodedNest.empty())
	{
		auto testPoint = floodedNest.front();
		floodedNest.pop_front();

		for (auto nextPoint : testPoint.GetNeighbours(input, false))
		{
			if (!insidePoints.contains(nextPoint) && !connectedPipes.contains(nextPoint))
			{
				floodedNest.push_back(nextPoint);
				insidePoints.insert(nextPoint);
			}
		}
	}

	std::cout << insidePoints.size() << "\n";

	return 0;
}
