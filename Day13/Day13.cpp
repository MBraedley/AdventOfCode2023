// Day13.cpp : Source file for your target.
//

#include "Day13.h"
#include "Utils.h"

#include <stack>
#include <cassert>

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

	auto GetReflectedLines = [&](const std::vector<std::string>& map, std::size_t oldSize = 0) -> std::size_t
		{
			std::deque<std::string> lhs;
			for (const auto& s : map)
			{
				lhs.push_back(s);
			}

			std::deque<std::string> rhs;
			rhs.push_back(lhs.back());
			lhs.pop_back();

			while ((lhs.size() == oldSize || !ComapareStacks(lhs, rhs)) && !lhs.empty())
			{
				rhs.push_back(lhs.back());
				lhs.pop_back();
			}

			return lhs.size();
		};

	std::size_t horizontalSum = 0;
	std::size_t verticalSum = 0;

	std::vector<std::pair<std::size_t, std::size_t>> reflections;

	for (const auto& m : maps)
	{
		auto h = GetReflectedLines(m);
		horizontalSum += h;
		auto mt = utils::Transpose(m);
		auto v = GetReflectedLines(mt);
		verticalSum += v;
		reflections.emplace_back(h, v);
	}

	std::cout << horizontalSum * 100 + verticalSum << "\n";

	//part 2
	
	horizontalSum = 0;
	verticalSum = 0;

	auto runReflections = [&](std::vector<std::string> map, std::size_t i)
		{
			for (auto& line : map)
			{
				for (auto& c : line)
				{
					c = (c == '.' ? '#' : '.');

					auto h = GetReflectedLines(map, reflections[i].first);
					if (h != reflections[i].first && h != 0)
					{
						horizontalSum += h;
						return;
					}

					auto mt = utils::Transpose(map);
					auto v = GetReflectedLines(mt, reflections[i].second);
					if (v != reflections[i].second && v != 0)
					{
						verticalSum += v;
						return;
					}

					c = (c == '.' ? '#' : '.');
				}
			}

			throw std::exception("no new refelction");
		};

	for (size_t i = 0; i < reflections.size(); i++)
	{
		auto& m = maps[i];
		runReflections(m, i);
	}

	std::cout << horizontalSum * 100 + verticalSum << "\n";

	return 0;
}
