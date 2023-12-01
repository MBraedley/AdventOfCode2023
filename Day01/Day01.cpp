// Day01.cpp : Source file for your target.
//

#include "Day01.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::int64_t sum = 0;
	for (auto line : input)
	{
		char d1 = line[line.find_first_of("0123456789")];
		char d2 = line[line.find_last_of("0123456789")];

		int v1 = (d1 - '0') * 10;
		int v2 = (d2 - '0');
		sum += v1 + v2;
	}

	std::cout << sum;
}
