// Day17.cpp : Source file for your target.
//

#include "Day17.h"
#include "Utils.h"

struct Step
{
	Step(
		utils::Pos _pos,
		utils::Direction _lastStep,
		std::uint32_t _stepsTaken,
		std::uint32_t _currentCost,
		const std::vector<std::string>& _input) :
		pos(_pos),
		lastStep(_lastStep),
		stepsTaken(_stepsTaken),
		currentCost(_currentCost),
		inputSize(std::make_pair(_input[0].size(), _input.size()))
	{
		double totalCost = 0.0;
		for (const auto& line : _input)
		{
			for (char c : line)
			{
				totalCost += c - '0';
			}
		}

		averageSquare = totalCost / (inputSize.first * inputSize.second);
	}

	utils::Pos pos;
	utils::Direction lastStep;
	std::uint32_t stepsTaken;
	std::uint32_t currentCost;
	std::set<utils::Pos> visitedPoints;

	std::pair<std::size_t, std::size_t> inputSize;
	double averageSquare;

	double GetCost() const
	{
		double remainingCost = pos.GetManDistance(utils::Pos(inputSize.first - 1, inputSize.second - 1));
		return currentCost + remainingCost;
	}
};

auto operator<=>(const Step& lhs, const Step& rhs)
{
	if (lhs.currentCost == rhs.currentCost)
	{
		if (lhs.pos == rhs.pos)
		{
			if (lhs.lastStep == rhs.lastStep)
			{
				if (lhs.stepsTaken == rhs.stepsTaken)
				{
					return lhs.visitedPoints.size() <=> rhs.visitedPoints.size();
				}

				return lhs.stepsTaken <=> rhs.stepsTaken;
			}

			return lhs.lastStep <=> rhs.lastStep;
		}

		return lhs.pos <=> rhs.pos;
	}

	return lhs.currentCost <=> rhs.currentCost;
}

bool operator==(const Step& lhs, const Step& rhs)
{
	return lhs.pos == rhs.pos
		&& lhs.currentCost == rhs.currentCost
		&& lhs.lastStep == rhs.lastStep
		&& lhs.stepsTaken == rhs.stepsTaken
		&& lhs.visitedPoints == rhs.visitedPoints;
}

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("input.txt");

	struct compareCost
	{
		bool operator()(const Step& lhs, const Step& rhs) { return lhs.GetCost() > rhs.GetCost(); }
	};

	std::priority_queue<Step, std::vector<Step>, compareCost> nextSteps;
	std::map<utils::Pos, std::set<Step>> posCosts;

	Step start(utils::Pos(), utils::Direction::East, 0, 0, input);

	nextSteps.push(start);

	utils::Pos end(input[0].size() - 1, input.size() - 1);

	std::uint32_t lowestCost = std::numeric_limits<std::uint32_t>::max();

	while (!nextSteps.empty())
	{
		auto p = nextSteps.top();

		nextSteps.pop();

		bool validPath = true;

		if (p.pos == end)
		{
			if (p.currentCost < lowestCost)
			{
				utils::PrintResult(p.currentCost, startTime);
				lowestCost = p.currentCost;
			}
			validPath = false;
		}
		else if (posCosts.contains(p.pos))
		{
			if (posCosts[p.pos].contains(p))
			{
				validPath = false;
			}
			else
			{
				for (auto s : posCosts[p.pos])
				{
					if (p.currentCost >= s.currentCost)
					{
						if (p.stepsTaken == 3)
						{
							validPath = false;
						}
						else if (p.lastStep == s.lastStep && p.stepsTaken >= s.stepsTaken)
						{
							validPath = false;
						}
					}
				}
			}
		}

		if (validPath)
		{
			posCosts[p.pos].emplace(p);
			for (auto dir : { utils::Direction::North, utils::Direction::East, utils::Direction::South, utils::Direction::West })
			{
				auto np = p.pos.GetNeighbour(dir, input);
				if (np.has_value() &&
					!p.visitedPoints.contains(*np) &&
					(dir != p.lastStep || p.stepsTaken < 3))
				{
					Step ns(*np, dir, dir == p.lastStep ? p.stepsTaken + 1 : 1, p.currentCost + (input[np->Y][np->X] - '0'), input);
					ns.visitedPoints = p.visitedPoints;
					ns.visitedPoints.emplace(p.pos);

					nextSteps.push(ns);
				}
			}
		}
	}

	utils::PrintResult(lowestCost, startTime);

	return 0;
}
