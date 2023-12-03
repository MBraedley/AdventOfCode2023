// Utils.h : Header file for your target.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <filesystem>
#include <fstream>
#include <set>

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

		std::set<Pos> GetNeighbours(const std::vector<std::string>& map);

		std::strong_ordering operator<=>(const Pos& rhs) const
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
	};
}

utils::Pos operator+(const utils::Pos& lhs, const utils::Pos& rhs);
