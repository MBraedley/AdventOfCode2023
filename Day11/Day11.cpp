// Day11.cpp : Source file for your target.
//

#include "Day11.h"
#include "Utils.h"

int main()
{
	auto input = utils::ReadInput( "input.txt" );

	//for ( auto line : input )
	//{
	//	std::cout << line << "\n";
	//}
	//std::cout << "\n";

	std::vector<bool> expandVert( input.size(), true );
	std::vector<bool> expandHorz( input[0].size(), true );

	for ( std::size_t y = 0; y < input.size(); y++ )
	{
		for ( std::size_t x = 0; x < input[y].size(); x++ )
		{
			if ( input[y][x] == '#' )
			{
				expandVert[y] = false;
				expandHorz[x] = false;
			}
		}
	}

	for ( std::size_t i = 1; i <= expandVert.size(); i++ )
	{
		auto y = expandVert.size() - i;
		if ( expandVert[y] )
		{
			input.insert( input.begin() + y, input[y] );
		}
	}

	for ( std::size_t i = 1; i <= expandVert.size(); i++ )
	{
		auto x = expandHorz.size() - i;
		if ( expandHorz[x] )
		{
			for ( std::string& line : input )
			{
				line.insert( x, 1, '.' );
			}
		}
	}

	//for ( auto line : input )
	//{
	//	std::cout << line << "\n";
	//}
	//std::cout << "\n";

	std::vector<utils::Pos> galaxies;

	for ( std::size_t y = 0; y < input.size(); y++ )
	{
		for ( std::size_t x = 0; x < input[y].size(); x++ )
		{
			if ( input[y][x] == '#' )
			{
				galaxies.emplace_back( x, y );
			}
		}
	}

	std::uint32_t sum = 0;
	for ( std::size_t i = 0; i < galaxies.size() - 1; i++ )
	{
		for ( std::size_t j = i + 1; j < galaxies.size(); j++ )
		{
			auto dist = galaxies[i].GetManDistance( galaxies[j] );
			sum += dist;
			//std::cout << i + 1 << "->" << j + 1 << " " << dist << "\n";
		}
	}

	std::cout << sum << "\n";

	return 0;
}
