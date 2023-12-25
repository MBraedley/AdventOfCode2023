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
	{}

	utils::Pos pos;
	utils::Direction lastStep;
	std::uint32_t stepsTaken;
	std::uint32_t currentCost;
	std::set<utils::Pos> visitedPoints;

	std::pair<std::size_t, std::size_t> inputSize;

	double GetCost() const
	{
		double avgCost = static_cast<double>(currentCost) / static_cast<double>(pos.GetManDistance(utils::Pos()));
		auto totalCost = currentCost + avgCost * ( pos.GetManDistance(utils::Pos(inputSize.first, inputSize.second)) + visitedPoints.size());
		return totalCost;
	}
};

auto operator<=>(const Step& lhs, const Step& rhs)
{
	//if (rhs.currentCost == lhs.currentCost)
	//{
	//	if (rhs.pos.GetManDistance(utils::Pos()) == lhs.pos.GetManDistance(utils::Pos()))
	//	{
	//		if (rhs.visitedPoints.size() == lhs.visitedPoints.size())
	//		{
	//			if (rhs.stepsTaken == lhs.stepsTaken)
	//			{
	//				return rhs.pos <=> lhs.pos;
	//			}
	//			return rhs.stepsTaken <=> lhs.stepsTaken;
	//		}
	//		return rhs.visitedPoints.size() <=> lhs.visitedPoints.size();
	//	}
	//	return rhs.pos.GetManDistance(utils::Pos()) <=> lhs.pos.GetManDistance(utils::Pos());
	//}
	//return rhs.currentCost <=> lhs.currentCost;
	return rhs.GetCost() <=> lhs.GetCost();
}

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("input.txt");

	std::priority_queue<Step> nextSteps;

	Step start(utils::Pos(), utils::Direction::East, 0, 0, input);

	nextSteps.push(start);

	utils::Pos end(input[0].size() - 1, input.size() - 1);

	while (nextSteps.top().pos != end)
	{
		auto p = nextSteps.top();

		nextSteps.pop();

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

	utils::PrintResult(nextSteps.top().currentCost + (input[end.Y][end.X] - '0'), startTime);

	return 0;
}
