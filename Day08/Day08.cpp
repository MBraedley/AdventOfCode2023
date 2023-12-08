// Day08.cpp : Source file for your target.
//

#include "Day08.h"
#include "Utils.h"

int main()
{
	auto input = utils::ReadInput( "input.txt" );

	std::string directions = input[0];

	input.erase( input.begin(), input.begin() + 2 );

	std::map<std::string, std::pair<std::string, std::string>> map;
	std::regex re( R"(([A-Z]+) = \(([A-Z]+), ([A-Z]+)\))" );

	for ( auto line : input )
	{
		std::smatch m;
		std::regex_match( line, m, re );
		map.emplace( m[1], std::make_pair( m[2], m[3] ) );
	}

	std::string currentLocation = "AAA";
	std::uint64_t stepsTaken = 0;
	while ( currentLocation != "ZZZ" )
	{
		char dir = directions[stepsTaken % directions.size()];
		if ( dir == 'L' )
		{
			currentLocation = map[currentLocation].first;
		}
		else
		{
			currentLocation = map[currentLocation].second;
		}
		stepsTaken++;
	}

	std::cout << stepsTaken << "\n";

	//part2

	std::vector<std::string> currentLocations;
	std::set<std::string> endingLocations;

	for ( const auto& [key, value] : map )
	{
		if ( key.ends_with( "A" ) )
		{
			currentLocations.push_back( key );
		}

		if ( key.ends_with( "Z" ) )
		{
			endingLocations.emplace( key );
		}
	}

	std::vector<std::uint32_t> stepsForPath;
	for ( auto loc : currentLocations )
	{
		stepsTaken = 0;
		while ( !endingLocations.contains( loc ) )
		{
			char dir = directions[stepsTaken % directions.size()];
			if ( dir == 'L' )
			{
				loc = map[loc].first;
			}
			else
			{
				loc = map[loc].second;
			}
			stepsTaken++;
		}
		stepsForPath.push_back( stepsTaken );
	}

	stepsTaken = 1;
	for ( std::uint64_t n : stepsForPath )
	{
		stepsTaken = std::lcm( stepsTaken, n );
	}

	std::cout << stepsTaken << "\n";

	return 0;
}
