// Day10.cpp : Source file for your target.
//

#include "Day10.h"
#include "Utils.h"

#include <cassert>

struct Conections
{
	bool north = false;
	bool south = false;
	bool east = false;
	bool west = false;
};

using QueueItem = std::tuple<utils::Pos, Conections, std::uint32_t>;
auto operator<=>(const QueueItem& lhs, const QueueItem& rhs)
{
	return std::get<std::uint32_t>(rhs) <=> std::get<std::uint32_t>(lhs);
}

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::map<utils::Pos, Conections> pipes;
	utils::Pos start(0, 0);

	for (std::size_t y = 0; y < input.size(); y++)
	{
		for (std::size_t x = 0; x < input[y].size(); x++)
		{
			Conections c;
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

	Conections startConnections;
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

	std::priority_queue<QueueItem> bfsQueue;
	std::map<utils::Pos, std::uint32_t> stepsTaken;
	stepsTaken.emplace(start, 0);

	std::uint32_t maxSteps = 0;

	bfsQueue.push(std::make_tuple(start, startConnections, 0));
	while (!bfsQueue.empty())
	{
		auto [pos, cons, steps] = bfsQueue.top();
		bfsQueue.pop();

		if (steps > maxSteps)
		{
			maxSteps = steps;
		}

		if (cons.north)
		{
			assert(pipes.contains(pos + northDir));
			if (!stepsTaken.contains(pos + northDir) || stepsTaken[pos + northDir] > steps + 1)
			{
				stepsTaken[pos + northDir] = steps + 1;
				bfsQueue.push(std::make_tuple(pos + northDir, pipes[pos + northDir], steps + 1));
			}
		}

		if (cons.south)
		{
			assert(pipes.contains(pos + southDir));
			if (!stepsTaken.contains(pos + southDir) || stepsTaken[pos + southDir] > steps + 1)
			{
				stepsTaken[pos + southDir] = steps + 1;
				bfsQueue.push(std::make_tuple(pos + southDir, pipes[pos + southDir], steps + 1));
			}
		}

		if (cons.east)
		{
			assert(pipes.contains(pos + eastDir));
			if (!stepsTaken.contains(pos + eastDir) || stepsTaken[pos + eastDir] > steps + 1)
			{
				stepsTaken[pos + eastDir] = steps + 1;
				bfsQueue.push(std::make_tuple(pos + eastDir, pipes[pos + eastDir], steps + 1));
			}
		}

		if (cons.west)
		{
			assert(pipes.contains(pos + westDir));
			if (!stepsTaken.contains(pos + westDir) || stepsTaken[pos + westDir] > steps + 1)
			{
				stepsTaken[pos + westDir] = steps + 1;
				bfsQueue.push(std::make_tuple(pos + westDir, pipes[pos + westDir], steps + 1));
			}
		}
	}

	std::cout << maxSteps << "\n";

	return 0;
}
