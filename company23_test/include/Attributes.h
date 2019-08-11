#pragma once
#include <vector>
#include <string>

enum class AttributeType
{
	Number, Priority, Array, String
};

class IAttribute
{
public:
	virtual AttributeType type() const = 0;
};

class AttributeArray : public IAttribute
{
	std::vector<std::unique_ptr<IAttribute>> mAttributes;

public:
	void addAttribute(IAttribute* attr_)
	{
		mAttributes.emplace_back(std::unique_ptr<IAttribute>(attr_));
	}
	
	IAttribute* at(size_t index_)
	{
		return mAttributes.at(index_).get();
	};

	std::size_t size()
	{
		return mAttributes.size();
	};

	virtual AttributeType type() const override
	{
		return AttributeType::Array;
	}
};

class NumberAttribute : public IAttribute
{
	std::uint64_t mNumber;

public:
	NumberAttribute(std::uint64_t number_)
		: mNumber(number_)
	{
	}

	std::uint64_t get() const
	{
		return mNumber;
	};

	virtual AttributeType type() const override
	{
		return AttributeType::Number;
	}
};

class PriorityAttribute : public IAttribute
{
	std::uint32_t mPriority;

public:
	PriorityAttribute(std::uint32_t priority_) 
		: mPriority(priority_)
	{
	}

	std::uint32_t get() const
	{
		return mPriority;
	};

	virtual AttributeType type() const override
	{
		return AttributeType::Priority;
	}
};

class StringAttribute : public IAttribute
{
	std::string mMessage;

public:
	StringAttribute(const std::string& message_)
		: mMessage(message_)
	{
	}

	std::string get() const
	{
		return mMessage;
	};

	virtual AttributeType type() const override
	{
		return AttributeType::String;
	}
};