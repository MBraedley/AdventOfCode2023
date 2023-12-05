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
			ret = m_Dest + (m_Source - input);
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
	return 0;
}
