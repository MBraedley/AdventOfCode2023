// Utils.cpp : Source file for your target.
//

#include "Utils.h"

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
