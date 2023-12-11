// Utils.h : Header file for your target.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <filesystem>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>

namespace utils
{
	std::vector<std::string> ReadInput(const std::filesystem::path& input);

	std::vector<std::vector<std::string>> ReadFormattedInput(const std::filesystem::path& input, const std::regex& format);

	std::vector<std::string> Tokenize(std::string str, char delim);

	class Pos
	{
	public:
		Pos(int x, int y) :
			X(x), Y(y)
		{}

		int X;
		int Y;

		std::set<Pos> GetNeighbours(const std::vector<std::string>& map, bool includeDiagonals = true);
		int GetManDistance(const Pos& other);

		std::strong_ordering operator<=>(const utils::Pos& rhs) const
		{
			if (X == rhs.X)
			{
				return Y <=> rhs.Y;
			}
			else
			{
				return X <=> rhs.X;
			}
		}

		bool operator==(const utils::Pos& rhs) const
		{
			return X == rhs.X && Y == rhs.Y;
		}

		bool operator!=(const utils::Pos& rhs) const
		{
			return !(*this == rhs);
		}
	};
}

utils::Pos operator+(const utils::Pos& lhs, const utils::Pos& rhs);
utils::Pos operator-(const utils::Pos& lhs, const utils::Pos& rhs);
