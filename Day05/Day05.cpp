// Day05.cpp : Source file for your target.
//

#include "Day05.h"
#include "Utils.h"

#include <optional>


class Mapping
{
public:
	Mapping( std::uint32_t source, std::uint32_t dest, std::uint32_t range ) :
		m_Source( source ), m_Dest( dest ), m_Range( range )
	{}

	~Mapping() = default;

	std::optional<std::uint32_t> GetOutput( std::uint32_t input ) const
	{
		std::optional<std::uint32_t> ret = std::nullopt;

		if ( input >= m_Source && input < m_Source + m_Range )
		{
			ret = m_Dest + (input - m_Source);
		}

		return ret;
	}

private:
	std::uint32_t m_Source;
	std::uint32_t m_Dest;
	std::uint32_t m_Range;
};

class MappingSet
{
public:
	MappingSet() = default;
	~MappingSet() = default;

	void AddMapping( std::uint32_t source, std::uint32_t dest, std::uint32_t range )
	{
		m_Mappings.emplace_back( source, dest, range );
	}

	std::uint32_t GetOutput( std::uint32_t input ) const
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

	std::uint32_t source, dest, range;

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

	std::uint32_t seed;
	std::uint32_t closestLocation = std::numeric_limits<std::uint32_t>::max();
	std::stringstream sstrm(seedsStr);

	while (sstrm >> seed)
	{
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

	return 0;
}
