// Day09.cpp : Source file for your target.
//

#include "Day09.h"
#include "Utils.h"

class Polynomial
{
public:
	Polynomial(const std::deque<std::int64_t>& poly)
	{
		m_Regression.push_back(poly);
		CreateRegression();
	}

	void CreateRegression()
	{
		const auto& p = m_Regression.back();
		if (p.size() <= 1)
		{
			return;
		}

		bool done = true;
		std::deque<std::int64_t> np;
		for (std::size_t i = 1; i < p.size(); i++)
		{
			np.push_back(p[i] - p[i - 1]);
			if (np.back() != 0)
			{
				done = false;
			}
		}
		m_Regression.push_back(np);

		if (!done)
		{
			CreateRegression();
		}
	}

	std::int64_t GetNextValue()
	{
		for (std::size_t i = 1; i < m_Regression.size(); i++)
		{
			std::size_t n = m_Regression.size() - i;
			m_Regression[n - 1].push_back(m_Regression[n].back() + m_Regression[n - 1].back());
		}

		return m_Regression[0].back();
	}

	std::int64_t GetPrevValue()
	{
		for (std::size_t i = 1; i < m_Regression.size(); i++)
		{
			std::size_t n = m_Regression.size() - i;
			m_Regression[n - 1].push_front(m_Regression[n - 1].front() - m_Regression[n].front());
		}

		return m_Regression[0].front();
	}

	~Polynomial() = default;

private:
	std::vector<std::deque<std::int64_t>> m_Regression;
};

int main()
{
	auto input = utils::ReadInput("input.txt");

	std::int64_t sum1 = 0;
	std::int64_t sum2 = 0;

	std::int64_t val;
	for (auto line : input)
	{
		std::deque<std::int64_t> poly;
		std::stringstream sstrm(line);
		while (sstrm >> val)
		{
			poly.push_back(val);
		}
		Polynomial p(poly);
		sum1 += p.GetNextValue();
		sum2 += p.GetPrevValue();
	}

	std::cout << sum1 << "\n" << sum2 << "\n";

	return 0;
}
