// Day13.cpp : Source file for your target.
//

#include "Day13.h"
#include "Utils.h"

#include <stack>

int main()
{
	std::vector<std::vector<std::string>> maps;
	auto input = utils::ReadInput("input.txt");

	std::vector<std::string> map;
	for (auto& line : input)
	{
		if (line.empty())
		{
			maps.push_back(map);
			map.clear();
		}
		else
		{
			map.push_back(line);
		}
	}

	if (!map.empty())
	{
		maps.push_back(map);
	}

	auto ComapareStacks = [](const std::deque<std::string>& lhs, const std::deque<std::string>& rhs) -> bool
		{
			for (auto lIter = lhs.rbegin(), rIter = rhs.rbegin(); lIter != lhs.rend() && rIter != rhs.rend(); lIter++, rIter++)
			{
				if (*lIter != *rIter)
				{
					return false;
				}
			}

			return true;
		};

	auto GetReflectedLines = [&](const std::vector<std::string>& map) -> std::size_t
		{
			std::deque<std::string> lhs;
			for (const auto& s : map)
			{
				lhs.push_back(s);
			}

			std::deque<std::string> rhs;
			rhs.push_back(lhs.back());
			lhs.pop_back();

			while (!ComapareStacks(lhs, rhs) && !lhs.empty())
			{
				rhs.push_back(lhs.back());
				lhs.pop_back();
			}

			return lhs.size();
		};

	std::size_t horizontalSum = 0;
	std::size_t verticalSum = 0;

	for (const auto& m : maps)
	{
		horizontalSum += GetReflectedLines(m);
		auto mt = utils::Transpose(m);
		verticalSum += GetReflectedLines(mt);
	}

	std::cout << horizontalSum * 100 + verticalSum << "\n";

	return 0;
}
