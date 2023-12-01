// Day01.cpp : Source file for your target.
//

#include "Day01.h"
#include "Utils.h"

#include <map>
#include <cassert>

int main()
{
	auto input = utils::ReadInput( "input.txt" );

	std::int64_t sum = 0;
	for ( auto line : input )
	{
		char d1 = line[line.find_first_of( "123456789" )];
		char d2 = line[line.find_last_of( "123456789" )];

		int v1 = (d1 - '0') * 10;
		int v2 = (d2 - '0');
		sum += v1 + v2;
	}

	std::cout << sum << "\n";

	//part 2

	std::regex re( R"(([1-9]|one|two|three|four|five|six|seven|eight|nine))" );
	std::map<std::string, int> lookup =
	{
		{"1", 1},
		{"2", 2},
		{"3", 3},
		{"4", 4},
		{"5", 5},
		{"6", 6},
		{"7", 7},
		{"8", 8},
		{"9", 9},
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9}
	};

	std::regex sanitizer( R"((on|tw|thre|fiv|eigh|nin)(e|o|t))" );

	sum = 0;
	for ( auto line : input )
	{
		auto sanitizedLine = std::regex_replace( line, sanitizer, "$1$2$2" );
		std::sregex_token_iterator iter( sanitizedLine.begin(), sanitizedLine.end(), re );

		std::vector<std::string> m(iter, std::sregex_token_iterator());

		int v1 = lookup[*m.begin()] * 10;
		int v2 = lookup[*m.rbegin()];

		sum += v1 + v2;
	}

	std::cout << sum << "\n";
}
