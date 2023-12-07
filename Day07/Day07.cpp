// Day07.cpp : Source file for your target.
//

#include "Day07.h"
#include "Utils.h"

#include <cassert>

constexpr std::uint8_t GetCardValue( char c )
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
		return 11;
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

	HandOfCards( const std::string& hand, std::uint32_t wager ) :
		m_Wager(wager)
	{
		for ( char c : hand )
		{
			m_UnsortedHand.push_back( GetCardValue( c ) );
			m_Hand[GetCardValue( c )]++;
		}

		bool hasPair = false;
		bool hasTwoPair = false;
		bool hasTrip = false;
		bool hasQuad = false;
		bool hasQuint = false;

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
		}

		if ( hasQuint )
		{
			m_Rank = Rank::FiveOfAKind;
		}
		else if ( hasQuad )
		{
			m_Rank = Rank::FourOfAKind;
		}
		else if ( hasTrip && hasPair )
		{
			m_Rank = Rank::FullHouse;
		}
		else if ( hasTrip )
		{
			m_Rank = Rank::ThreeOfAKind;
		}
		else if ( hasTwoPair )
		{
			m_Rank = Rank::TwoPair;
		}
		else if ( hasPair )
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

	//std::vector<HandOfCards> hands;
	std::multiset<HandOfCards> sortedHands;
	for ( const auto& line : input )
	{
		//hands.emplace_back( line[1], std::stoi( line[2] ) );
		sortedHands.emplace( line[1], std::stoi( line[2] ) );
	}

	assert( sortedHands.size() == input.size() );

	std::uint32_t totalPayout = 0;
	std::uint32_t rank = 1;
	for ( const auto& hand : sortedHands )
	{
		totalPayout += hand.GetPayout( rank++ );
	}

	std::cout << totalPayout << "\n";

	return 0;
}
