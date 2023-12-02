// Utils.h : Header file for your target.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <filesystem>
#include <fstream>

namespace utils
{
	std::vector<std::string> ReadInput(const std::filesystem::path& input);

	std::vector<std::vector<std::string>> ReadFormattedInput(const std::filesystem::path& input, const std::regex& format);

	std::vector<std::string> Tokenize(std::string str, char delim);
}