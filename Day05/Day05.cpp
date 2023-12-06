// Day05.cpp : Source file for your target.
//

#include "Day05.h"
#include "Utils.h"

#include <optional>
#include <cassert>

struct MappedRanges
{
	std::vector<std::pair<std::uint64_t, std::uint64_t>> m_MappedDests;
	std::vector<std::pair<std::uint64_t, std::uint64_t>> m_UnmappedDests;
};

class Mapping
{
public:
	Mapping( std::uint64_t source, std::uint64_t dest, std::uint64_t range ) :
		m_Source( source ), m_Dest( dest ), m_Range( range )
	{}

	~Mapping() = default;

	std::optional<std::uint64_t> GetOutput( std::uint64_t input ) const
	{
		std::optional<std::uint64_t> ret = std::nullopt;

		if ( input >= m_Source && input < m_Source + m_Range )
		{
			ret = m_Dest + (input - m_Source);
		}

		return ret;
	}

	MappedRanges GetOutput( const MappedRanges& input ) const
	{
		MappedRanges ret;
		ret.m_MappedDests = input.m_MappedDests;

		for ( const auto& in : input.m_UnmappedDests )
		{
			auto start = GetOutput( in.first );
			auto end = GetOutput( in.first + in.second - 1 );

			if ( start.has_value() && end.has_value() )
			{
				ret.m_MappedDests.emplace_back( *start, in.second );
			}
			else if ( start.has_value() )
			{
				assert( *start >= m_Dest );
				assert( m_Range > (*start - m_Dest) );

				auto destRange = m_Range - (*start - m_Dest);
				ret.m_MappedDests.emplace_back( *start, destRange );

				assert( in.second >= destRange );
				if ( in.second > destRange )
				{
					ret.m_UnmappedDests.emplace_back( in.first + destRange, in.second - destRange );
				}
			}
			else if ( end.has_value() )
			{
				//assert( *end >= m_Dest );
				auto destRange = *end - m_Dest + 1;
				ret.m_MappedDests.emplace_back( m_Dest, destRange );

				assert( in.second >= destRange );
				if ( in.second > destRange )
				{
					ret.m_UnmappedDests.emplace_back( in.first, in.second - destRange );
				}
			}
			else //if ( !start.has_value() && !end.has_value() )
			{
				if ( in.first < m_Source && in.first + in.second > m_Source + m_Range )
				{
					auto firstRange = m_Source - in.first;
					ret.m_UnmappedDests.emplace_back( in.first, firstRange );
					ret.m_MappedDests.emplace_back( m_Dest, m_Range );
					ret.m_UnmappedDests.emplace_back( m_Source + m_Range, in.second - (firstRange + m_Range) );
				}
				else
				{
					ret.m_UnmappedDests.push_back( in );
				}
			}
		}

		return ret;
	}

private:
	std::uint64_t m_Source;
	std::uint64_t m_Dest;
	std::uint64_t m_Range;
};

class MappingSet
{
public:
	MappingSet() = default;
	~MappingSet() = default;

	void AddMapping( std::uint64_t source, std::uint64_t dest, std::uint64_t range )
	{
		m_Mappings.emplace_back( source, dest, range );
	}

	std::uint64_t GetOutput( std::uint64_t input ) const
	{
		for ( const auto& mapping : m_Mappings )
		{
			if ( auto out = mapping.GetOutput( input ); out.has_value() )
			{
				return out.value();
			}
		}

		return input;
	}

	MappedRanges GetOutput( const MappedRanges& input ) const
	{
		MappedRanges ret = input;
		for ( const auto& mapping : m_Mappings )
		{
			ret = mapping.GetOutput( ret );
		}

		return ret;
	}

private:
	std::vector<Mapping> m_Mappings;
};


int main()
{
	std::vector<MappingSet> mappings;

	auto input = utils::ReadInput("input.txt");
	std::deque<std::string> queue(input.begin(), input.end());

	std::string seedsStr = queue.front();//save this for later
	queue.pop_front();
	queue.pop_front();

	queue.push_back("");

	std::uint64_t source, dest, range;

	while (!queue.empty())
	{
		queue.pop_front();//name of mapping
		MappingSet mapSet;
		while (!queue.front().empty())
		{
			std::stringstream sstrm(queue.front());
			sstrm >> dest >> source >> range;
			mapSet.AddMapping(source, dest, range);
			queue.pop_front();
		}
		queue.pop_front();

		mappings.push_back(mapSet);
	}

	seedsStr = seedsStr.substr(seedsStr.find_first_of(':') + 1);

	std::uint64_t seed;
	std::uint64_t closestLocation = std::numeric_limits<std::uint64_t>::max();
	std::stringstream sstrm1(seedsStr);

	std::vector<std::uint64_t> seeds;

	while (sstrm1 >> seed)
	{
		seeds.push_back( seed );
		source = seed;
		for (const auto& mapping : mappings)
		{
			dest = mapping.GetOutput(source);
			source = dest;
		}

		if (source < closestLocation)
		{
			closestLocation = source;
		}
	}

	std::cout << closestLocation << "\n";

	closestLocation = std::numeric_limits<std::uint64_t>::max();

	MappedRanges mr;

	for ( auto s : seeds )
	{
		mr.m_UnmappedDests.emplace_back( s, 1 );
	}

	for ( const auto& mapping : mappings )
	{
		auto dest = mapping.GetOutput( mr );
		dest.m_UnmappedDests.insert( dest.m_UnmappedDests.end(), dest.m_MappedDests.begin(), dest.m_MappedDests.end() );
		dest.m_MappedDests.clear();
		std::swap( mr, dest );
	}

	closestLocation = std::numeric_limits<std::uint64_t>::max();
	for ( const auto& [start, range] : mr.m_UnmappedDests )
	{
		if ( start < closestLocation )
		{
			closestLocation = start;
		}
	}

	std::cout << closestLocation << "\n";

	//part 2

	mr.m_MappedDests.clear();
	mr.m_UnmappedDests.clear();

	std::stringstream sstrm2( seedsStr );
	while ( sstrm2 >> seed >> range )
	{
		mr.m_UnmappedDests.emplace_back( seed, range );
	}

	for ( const auto& mapping : mappings )
	{
		auto dest = mapping.GetOutput( mr );
		dest.m_UnmappedDests.insert( dest.m_UnmappedDests.end(), dest.m_MappedDests.begin(), dest.m_MappedDests.end() );
		dest.m_MappedDests.clear();
		std::swap( mr, dest );
	}

	closestLocation = std::numeric_limits<std::uint64_t>::max();
	for ( const auto& [start, range] : mr.m_UnmappedDests )
	{
		if ( start < closestLocation )
		{
			closestLocation = start;
		}
	}

	std::cout << closestLocation << "\n";

	return 0;
}
