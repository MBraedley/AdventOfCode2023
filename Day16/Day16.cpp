// Day16.cpp : Source file for your target.
//

#include "Day16.h"
#include "Utils.h"

#include <cassert>

struct Tile
{
	Tile(char c) : type(c) {};

	char type = '.';
	utils::Connections lightOut;
};

int main()
{
	auto input = utils::ReadInput("input.txt");

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
	utils::Connections start;
	start.east = true;
	lightBeams.push(std::make_tuple(utils::Pos(0, 0), start));

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

		auto sendLight = [&]( const utils::Connections& dir)
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

	std::cout << energized << "\n";

	return 0;
}
