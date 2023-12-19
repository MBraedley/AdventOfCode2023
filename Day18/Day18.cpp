// Day18.cpp : Source file for your target.
//

#include "Day18.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::regex re(R"((R|L|U|D) (\d+) \(#([0-9a-f]{5})([0-9a-f])\))");
	auto input = utils::ReadFormattedInput("input.txt", re);

	int minX = 0;
	int minY = 0;
	int maxX = 0;
	int maxY = 0;

	std::set<utils::Pos> trench;
	utils::Pos p(0, 0);
	trench.insert(p);

	utils::Pos l(1, 0);
	utils::Pos r(-1, 0);
	utils::Pos u(0, -1);
	utils::Pos d(0, 1);

	std::vector<utils::Pos> trench2;
	utils::Pos p2(0, 0);
	trench2.push_back(p2);
	std::size_t perim = 0;

	for (auto m : input)
	{
		char dir = m[1][0];
		int dist = std::stoi(m[2]);

		for (int i = 0; i < dist; i++)
		{
			switch (dir)
			{
			case 'R':
				p = p + r;
				break;
			case 'L':
				p = p + l;
				break;
			case 'U':
				p = p + u;
				break;
			case 'D':
				p = p + d;
				break;
			default:
				assert(false);
				break;
			}
			trench.insert(p);

			if (p.X < minX)
			{
				minX = p.X;
			}

			if (p.Y < minY)
			{
				minY = p.Y;
			}

			if (p.X > maxX)
			{
				maxX = p.X;
			}

			if (p.Y > maxY)
			{
				maxY = p.Y;
			}
		}

		int dist2 = std::stoi(m[3], nullptr, 16);
		switch (m[4][0])
		{
		case '0': //R
			p2 = p2 + utils::Pos(dist2, 0);
			break;
		case '1': //D
			p2 = p2 + utils::Pos(0, dist2);
			break;
		case '2': //L
			p2 = p2 + utils::Pos(-dist2, 0);
			break;
		case '3': //U
			p2 = p2 + utils::Pos(0, -dist2);
			break;
		default:
			assert(false);
			break;
		}

		perim += dist2;
		trench2.push_back(p2);
	}

	std::queue<utils::Pos> fillQueue;
	p = *trench.begin() + utils::Pos(1, 1);
	fillQueue.push(p);

	assert(!trench.contains(p));
	trench.insert(p);

	while (!fillQueue.empty())
	{
		for (auto neighbour : fillQueue.front().GetUnboundedNeighbours(false))
		{
			if (!trench.contains(neighbour))
			{
				trench.insert(neighbour);
				fillQueue.push(neighbour);
			}
		}
		fillQueue.pop();
	}

	utils::PrintResult(trench.size(), startTime);

	//part 2

	assert(trench2.front() == trench2.back());

	std::int64_t size = 0;
	for (std::size_t i = 1; i < trench2.size(); i++)
	{
		std::int64_t x1 = trench2[i - 1].X;
		std::int64_t x2 = trench2[i].X;
		std::int64_t y1 = trench2[i - 1].Y;
		std::int64_t y2 = trench2[i].Y;
		size += x1 * y2 - x2 * y1;
	}

	assert(size % 2 == 0);
	utils::PrintResult((size + perim) / 2 + 1, startTime);

	return 0;
}
