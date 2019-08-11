#pragma once
#include "Attributes.h"
class PrimeFactorsMessageHandler;
class PrimeFactorsResultMessageHandler;
class LogMessageHandler;


class AttributeHandler
{
public:
	virtual void handle(IAttribute* attr_) = 0;
	virtual ~AttributeHandler() {}
};

class NumberAttributeHandler : public AttributeHandler
{
	PrimeFactorsMessageHandler* mMessageHandler;
public:
	NumberAttributeHandler(PrimeFactorsMessageHandler* messageHandler_) 
		: mMessageHandler(messageHandler_)
	{}

	virtual void handle(IAttribute* attr_);
};

class PriorityAttributeHandler : public AttributeHandler
{
	PrimeFactorsMessageHandler* mMessageHandler;
public:
	PriorityAttributeHandler(PrimeFactorsMessageHandler* messageHandler_) 
		: mMessageHandler(messageHandler_)
	{}

	void handle(IAttribute* attr_);
};

class ResultAttributeHandler : public AttributeHandler
{
	PrimeFactorsResultMessageHandler* mMessageHandler;
public:
	ResultAttributeHandler(PrimeFactorsResultMessageHandler* messageHandler_)
		: mMessageHandler(messageHandler_)
	{}

	void handle(IAttribute* attr_);
};


class StringAttributeHandler : public AttributeHandler
{
	LogMessageHandler* mMessageHandler;
public:
	StringAttributeHandler(LogMessageHandler* messageHandler_)
		: mMessageHandler(messageHandler_)
	{}

	void handle(IAttribute* attr_);
};
