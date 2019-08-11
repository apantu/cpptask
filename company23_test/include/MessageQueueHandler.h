#pragma once

#include <memory>
#include <map>
#include <atomic>
#include <mutex>
#include "Messages.h"

class Application;
class MessageHandler;
class WorkloadManager;
class MessageQueue;

class MessageQueueHandler
{
	std::mutex mMutex;
	std::map<MessageType, std::unique_ptr<MessageHandler>> mSupportedHandlers;
	Application* mUICallback;
	std::unique_ptr<WorkloadManager> mWorkloadContext;
	MessageQueue* mMessageQueue;
	std::atomic<bool> mIsStopped;

public:

	MessageQueueHandler(const MessageQueueHandler&) = delete;
	MessageQueueHandler& operator=(const MessageQueueHandler&) = delete;

	MessageQueueHandler();
	~MessageQueueHandler();
	
	void addUI(Application* ui_);
	void addMessageQueue(MessageQueue* messageQueue_);

	void process(Message* message_);
	void stop();
	void run();
};