// Day06.cpp : Source file for your target.
//

#include "Day06.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto input = utils::ReadInput( "input.txt" );

	auto times = utils::Tokenize( input[0], ' ' );
	auto dists = utils::Tokenize( input[1], ' ' );

	assert( times.size() == dists.size() );

	std::vector<std::uint32_t> wins;

	for ( std::size_t i = 1; i < times.size(); i++ )
	{
		std::uint32_t win = 0;
		int time = std::stoi( times[i] );
		int dist = std::stoi( dists[i] );

		//brute forcing because it's probably going to be fast enough
		for ( int t = 0; t <= time; t++ )
		{
			int d = (time - t) * t;
			if ( d > dist )
			{
				win++;
			}
		}
		wins.push_back( win );
	}

	int product = std::accumulate( wins.begin(), wins.end(), 1, std::multiplies<int>() );

	std::cout << product << "\n";

	return 0;
}
