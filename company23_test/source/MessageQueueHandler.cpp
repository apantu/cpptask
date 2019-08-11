#include "MessageQueueHandler.h"

#include "Application.h"
#include "ThreadPool.h"
#include "Messages.h"
#include "MessageHandlers.h"
#include "WorkloadManager.h"
#include "MessageQueue.h"
#include <memory>

MessageQueueHandler::MessageQueueHandler()
	: mUICallback(nullptr)
	, mWorkloadContext(nullptr)
	, mIsStopped(false)
	, mMessageQueue(nullptr)
{
}

MessageQueueHandler::~MessageQueueHandler()
{
}

void MessageQueueHandler::addUI(Application* ui_)
{
	mUICallback = ui_;
	mSupportedHandlers.emplace(std::make_pair(MessageType::PrimeFactorsResult, std::make_unique<PrimeFactorsResultMessageHandler>(mUICallback)));
	mSupportedHandlers.emplace(std::make_pair(MessageType::Exit, std::make_unique<ExitMessageHandler>(mUICallback)));
	mSupportedHandlers.emplace(std::make_pair(MessageType::Log, std::make_unique<LogMessageHandler>(mUICallback)));
}

void MessageQueueHandler::addMessageQueue(MessageQueue * messageQueue_)
{
	mMessageQueue = messageQueue_;
	mWorkloadContext = std::make_unique<WorkloadManager>(this, mMessageQueue);

	mSupportedHandlers.emplace(std::make_pair(MessageType::Restart, std::make_unique<RestartMessageHandler>(mWorkloadContext.get())));
	mSupportedHandlers.emplace(std::make_pair(MessageType::PrimeFactorsTask, std::make_unique<PrimeFactorsMessageHandler>(mWorkloadContext.get())));
}

void MessageQueueHandler::process(Message* message_)
{
	if (nullptr == message_)
		return;

	const auto &messageHandler = mSupportedHandlers.at(message_->type());
	messageHandler->handle(message_);
}

void MessageQueueHandler::stop()
{
	mWorkloadContext->stop();
	mMessageQueue->close();
	mIsStopped = true;
}

void MessageQueueHandler::run() 
{
	while (!mIsStopped) 
	{
		try 
		{
			process(mMessageQueue->pop());
		}
		catch (std::exception& /*ex*/) 
		{
			//trace
		}
	}
}
