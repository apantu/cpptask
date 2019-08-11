#pragma once
#include <mutex>
#include <queue>
#include <atomic>

#include "Messages.h"

class MessageQueue
{
	std::mutex mMutex;
	std::condition_variable mIsNotEmpty;
	std::condition_variable mIsNotFull;
	std::atomic<bool> mIsClosed;

	const std::uint64_t mMaxQueueSize;

	std::queue<std::unique_ptr<Message>> mTaskQueue;

public:
	MessageQueue(const MessageQueue&) = delete;
	MessageQueue& operator=(const MessageQueue&) = delete;

	MessageQueue(std::uint64_t maxQueueSize_);
	~MessageQueue();

	void push(Message* message_);
	Message* pop();

	void close();
};



