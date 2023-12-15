// Day15.cpp : Source file for your target.
//

#include "Day15.h"
#include "Utils.h"

#include <list>
#include <unordered_map>

using Label = std::string;
using LabeledLens = std::pair<Label, std::uint8_t>;
using Box = std::list<LabeledLens>;
using Boxes = std::unordered_map<std::uint8_t, Box>;

auto operator<=>( const LabeledLens& lhs, const LabeledLens& rhs )
{
	return lhs.first <=> rhs.first;
}

auto operator<=>( const Label& lhs, const LabeledLens& rhs )
{
	return lhs <=> rhs.first;
}

auto operator<=>( const LabeledLens& lhs, const Label& rhs )
{
	return lhs.first <=> rhs;
}

bool operator==( const LabeledLens& lhs, const LabeledLens& rhs )
{
	return lhs.first == rhs.first;
}

bool operator==( const LabeledLens& lhs, const Label& rhs )
{
	return lhs.first == rhs;
}

bool operator==( const Label& lhs, const LabeledLens& rhs )
{
	return lhs == rhs.first;
}

int main()
{
	auto input = utils::ReadInput( "input.txt" );
	input = utils::Tokenize( input[0], ',' );

	std::uint32_t sum = 0;

	auto hasher = []( std::string str ) -> std::uint8_t
		{
			std::uint8_t hash = 0;
			for ( char c : str )
			{
				std::uint8_t v = static_cast<std::uint8_t>(c);
				hash += v;
				hash *= 17;
			}

			return hash;
		};

	for ( auto str : input )
	{
		sum += hasher( str );
	}

	std::cout << sum << "\n";

	//part 2

	Boxes boxes;
	for ( auto str : input )
	{
		if ( auto pos = str.find( '-' ); pos != str.npos )
		{
			str = str.substr( 0, pos );
			auto boxId = hasher( str );

			if ( auto iter = std::find_if( boxes[boxId].begin(), boxes[boxId].end(), [&]( const LabeledLens& ll ) { return ll == str; } ); iter != boxes[boxId].end() )
			{
				boxes[boxId].erase( iter );
			}
		}
		else if ( auto pos = str.find( '=' ); pos != str.npos )
		{
			auto instruction = utils::Tokenize( str, '=' );
			auto boxId = hasher( instruction[0] );
			std::uint8_t lens = std::stoul( instruction[1] );

			LabeledLens ll = std::make_pair( instruction[0], lens );

			if ( auto iter = std::find_if( boxes[boxId].begin(), boxes[boxId].end(), [&]( const LabeledLens& lhs ) { return lhs == ll; } ); iter != boxes[boxId].end() )
			{
				*iter = ll;
			}
			else
			{
				boxes[boxId].push_back( ll );
			}
		}
	}

	std::uint64_t focalPower = 0;
	for ( std::size_t boxId = 0; boxId < boxes.size(); boxId++ )
	{
		std::size_t lensId = 0;
		for ( auto ll : boxes[boxId] )
		{
			focalPower += (boxId + 1) * (++lensId) * ll.second;
			std::cout << (boxId + 1) << " * " << lensId << " * " << static_cast<int>( ll.second ) << "\n";
		}
	}

	std::cout << focalPower << "\n";

	return 0;
}
