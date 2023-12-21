// Day20.cpp : Source file for your target.
//

#include "Day20.h"
#include "Utils.h"

#include <cassert>

enum class ModuleType
{
	Broadcaster,
	FlipFlop,
	Nand,
	Output,
};

struct Module
{
	std::string name;
	ModuleType type = ModuleType::Output;
	std::vector<std::string> inputs;
	std::vector<std::string> outputs;
	bool state = false;
};

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::regex re(R"(^([\%\&]?)([a-z]+) -> (.+)$)");
	auto input = utils::ReadFormattedInput("input.txt", re);

	std::map<std::string, Module> modules;
	for (auto m : input)
	{
		Module mod;
		mod.name = m[2];
		std::string outputs = m[3];
		std::erase(outputs, ' ');
		mod.outputs = utils::Tokenize(outputs, ',');

		if (m[1].empty())
		{
			mod.type = ModuleType::Broadcaster;
		}
		else if (m[1] == "&")
		{
			mod.type = ModuleType::Nand;
		}
		else if (m[1] == "%")
		{
			mod.type = ModuleType::FlipFlop;
		}
		else
		{
			assert(false);
			mod.type = ModuleType::Output;
		}

		modules.emplace(mod.name, mod);
	}

	for (auto& [name, mod] : modules)
	{
		for (auto output : mod.outputs)
		{
			//assert(modules.contains(output));

			modules[output].inputs.push_back(name);
		}
	}

	std::size_t lowPulses = 0;
	std::size_t highPulses = 0;
	std::queue<std::pair<std::string, bool>> pulseTrain;

	std::map<std::string, std::size_t> part2;

	for (int i = 0; i < 5000; i++)
	{
		pulseTrain.push({ "broadcaster", false });

		while (!pulseTrain.empty())
		{
			auto [mod, level] = pulseTrain.front();
			level ? highPulses++ : lowPulses++;

			switch (modules[mod].type)
			{
			case ModuleType::Broadcaster:
				modules[mod].state = level;
				for (auto output : modules[mod].outputs)
				{
					pulseTrain.push({ output, level });
				}
				break;
			case ModuleType::FlipFlop:
				if (level == false)
				{
					modules[mod].state = !modules[mod].state;

					for (auto output : modules[mod].outputs)
					{
						pulseTrain.push({ output, modules[mod].state });
					}
				}
				break;
			case ModuleType::Nand:
				if (level == false)
				{
					modules[mod].state = true;
				}
				else
				{
					bool allI = true;
					for (auto in : modules[mod].inputs)
					{
						allI = allI && modules[in].state;
					}

					modules[mod].state = !allI;
				}

				for (auto output : modules[mod].outputs)
				{
					pulseTrain.push({ output, modules[mod].state });

					if (output == "sq" && modules[mod].state == true)
					{
						part2[mod] = i + 1;
					}
				}
				break;
			case ModuleType::Output:
				modules[mod].state = level;
				break;
			default:
				break;
			}

			pulseTrain.pop();
		}
	}

	utils::PrintResult(lowPulses * highPulses, startTime);

	std::size_t buttonPresses = 1;
	for (auto [name, presses] : part2)
	{
		buttonPresses = std::lcm(buttonPresses, presses);
	}

	utils::PrintResult(buttonPresses, startTime);

	return 0;
}
