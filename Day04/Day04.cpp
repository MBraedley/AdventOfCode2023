// Day04.cpp : Source file for your target.
//

#include "Day04.h"
#include "Utils.h"

int main()
{
	std::regex re(R"(Card +(\d+): ([0-9 ]+) \| ([0-9 ]+))");
	auto input = utils::ReadFormattedInput("input.txt", re);

	std::uint64_t sum = 0;

	for (auto card : input)
	{
		auto winningNumbers = utils::Tokenize(card[2], ' ');
		auto cardNumbers = utils::Tokenize(card[3], ' ');

		std::set<int> w;
		for (auto num : winningNumbers)
		{
			w.insert(std::stoi(num));
		}

		std::set<int> p;
		for (auto num : cardNumbers)
		{
			p.insert(std::stoi(num));
		}

		std::vector<int> matches;
		std::set_intersection(w.begin(), w.end(), p.begin(), p.end(), std::back_inserter(matches));

		if (!matches.empty())
		{
			sum += std::pow(2ll, matches.size() - 1ll);
		}
	}

	std::cout << sum << "\n";

	return 0;
}
