#include "MessageHandlers.h"
#include "Messages.h"
#include "WorkloadManager.h"
#include "Application.h"

void RestartMessageHandler::handle(Message * message_)
{
	mCallback->restart();
}

void ExitMessageHandler::handle(Message * message_)
{
	mCallback->stop();
}

void PrimeFactorsMessageHandler::handle(Message * message_)
{
	auto attributes = static_cast<AttributeArray*>(message_->attr());

	auto size = attributes->size();
	for (decltype(size) i = 0; i < size; ++i)
	{
		auto attribute = attributes->at(i);
		const auto& attributeHandler = mSupportedAttributes.at(attribute->type());
		attributeHandler->handle(attribute);
	}

	mCallback->addTask(mNumber, mPriority);
}

void PrimeFactorsMessageHandler::setNumber(std::uint64_t number_)
{
	mNumber = number_;
}

void PrimeFactorsMessageHandler::setPriority(std::uint32_t priority_)
{
	mPriority = priority_;
}

void PrimeFactorsResultMessageHandler::handle(Message * message_)
{
	auto attribute = message_->attr();

	const auto& attributeHandler = mSupportedAttributes.at(attribute->type());
	attributeHandler->handle(attribute);

	mCallback->print(mMessage);
}

void PrimeFactorsResultMessageHandler::setMessage(const std::string& message_)
{
	mMessage.assign(message_);
}

MessageHandler::MessageHandler(WorkloadManager * context_)
	: mCallback(context_)
{
}

void LogMessageHandler::handle(Message * message_)
{
	auto attribute = message_->attr();

	const auto& attributeHandler = mSupportedAttributes.at(attribute->type());
	attributeHandler->handle(attribute);

	mCallback->print(mMessage);
}

void LogMessageHandler::setMessage(const std::string & message_)
{
	mMessage.assign(message_);
}
