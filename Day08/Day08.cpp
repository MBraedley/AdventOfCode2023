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
	std::uint32_t stepsTaken = 0;
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
	std::vector<std::string> endingLocations;

	for ( const auto& [key, value] : map )
	{
		if ( key.ends_with( "A" ) )
		{
			currentLocations.push_back( key );
		}

		if ( key.ends_with( "Z" ) )
		{
			endingLocations.push_back( key );
		}
	}

	std::sort( endingLocations.begin(), endingLocations.end() );
	stepsTaken = 0;
	std::vector<std::string> diff;

	do
	{
		char dir = directions[stepsTaken % directions.size()];
		std::vector<std::string> nextLocations;
		for ( auto pos : currentLocations )
		{
			if ( dir == 'L' )
			{
				nextLocations.push_back( map[pos].first );
			}
			else
			{
				nextLocations.push_back( map[pos].second );
			}
		}
		std::swap( currentLocations, nextLocations );
		std::sort( currentLocations.begin(), currentLocations.end() );
		diff.clear();
		std::set_difference( currentLocations.begin(), currentLocations.end(), endingLocations.begin(), endingLocations.end(), std::back_inserter( diff ) );

		stepsTaken++;
	} while ( !diff.empty() );

	std::cout << stepsTaken << "\n";

	return 0;
}
