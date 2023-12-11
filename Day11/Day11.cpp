// Day11.cpp : Source file for your target.
//

#include "Day11.h"
#include "Utils.h"

int main()
{
	auto input = utils::ReadInput( "input.txt" );

	std::vector<bool> expandVert( input.size(), true );
	std::vector<bool> expandHorz( input[0].size(), true );

	std::vector<utils::Pos> galaxies;

	for ( std::size_t y = 0; y < input.size(); y++ )
	{
		for ( std::size_t x = 0; x < input[y].size(); x++ )
		{
			if ( input[y][x] == '#' )
			{
				expandVert[y] = false;
				expandHorz[x] = false;
				galaxies.emplace_back( x, y );
			}
		}
	}

	auto getExpansion = [&]( const utils::Pos& lhs, const utils::Pos& rhs, bool part2 ) -> std::uint64_t
		{
			std::uint64_t expFactor = part2 ? 999999 : 1;
			std::uint64_t expansion = 0;
			for ( int x = std::min( lhs.X, rhs.X ) + 1; x < std::max( lhs.X, rhs.X ); x++ )
			{
				if ( expandHorz[x] )
				{
					expansion += expFactor;
				}
			}

			for ( int y = std::min( lhs.Y, rhs.Y ) + 1; y < std::max( lhs.Y, rhs.Y ); y++ )
			{
				if ( expandVert[y] )
				{
					expansion += expFactor;
				}
			}

			return expansion;
		};

	std::uint32_t sum1 = 0;
	std::uint64_t sum2 = 0;
	for ( std::size_t i = 0; i < galaxies.size() - 1; i++ )
	{
		for ( std::size_t j = i + 1; j < galaxies.size(); j++ )
		{
			sum1 += galaxies[i].GetManDistance( galaxies[j] ) + getExpansion(galaxies[i], galaxies[j], false);
			sum2 += galaxies[i].GetManDistance( galaxies[j] ) + getExpansion(galaxies[i], galaxies[j], true);
		}
	}

	std::cout << sum1 << "\n";
	std::cout << sum2 << "\n";

	return 0;
}
