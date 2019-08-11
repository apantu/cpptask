#pragma once
#include <string>
#include <sstream>
#include "Messages.h"

class InputTranslator
{
public:
	InputTranslator() = delete;
	InputTranslator(const InputTranslator&) = delete;
	InputTranslator& operator=(const InputTranslator&) = delete;

	static Message* translate(const std::string& command_);
};
