// Day14.cpp : Source file for your target.
//

#include "Day14.h"
#include "Utils.h"

int main()
{
	auto startTime = std::chrono::system_clock::now();
	auto input = utils::ReadInput("input.txt");

	std::vector<std::pair<std::vector<std::string>, std::size_t>> history;

	auto CalcLoad = [&]() -> std::size_t
		{
			std::size_t load = 0;
			for (std::size_t y = 0; y < input.size(); y++)
			{
				for (std::size_t x = 0; x < input[y].size(); x++)
				{
					if (input[y][x] == 'O')
					{
						load += input.size() - y;
					}
				}
			}

			return load;
		};

	history.emplace_back(input, CalcLoad());

	std::size_t load = 0;

	for (std::size_t x = 0; x < input[0].size(); x++)
	{
		for (std::size_t y = 0; y < input.size(); y++)
		{
			if (input[y][x] == '.')
			{
				std::size_t offset = 0;
				while (y + offset < input.size() && input[y + offset][x] == '.')
				{
					offset++;
				}

				if (y + offset < input.size() && input[y + offset][x] == 'O')
				{
					input[y][x] = 'O';
					input[y + offset][x] = '.';
				}
			}

			if (input[y][x] == 'O')
			{
				load += input.size() - y;
			}
		}
	}

	utils::PrintResult(load, startTime);

	//part2


	auto RollNorth = [&]()
		{
			for (std::size_t x = 0; x < input[0].size(); x++)
			{
				for (std::size_t y = 0; y < input.size(); y++)
				{
					if (input[y][x] == '.')
					{
						std::size_t offset = 0;
						while (y + offset < input.size() && input[y + offset][x] == '.')
						{
							offset++;
						}

						if (y + offset < input.size() && input[y + offset][x] == 'O')
						{
							input[y][x] = 'O';
							input[y + offset][x] = '.';
						}
					}
				}
			}
		};

	auto RollWest = [&]()
		{
			for (std::size_t y = 0; y < input.size(); y++)
			{
				for (std::size_t x = 0; x < input[y].size(); x++)
				{
					if (input[y][x] == '.')
					{
						std::size_t offset = 0;
						while (x + offset < input.size() && input[y][x + offset] == '.')
						{
							offset++;
						}

						if (x + offset < input.size() && input[y][x + offset] == 'O')
						{
							input[y][x] = 'O';
							input[y][x + offset] = '.';
						}
					}
				}
			}
		};

	auto RollSouth = [&]()
		{
			for (std::size_t x = 0; x < input[0].size(); x++)
			{
				for (std::size_t i = 0; i < input.size(); i++)
				{
					std::size_t y = input.size() - i - 1;
					if (input[y][x] == '.')
					{
						std::size_t offset = 0;
						while (offset <= y && input[y - offset][x] == '.')
						{
							offset++;
						}

						if (offset <= y && input[y - offset][x] == 'O')
						{
							input[y][x] = 'O';
							input[y - offset][x] = '.';
						}
					}
				}
			}
		};

	auto RollEast = [&]()
		{
			for (std::size_t y = 0; y < input.size(); y++)
			{
				for (std::size_t i = 0; i < input[y].size(); i++)
				{
					std::size_t x = input[y].size() - i - 1;
					if (input[y][x] == '.')
					{
						std::size_t offset = 0;
						while (offset <= x && input[y][x - offset] == '.')
						{
							offset++;
						}

						if (offset <= x && input[y][x - offset] == 'O')
						{
							input[y][x] = 'O';
							input[y][x - offset] = '.';
						}
					}
				}
			}
		};

	auto ToString = [&]() -> std::string
		{
			std::stringstream sstrm;
			for (const auto& line : input)
			{
				sstrm << line;
			}
			return sstrm.str();
		};

	std::size_t cycleNum = 0;
	std::size_t cycleStart = 0;
	std::map<std::string, std::size_t> cycles;
	bool cycleFound = false;
	while (!cycleFound)
	{
		RollNorth();
		RollWest();
		RollSouth();
		RollEast();

		history.emplace_back(input, CalcLoad());

		auto [iter, inserted] = cycles.emplace(ToString(), ++cycleNum);
		cycleFound = !inserted;
		if (cycleFound)
		{
			cycleStart = iter->second;
		}
	}

	std::size_t endCycle = (1000000000 - cycleStart) % (cycleNum - cycleStart) + cycleStart;

	load = history[endCycle].second;

	utils::PrintResult(load, startTime);

	return 0;
}
