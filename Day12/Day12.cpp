// Day12.cpp : Source file for your target.
//

#include "Day12.h"
#include "Utils.h"

#include <thread>
#include <future>
#include <unordered_map>
#include <mutex>

using MemoKey = std::pair<std::string, int>;

namespace std
{
	template<>
	struct hash<MemoKey>
	{
		std::size_t operator()( const MemoKey& obj ) const noexcept
		{
			auto h1 = std::hash<std::string>{}(obj.first);
			auto h2 = std::hash<int>{}(obj.second);

			return h1 ^ h2;
		}
	};
}

std::unordered_map<MemoKey, std::optional<std::string>> MemoPad;
std::unordered_map<int, std::regex> RegexLookup;
std::mutex MemoLock;
std::mutex RegexLock;

std::regex& GetRegex( int group )
{
	std::unique_lock<std::mutex>( RegexLock );
	if ( !RegexLookup.contains( group ) )
	{
		std::stringstream sstrm;
		sstrm << R"(^[^#]*?([\?#]{)" << group << R"(})[^#])";
		RegexLookup.emplace( group, sstrm.str() );
	}
	return RegexLookup[group];
}

std::regex GetRegex( const std::vector<int>& groups, std::size_t reps )
{
	std::stringstream sstrm;

	sstrm << "^";

	if ( reps > 1 )
	{
		sstrm << "(";
	}
	
	bool firstGroup = true;
	for ( int group : groups )
	{
		sstrm << ( firstGroup ? "\\.*" : "\\.+" ) << "(#{" << group << "})";
		firstGroup = false;
	}

	sstrm << "[\\.\\?]?";

	if ( reps > 1 )
	{
		sstrm << "){" << reps << "}";
	}

	return std::regex( sstrm.str() );
}

const std::optional<std::string> DoRegex( std::string str, int group )
{
	std::unique_lock<std::mutex>( MemoLock );
	MemoKey key = std::make_pair( str, group );
	if ( !MemoPad.contains( key ) )
	{
		std::smatch m;
		std::regex& re = GetRegex( group );
		std::regex_search( key.first, m, re );
		std::optional<std::string> suffix;
		std::string prefix = m.prefix();
		if ( !m.empty() )
		{
			suffix = m.suffix().str();
		}

		MemoPad.emplace( key, suffix );
	}
	return MemoPad[key];
}

void GetMatchCount( const std::string& springs, const std::vector<int>& groups, std::size_t groupRep, const std::regex& fullMatchRegex, std::set<std::string>& matches )
{
	auto rPos = springs.find_first_of( '?' );

	if ( rPos == springs.npos )
	{
		matches.insert( springs );
		return;
	}

	std::smatch m;

	std::string springs1 = springs;
	springs1.replace( rPos, 1, 1, '.' );

	if ( std::regex_search( springs1, m, fullMatchRegex ) )
	{
		std::string suffix = m.suffix();
		if ( suffix.find( '#' ) == suffix.npos )
		{
			std::replace( springs1.begin(), springs1.end(), '?', '.' );
			matches.insert( springs1 );
		}
	}
	else
	{
		std::string unmatched = springs1;
		bool passed = true;

		for ( std::size_t i = 0; i < groupRep; i++ )
		{
			for ( int group : groups )
			{
				auto m = DoRegex( unmatched, group );
				if ( !m.has_value() )
				{
					passed = false;
					break;
				}
				else
				{
					unmatched = "." + m.value();
				}
			}
		}

		if ( passed )
		{
			GetMatchCount( springs1, groups, groupRep, fullMatchRegex, matches );
		}
	}

	std::string springs2 = springs;
	springs2.replace( rPos, 1, 1, '#' );

	if ( std::regex_search( springs2, m, fullMatchRegex ) )
	{
		std::string suffix = m.suffix();
		if ( suffix.find( '#' ) == suffix.npos )
		{
			std::replace( springs2.begin(), springs2.end(), '?', '.' );
			matches.insert( springs2 );
		}
	}
	else
	{
		std::string unmatched = springs2;
		bool passed = true;

		for ( std::size_t i = 0; i < groupRep; i++ )
		{
			for ( int group : groups )
			{
				auto m = DoRegex( unmatched, group );
				if ( !m.has_value() )
				{
					passed = false;
					break;
				}
				else
				{
					unmatched = "." + m.value();
				}
			}
		}

		if ( passed )
		{
			GetMatchCount( springs2, groups, groupRep, fullMatchRegex, matches );
		}
	}
}

int main()
{
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "input.txt" );

	std::vector<std::uint32_t> expected;
	expected.reserve( input.size() );
	std::ifstream eifstrm("expected.txt");
	std::uint32_t val;
	while ( eifstrm >> val )
	{
		expected.push_back( val );
	}

	std::vector<std::pair<std::string, std::vector<int>>> records;

	for ( auto line : input )
	{
		std::stringstream sstrm( line );
		std::string r;
		sstrm >> r;

		int count;
		std::vector<int> check;
		char c;
		while ( sstrm >> count )
		{
			check.push_back( count );
			sstrm >> c;
		}
		records.emplace_back( r, check );
	}

	std::vector<std::future<std::size_t>> futures1;
	std::vector<std::future<std::size_t>> futures2;
	std::size_t count1 = 0;
	std::size_t count2 = 0;

	auto expectedIter = expected.begin();

	for ( auto& [record, groups] : records )
	{
		std::set<std::string> matches1;
		GetMatchCount( "." + record + ".", groups, 1, GetRegex( groups, 1 ), matches1 );
		count1 += matches1.size();

		if ( matches1.size() != *expectedIter )
		{
			std::cout << record << " " << groups[0];
			for ( std::size_t i = 1; i < groups.size(); i++ )
			{
				std::cout << "," << groups[i];
			}

			std::cout << "  " << matches1.size() << " vs " << *expectedIter << "\n";
		}
		expectedIter++;
	}

	//for ( auto& f : futures1 )
	//{
	//	count1 += f.get();
	//}

	std::cout << count1 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	//part 2

	for ( auto& [record, groups] : records )
	{
		std::set<std::string> matches2;
		std::stringstream expRecord;
		expRecord << record;
		for ( int i = 1; i < 5; i++ )
		{
			expRecord << "?" << record;
		}
		GetMatchCount( "." + expRecord.str() + ".", groups, 5, GetRegex(groups, 5), matches2);
		count2 += matches2.size();
	}

	//for ( auto& f : futures2 )
	//{
	//	count2 += f.get();
	//}

	std::cout << count2 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	return 0;
}
