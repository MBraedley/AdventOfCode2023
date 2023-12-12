// Day12.cpp : Source file for your target.
//

#include "Day12.h"
#include "Utils.h"

//enum class Spring
//{
//	Operational,
//	Damaged,
//	Unknown,
//};

std::vector<std::string> GetPermutations(const std::string& springs)
{
	std::vector<std::string> ret;
	auto rPos = springs.find_first_of('?');

	if (rPos == springs.npos)
	{
		ret.push_back(springs);
		return ret;
	}

	std::string springs1 = springs;
	springs1.replace(rPos, 1, 1, '.');
	//ret.push_back(springs1);
	auto moreOptions = GetPermutations(springs1);
	ret.insert(ret.end(), moreOptions.begin(), moreOptions.end());

	std::string springs2 = springs;
	springs2.replace(rPos, 1, 1, '#');
	//ret.push_back(springs2);
	moreOptions = GetPermutations(springs2);
	ret.insert(ret.end(), moreOptions.begin(), moreOptions.end());

	return ret;
}

std::regex GenerateRegex(const std::vector<int>& springGroups)
{
	bool beginningMatch = true;
	std::stringstream sstrm;
	for (int group : springGroups)
	{
		sstrm << (beginningMatch ? "\\.*" : "\\.+") << "#{" << group << "}";
		beginningMatch = false;
	}

	sstrm << "\\.*";

	return std::regex(sstrm.str());
}

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::vector<std::pair<std::string, std::vector<int>>> records;

	for (auto line : input)
	{
		std::stringstream sstrm(line);
		std::string r;
		sstrm >> r;
		//std::vector<Spring> vr;
		//for (char c : r)
		//{
		//	switch (c)
		//	{
		//	case '.':
		//		vr.push_back(Spring::Operational);
		//		break;
		//	case '#':
		//		vr.push_back(Spring::Damaged);
		//		break;
		//	case '?':
		//		vr.push_back(Spring::Unknown);
		//		break;
		//	default:
		//		throw std::invalid_argument("invalid spring type");
		//		break;
		//	}
		//}

		int count;
		std::vector<int> check;
		char c;
		while (sstrm >> count)
		{
			check.push_back(count);
			sstrm >> c;
		}
		records.emplace_back(r, check);
	}

	std::vector<std::uint32_t> matchCounts;
	for (auto [record, groups] : records)
	{
		auto re = GenerateRegex(groups);

		std::uint32_t count = 0;
		for (auto r : GetPermutations(record))
		{
			if (std::regex_match(r, re))
			{
				count++;
			}
		}

		matchCounts.push_back(count);
	}

	std::cout << std::accumulate(matchCounts.begin(), matchCounts.end(), 0) << "\n";

	return 0;
}
