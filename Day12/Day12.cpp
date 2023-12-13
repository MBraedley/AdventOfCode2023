// Day12.cpp : Source file for your target.
//

#include "Day12.h"
#include "Utils.h"

#include <thread>
#include <future>
#include <unordered_map>

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

std::regex& GetRegex( int group )
{
	if ( !RegexLookup.contains( group ) )
	{
		std::stringstream sstrm;
		sstrm << R"([^#]([\?#]{)" << group << R"(})[^#])";
		RegexLookup.emplace( group, sstrm.str() );
	}
	return RegexLookup[group];
}

std::regex GetRegex( const std::vector<int>& groups )
{
	std::stringstream sstrm;
	for ( int group : groups )
	{
		sstrm << "[\\.\\?]+" << "[#\\?]{" << group << "}";
	}

	sstrm << "[\\.\\?]+";

	return std::regex( sstrm.str() );
}

const std::optional<std::string> DoRegex( std::string str, int group )
{
	MemoKey key = std::make_pair( str, group );
	if ( !MemoPad.contains( key ) )
	{
		std::smatch m;
		std::regex& re = GetRegex( group );
		std::regex_search( key.first, m, re );
		std::optional<std::string> suffix;
		std::string prefix = m.prefix();
		if ( !m.empty() && (prefix.empty() || prefix.find('#') == prefix.npos) )
		{
			suffix = m.suffix().str();
		}

		MemoPad.emplace( key, suffix );
	}
	return MemoPad[key];
}

void GetMatchCount( const std::string& springs, const std::vector<int>& groups, const std::regex& fullMatchRegex, std::set<std::string>& matches )
{
	auto rPos = springs.find_first_of( '?' );

	if ( rPos == springs.npos )
	{
		matches.insert( springs );
		return;
	}

	std::string springs1 = springs;
	springs1.replace( rPos, 1, 1, '.' );
	std::string unmatched = springs1;
	bool passed = true;
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

	if ( passed && std::regex_match( springs1, fullMatchRegex ) )
	{
		GetMatchCount( springs1, groups, fullMatchRegex, matches );
	}

	std::string springs2 = springs;
	springs2.replace( rPos, 1, 1, '#' );
	unmatched = springs2;
	passed = true;
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

	if ( passed && std::regex_match( springs2, fullMatchRegex ) )
	{
		GetMatchCount( springs2, groups, fullMatchRegex, matches );
	}
}

int main()
{
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "input.txt" );

	std::vector<std::pair<std::string, std::vector<int>>> records;

	for ( auto line : input )
	{
		std::stringstream sstrm( line );
		std::string r;
		sstrm >> r;
		r = "." + r + ".";//make the regex easier

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

	for ( auto& [record, groups] : records )
	{
		std::set<std::string> matches;
		GetMatchCount( record, groups, GetRegex( groups ), matches );
		count1 += matches.size();
		//futures1.emplace_back( std::async( std::launch::async, [&]() -> std::size_t
		//	{
		//		return GetMatchCount( record, groups );
		//	} ) );

		//futures2.emplace_back( std::async( std::launch::async, [&]() -> std::size_t
		//	{
		//		auto re = GenerateRegex( groups, 5 );
		//		std::stringstream expRecord;
		//		expRecord << record;
		//		for ( int i = 1; i < 5; i++ )
		//		{
		//			expRecord << "?" << record;
		//		}
		//		return GetMatchCount( expRecord.str(), re );
		//	} ) );
	}

	//for ( auto& f : futures1 )
	//{
	//	count1 += f.get();
	//}

	std::cout << count1 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	//part 2
	for ( auto& f : futures2 )
	{
		count2 += f.get();
	}

	std::cout << count2 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	return 0;
}
