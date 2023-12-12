// Day12.cpp : Source file for your target.
//

#include "Day12.h"
#include "Utils.h"

#include <thread>
#include <future>

std::uint64_t GetMatchCount( const std::string& springs, const std::regex& re )
{
	auto rPos = springs.find_first_of( '?' );

	if ( rPos == springs.npos )
	{
		if ( std::regex_match( springs, re ) )
		{
			return 1;
		}
		return 0;
	}

	std::uint64_t count = 0;

	std::string springs1 = springs;
	springs1.replace( rPos, 1, 1, '.' );
	if ( std::regex_match( springs1, re ) )
	{
		count += GetMatchCount( springs1, re );
	}

	std::string springs2 = springs;
	springs2.replace( rPos, 1, 1, '#' );
	if ( std::regex_match( springs2, re ) )
	{
		count += GetMatchCount( springs2, re );
	}

	return count;
}

std::regex GenerateRegex( const std::vector<int>& springGroups, int reps )
{
	bool beginningMatch = true;
	std::stringstream sstrm;
	for ( int i = 0; i < reps; i++ )
	{
		for ( int group : springGroups )
		{
			sstrm << (beginningMatch ? "[\\.\\?]*" : "[\\.\\?]+") << "[#\\?]{" << group << "}";
			beginningMatch = false;
		}
	}

	sstrm << "[\\.\\?]*";

	return std::regex( sstrm.str() );
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

	for ( auto& [record, groups] : records )
	{
		futures1.emplace_back( std::async( std::launch::async, [&]() -> std::size_t
			{
				auto re = GenerateRegex( groups, 1 );
				return GetMatchCount( record, re );
			} ) );

		futures2.emplace_back( std::async( std::launch::async, [&]() -> std::size_t
			{
				auto re = GenerateRegex( groups, 5 );
				std::stringstream expRecord;
				expRecord << record;
				for ( int i = 1; i < 5; i++ )
				{
					expRecord << "?" << record;
				}
				return GetMatchCount( expRecord.str(), re );
			} ) );
	}

	std::size_t count1 = 0;
	std::size_t longestBranch = 0;
	for ( auto& f : futures1 )
	{
		count1 += f.get();
	}

	std::cout << count1 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	//part 2
	std::size_t count2 = 0;
	for ( auto& f : futures2 )
	{
		count2 += f.get();
	}

	std::cout << count2 << "\n";
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp) << "\n";

	return 0;
}
