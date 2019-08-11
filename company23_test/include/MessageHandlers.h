#pragma once
#include <memory>
#include <map>
#include "Attributes.h"
#include "AttributeHandlers.h"

struct Message;
class WorkloadManager;
class Application;

class MessageHandler
{
protected:
	WorkloadManager* mCallback;

public:
	MessageHandler(WorkloadManager* context_);
	virtual void handle(Message* message_) = 0;
};

class RestartMessageHandler : public MessageHandler
{
public:
	RestartMessageHandler(WorkloadManager* context_) : MessageHandler(context_) {};
	virtual void handle(Message* message_) override;
};

class ExitMessageHandler : public MessageHandler
{
	Application* mCallback;
public:
	ExitMessageHandler(Application* ui_) 
		: MessageHandler(nullptr) 
		, mCallback(ui_)
	{
	};
	virtual void handle(Message* message_) override;
};

class PrimeFactorsMessageHandler : public MessageHandler
{
	std::map<AttributeType, std::shared_ptr<AttributeHandler>> mSupportedAttributes;
	std::uint64_t mNumber;
	std::uint32_t mPriority;

public:
	PrimeFactorsMessageHandler(WorkloadManager* context_) : MessageHandler(context_), mNumber(0), mPriority(0)
	{
		mSupportedAttributes.emplace(std::make_pair(AttributeType::Number, std::make_shared<NumberAttributeHandler>(this)));
		mSupportedAttributes.emplace(std::make_pair(AttributeType::Priority, std::make_shared<PriorityAttributeHandler>(this)));
	};

	virtual void handle(Message* message_) override;

	void setNumber(std::uint64_t number_);
	void setPriority(std::uint32_t priority_);
};

class PrimeFactorsResultMessageHandler : public PrimeFactorsMessageHandler
{
	std::map<AttributeType, std::shared_ptr<AttributeHandler>> mSupportedAttributes;
	Application* mCallback;

	std::string mMessage;

public:
	PrimeFactorsResultMessageHandler(Application* ui_) 
		: PrimeFactorsMessageHandler(nullptr)
		, mCallback(ui_)
	{
		mSupportedAttributes.emplace(std::make_pair(AttributeType::Array, std::make_shared<ResultAttributeHandler>(this)));
	};

	virtual void handle(Message* message_) override;

	void setMessage(const std::string& message_);
};

class LogMessageHandler : public MessageHandler
{
	std::map<AttributeType, std::shared_ptr<AttributeHandler>> mSupportedAttributes;
	Application* mCallback;

	std::string mMessage;

public:
	LogMessageHandler(Application* ui_)
		: MessageHandler(nullptr)
		, mCallback(ui_)
	{
		mSupportedAttributes.emplace(std::make_pair(AttributeType::String, std::make_shared<StringAttributeHandler>(this)));
	};

	virtual void handle(Message* message_) override;

	void setMessage(const std::string& message_);
};