// Day19.cpp : Source file for your target.
//

#include "Day19.h"
#include "Utils.h"

#include <functional>

using PartRating = std::map<char, int>;

class Rule
{
public:
	Rule(std::optional<char> category, std::function<bool(int)> op, std::string output) :
		m_Category(category),
		m_Operation(op),
		m_Output(output)
	{

	}

	explicit Rule(std::string rule)
	{
		if (rule.find(':') == rule.npos)
		{
			m_Output = rule;
		}
		else
		{
			m_Category = rule[0];
			auto tokens = utils::Tokenize(rule.substr(2), ':');

			m_Operation = [op = rule[1], rhs = std::stoi(tokens[0])](int val) -> bool
				{
					if (op == '>')
					{
						return val > rhs;
					}
					else if (op == '<')
					{
						return val < rhs;
					}
					else
					{
						throw std::invalid_argument("Invalid operator");
					}
				};

			m_Output = tokens[1];
		}
	}

	std::optional<std::string> RunRule(const PartRating& part) const
	{
		if (m_Category.has_value() && m_Operation != nullptr)
		{
			if (part.contains(m_Category.value()) && m_Operation(part.at(m_Category.value())))
			{
				return m_Output;
			}
			else
			{
				return std::nullopt;
			}
		}
		else
		{
			return m_Output;
		}
	}

private:
	std::optional<char> m_Category = std::nullopt;
	std::function<bool(int)> m_Operation = nullptr;
	std::string m_Output;
};

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::map<std::string, std::vector<Rule>> workflows;
	std::ifstream istrm("input.txt");
	std::string line;
	std::regex ruleRe(R"(([a-z]+)\{([^\}]+)\})");

	while (std::getline(istrm, line) && !line.empty())
	{
		std::smatch m;
		std::regex_match(line, m, ruleRe);
		auto rules = utils::Tokenize(m[2], ',');

		for (auto rule : rules)
		{
			workflows[m[1]].emplace_back(rule);
		}
	}

	std::vector<PartRating> parts;
	std::regex partRe(R"(\{x=(\d+),m=(\d+),a=(\d+),s=(\d+)\})");
	while (std::getline(istrm, line))
	{
		std::smatch m;
		std::regex_match(line, m, partRe);
		PartRating part;
		part['x'] = std::stoi(m[1]);
		part['m'] = std::stoi(m[2]);
		part['a'] = std::stoi(m[3]);
		part['s'] = std::stoi(m[4]);

		parts.push_back(part);
	}

	std::vector<PartRating> accepted;
	std::vector<PartRating> rejected;

	auto EvaluateWorkflow = [](const PartRating& part, const std::vector<Rule>& rules) -> std::string
		{
			for (const auto& rule : rules)
			{
				if (auto output = rule.RunRule(part); output.has_value())
				{
					return output.value();
				}
			}

			throw std::exception("No matching rule");
		};

	for (auto part : parts)
	{
		std::string workflow = "in";
		while (workflow != "A" && workflow != "R")
		{
			workflow = EvaluateWorkflow(part, workflows[workflow]);
		}

		workflow == "A" ? accepted.push_back(part) : rejected.push_back(part);
	}

	std::size_t sum = 0;
	for (const auto& part : accepted)
	{
		for (const auto& [_, rating] : part)
		{
			sum += rating;
		}
	}

	utils::PrintResult(sum, startTime);

	return 0;
}
