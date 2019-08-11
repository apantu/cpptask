#pragma once
#include <atomic>

#include "MessageQueueHandler.h"
#include "MessageQueue.h"

//tbd: make a singleton
class Application
{
	std::mutex mMutex;
	std::atomic<bool> mStop;
	MessageQueue mMessageQueue;
	std::unique_ptr<MessageQueueHandler> mMessageProcessor;

public:
	Application(const Application&) = delete;
	const Application& operator=(const Application&) = delete;

	Application();
	~Application();
	
	void run();
	void stop();

	void print(const std::string& message_);
};


