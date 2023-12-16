// Day16.cpp : Source file for your target.
//

#include "Day16.h"
#include "Utils.h"

#include <cassert>
#include <future>

struct Tile
{
	Tile(char c) : type(c) {};

	char type = '.';
	utils::Connections lightOut;
};

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("input.txt");

	auto directLightBeam = [&](const utils::Pos& startPos, const utils::Connections& startDir) -> std::size_t
	{
		std::vector<std::vector<Tile>> grid;
		for (auto line : input)
		{
			std::vector<Tile> row;
			for (char c : line)
			{
				row.emplace_back(c);
			}
			grid.push_back(row);
		}

		std::queue<std::tuple<utils::Pos, utils::Connections>> lightBeams;
		lightBeams.push(std::make_tuple(startPos, startDir));

		utils::Connections north;
		north.north = true;

		utils::Connections south;
		south.south = true;

		utils::Connections east;
		east.east = true;

		utils::Connections west;
		west.west = true;

		while (!lightBeams.empty())
		{
			auto& [tilePos, lightDirection] = lightBeams.front();
			Tile& tile = grid[tilePos.Y][tilePos.X];

			auto sendLight = [&](const utils::Connections& dir)
				{
					assert(dir.Count() == 1);
					if ((tile.lightOut & dir) != dir)
					{
						tile.lightOut |= dir;
						for (auto nextPos : tilePos.GetNeighbours(dir, input))
						{
							lightBeams.push(std::make_tuple(nextPos, dir));
						}
					}
				};

			if (tile.type == '.')
			{
				sendLight(lightDirection);
			}
			else if (tile.type == '-')
			{
				if (lightDirection.east || lightDirection.west)
				{
					sendLight(lightDirection);
				}
				else
				{
					sendLight(east);
					sendLight(west);
				}
			}
			else if (tile.type == '|')
			{
				if (lightDirection.north || lightDirection.south)
				{
					sendLight(lightDirection);
				}
				else
				{
					sendLight(north);
					sendLight(south);
				}
			}
			else if (tile.type == '\\')
			{
				if (lightDirection.north)
				{
					sendLight(west);
				}
				else if (lightDirection.south)
				{
					sendLight(east);
				}
				else if (lightDirection.east)
				{
					sendLight(south);
				}
				else if (lightDirection.west)
				{
					sendLight(north);
				}
			}
			else if (tile.type == '/')
			{
				if (lightDirection.north)
				{
					sendLight(east);
				}
				else if (lightDirection.south)
				{
					sendLight(west);
				}
				else if (lightDirection.east)
				{
					sendLight(north);
				}
				else if (lightDirection.west)
				{
					sendLight(south);
				}
			}
			else
			{
				assert(false);
			}

			lightBeams.pop();
		}

		std::size_t energized = 0;
		for (const auto& row : grid)
		{
			for (const auto& tile : row)
			{
				if (tile.lightOut)
				{
					energized++;
				}
			}
		}

		return energized;
	};

	utils::Connections startDir;
	startDir.east = true;

	utils::Pos startPos(0, 0);

	std::size_t energized = directLightBeam(startPos, startDir);

	utils::PrintResult(energized, startTime);

	//part 2

	std::size_t maxEnergized = 0;
	std::size_t width = input[0].size();
	std::size_t height = input.size();

	utils::Connections north;
	north.north = true;

	utils::Connections south;
	south.south = true;

	utils::Connections east;
	east.east = true;

	utils::Connections west;
	west.west = true;

	std::vector<std::future<std::size_t>> futures;

	for (int x = 0; x < width; x++)
	{
		futures.push_back(std::async(std::launch::async, directLightBeam, utils::Pos(x, 0), south));
		futures.push_back(std::async(std::launch::async, directLightBeam, utils::Pos(x, height - 1), north));
	}

	for (int y = 0; y < height; y++)
	{
		futures.push_back(std::async(std::launch::async, directLightBeam, utils::Pos(0, y), east));
		futures.push_back(std::async(std::launch::async, directLightBeam, utils::Pos(width - 1, y), west));
	}

	for (auto& f : futures)
	{
		energized = f.get();
		if (energized > maxEnergized)
		{
			maxEnergized = energized;
		}
	}

	utils::PrintResult(maxEnergized, startTime);

	return 0;
}
