// Day04.cpp : Source file for your target.
//

#include "Day04.h"
#include "Utils.h"

int main()
{
	std::regex re(R"(Card +(\d+): ([0-9 ]+) \| ([0-9 ]+))");
	auto input = utils::ReadFormattedInput("input.txt", re);

	std::uint64_t sum = 0;

	std::vector<int> cardCopies( input.size(), 1 );

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

		std::size_t cardIndex = std::stoull( card[1] ) - 1;
		for ( std::size_t i = 1; i <= matches.size(); i++ )
		{
			cardCopies[cardIndex + i] += cardCopies[cardIndex];
		}
	}

	std::cout << sum << "\n";
	std::cout << std::accumulate( cardCopies.begin(), cardCopies.end(), 0 ) << "\n";

	return 0;
}
