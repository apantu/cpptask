#pragma once
#include <cstdint>
#include <vector>
#include "Attributes.h"

enum class MessageType
{
	Restart, Exit, PrimeFactorsResult, PrimeFactorsTask, Log
};

struct Message
{
	virtual MessageType type() = 0;
	virtual IAttribute* attr() = 0;
};

struct Restart : public Message
{
	virtual MessageType type() override
	{
		return MessageType::Restart;
	}
	virtual IAttribute* attr() override
	{
		return nullptr;
	}
};

struct Exit : public Message
{
	virtual MessageType type() override
	{
		return MessageType::Exit;
	}
	virtual IAttribute* attr() override
	{
		return nullptr;
	}
};

struct PrimeFactorsResult : public Message
{
	AttributeArray mAttributes;

	void add(std::uint64_t number_)
	{
		mAttributes.addAttribute(new NumberAttribute(number_));
	}

	virtual IAttribute* attr() override
	{
		return &mAttributes;
	}

	virtual MessageType type() override
	{
		return MessageType::PrimeFactorsResult;
	}
};

struct PrimeFactorsTask : public Message
{
	AttributeArray mAttributes;

	PrimeFactorsTask(std::uint64_t number_, std::uint32_t priority_)
	{
		mAttributes.addAttribute(new NumberAttribute(number_));
		mAttributes.addAttribute(new PriorityAttribute(priority_));
	};

	virtual MessageType type() override
	{
		return MessageType::PrimeFactorsTask;
	}

	virtual IAttribute* attr() override
	{
		return &mAttributes;
	}
};

struct LogMessage : public Message
{
	StringAttribute mAttribute;

	LogMessage(const std::string& message_)
		: mAttribute(message_)
	{}

	virtual IAttribute* attr() override
	{
		return &mAttribute;
	}

	virtual MessageType type() override
	{
		return MessageType::Log;
	}
};