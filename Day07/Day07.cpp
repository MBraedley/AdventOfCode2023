// Day07.cpp : Source file for your target.
//

#include "Day07.h"
#include "Utils.h"

#include <cassert>

constexpr std::uint8_t GetCardValue( char c, bool part2 = false )
{
	if ( c >= '0' && c <= '9' )
	{
		return c - '0';
	}
	else if ( c == 'T' )
	{
		return 10;
	}
	else if ( c == 'J' )
	{
		if ( part2 )
		{
			return 1;
		}
		else
		{
			return 11;
		}
	}
	else if ( c == 'Q' )
	{
		return 12;
	}
	else if ( c == 'K' )
	{
		return 13;
	}
	else if ( c == 'A' )
	{
		return 14;
	}
	else
	{
		throw std::invalid_argument( "Invalid card" );
	}
}

class HandOfCards
{
public:
	enum class Rank
	{
		HighCard,
		OnePair,
		TwoPair,
		ThreeOfAKind,
		FullHouse,
		FourOfAKind,
		FiveOfAKind,
	};

	HandOfCards( const std::string& hand, std::uint32_t wager, bool part2 = false ) :
		m_Wager(wager)
	{
		for ( char c : hand )
		{
			m_UnsortedHand.push_back( GetCardValue( c, part2 ) );
			m_Hand[GetCardValue( c, part2 )]++;
		}

		std::uint8_t jokerCount = 0;
		if ( part2 && m_Hand.contains( 1 ) )
		{
			jokerCount = m_Hand[1];
		}

		bool hasPair = false;
		bool hasTwoPair = false;
		bool hasTrip = false;
		bool hasQuad = false;
		bool hasQuint = false;
		std::uint8_t largestSet = 1;

		for ( const auto& [value, count] : m_Hand )
		{
			switch ( count )
			{
			case 5:
				hasQuint = true;
				break;
			case 4:
				hasQuad = true;
				break;
			case 3:
				hasTrip = true;
				break;
			case 2:
			{
				if ( hasPair )
				{
					hasTwoPair = true;
				}
				else
				{
					hasPair = true;
				}
				break;
			}
			case 1:
			default:
				break;
			}

			if ( count > largestSet && value != 1 )
			{
				largestSet = count;
			}
		}

		if ( hasQuint || largestSet + jokerCount == 5 )
		{
			m_Rank = Rank::FiveOfAKind;
		}
		else if ( hasQuad || largestSet + jokerCount == 4 )
		{
			m_Rank = Rank::FourOfAKind;
		}
		else if ( hasTrip && hasPair || hasTwoPair && jokerCount == 1 )
		{
			m_Rank = Rank::FullHouse;
		}
		else if ( hasTrip || largestSet + jokerCount == 3 )
		{
			m_Rank = Rank::ThreeOfAKind;
		}
		else if ( hasTwoPair )
		{
			m_Rank = Rank::TwoPair;
		}
		else if ( hasPair || largestSet + jokerCount == 2 )
		{
			m_Rank = Rank::OnePair;
		}
		else
		{
			m_Rank = Rank::HighCard;
		}
	}
	
	~HandOfCards() = default;

	std::uint32_t GetPayout( std::uint32_t rank ) const
	{
		return m_Wager * rank;
	}

	auto operator<=>( const HandOfCards& other ) const
	{
		auto rankComp = this->m_Rank <=> other.m_Rank;
		if ( rankComp == std::strong_ordering::equal )
		{
			return this->GetHandValue() <=> other.GetHandValue();
		}
		return rankComp;
	}

private:
	std::uint32_t GetHandValue() const
	{
		std::uint32_t val = 0;
		for ( auto c : m_UnsortedHand )
		{
			val = val * 100 + c;
		}

		return val;
	}

	std::vector<std::uint8_t> m_UnsortedHand;
	std::map<std::uint8_t, std::uint8_t> m_Hand;
	std::uint32_t m_Wager;
	Rank m_Rank;
};

int main()
{
	std::regex re( R"(([2-9TJQKA]{5}) (\d+))" );
	auto input = utils::ReadFormattedInput( "input.txt", re );

	std::multiset<HandOfCards> sortedHands1;
	std::multiset<HandOfCards> sortedHands2;
	for ( const auto& line : input )
	{
		sortedHands1.emplace( line[1], std::stoi( line[2] ) );
		sortedHands2.emplace( line[1], std::stoi( line[2] ), true );
	}

	assert( sortedHands1.size() == input.size() );
	assert( sortedHands2.size() == input.size() );

	std::uint32_t totalPayout = 0;
	std::uint32_t rank = 1;
	for ( const auto& hand : sortedHands1 )
	{
		totalPayout += hand.GetPayout( rank++ );
	}

	std::cout << totalPayout << "\n";

	//part 2

	totalPayout = 0;
	rank = 1;
	for ( const auto& hand : sortedHands2 )
	{
		totalPayout += hand.GetPayout( rank++ );
	}

	std::cout << totalPayout << "\n";

	return 0;
}
