#include "AttributeHandlers.h"
#include "MessageHandlers.h"
#include <string>

void NumberAttributeHandler::handle(IAttribute* attr_)
{
	NumberAttribute* attr = static_cast<NumberAttribute*>(attr_);
	auto number = attr->get();
	mMessageHandler->setNumber(number);
};

void PriorityAttributeHandler::handle(IAttribute* attr_)
{
	PriorityAttribute* attr = static_cast<PriorityAttribute*>(attr_);
	auto priority = attr->get();
	mMessageHandler->setPriority(priority);
};

void ResultAttributeHandler::handle(IAttribute * attr_)
{
	AttributeArray* array = static_cast<AttributeArray*>(attr_);

	std::string message("Number: ");

	auto size = array->size();
	for (decltype(size) i = 0; i < size; ++i)
	{
		if (1 == i)
		{
			message.append(", result: ");
		}

		NumberAttribute* attr = static_cast<NumberAttribute*>(array->at(i));
		auto number = attr->get();

		message.append(std::to_string(number));
		message.append(" ");
	}
	
	mMessageHandler->setMessage(message);
}

void StringAttributeHandler::handle(IAttribute * attr_)
{
	StringAttribute* attr = static_cast<StringAttribute*>(attr_);
	auto message = attr->get();
	mMessageHandler->setMessage(message);
}
