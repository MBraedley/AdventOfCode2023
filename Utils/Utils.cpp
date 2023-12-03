// Utils.cpp : Source file for your target.
//

#include "Utils.h"

#include <sstream>

std::vector<std::string> utils::ReadInput(const std::filesystem::path& input)
{
	std::vector<std::string> ret;
	std::ifstream istrm(input);
	std::string line;
	while ( std::getline(istrm, line))
	{
		ret.push_back(line);
	}

	return ret;
}

std::vector<std::vector<std::string>> utils::ReadFormattedInput(const std::filesystem::path& input, const std::regex& format)
{
	std::vector<std::vector<std::string>> ret;
	std::ifstream istrm(input);
	std::string line;
	while (std::getline(istrm, line))
	{
		std::smatch m;
		std::regex_match(line, m, format);
		ret.emplace_back(m.begin(), m.end());
	}

	return ret;
}

std::vector<std::string> utils::Tokenize(std::string str, char delim)
{
	std::stringstream sstrm(str);
	std::vector<std::string> ret;

	std::string token;
	while (std::getline(sstrm, token, delim))
	{
		ret.push_back(token);
	}

	return ret;
}

std::set<utils::Pos> utils::Pos::GetNeighbours(const std::vector<std::string>& map)
{
	std::set<Pos> ret;
	auto addPoint = [&](const Pos& p)
		{
			if (p.X >= 0 && p.X < map[0].size() &&
				p.Y >= 0 && p.Y < map.size())
			{
				ret.insert(p);
			}
		};

	addPoint(*this + Pos(-1, -1));
	addPoint(*this + Pos(0, -1));
	addPoint(*this + Pos(1, -1));
	addPoint(*this + Pos(-1, 0));
	addPoint(*this + Pos(1, 0));
	addPoint(*this + Pos(-1, 1));
	addPoint(*this + Pos(0, 1));
	addPoint(*this + Pos(1, 1));

	return ret;
}

utils::Pos operator+(const utils::Pos& lhs, const utils::Pos& rhs)
{
	utils::Pos ret(lhs.X + rhs.X, lhs.Y + rhs.Y);
	return ret;
}
