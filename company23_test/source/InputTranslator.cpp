#include "InputTranslator.h"
#include <algorithm>

Message* InputTranslator::translate(const std::string& command_)
{
	std::string command(command_);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (0 == command.compare("restart"))
	{
		return new Restart();
	}

	if (0 == command.compare("exit"))
	{
		return new Exit();
	}

	const auto separator = ' ';
	auto separatorPosition = command.find(separator);
	if (command.npos != separatorPosition)
	{
		std::stringstream tmp(command);
		std::uint64_t number;
		tmp >> number;
		std::uint32_t priority;
		tmp >> priority;

		return new PrimeFactorsTask(number, priority);
	}

	throw std::logic_error("Unsupported command!");
}
