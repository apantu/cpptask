#pragma once
#include "ThreadPool.h"

class MessageQueueHandler;
class MessageQueue;
class WorkloadManager
{
	std::mutex mMutex;
	std::uint32_t mThreadsCount;
	std::unique_ptr<ThreadPool> mThreadPool;
	MessageQueueHandler* mCallback;
	MessageQueue* mMessageQueue;

public:
	WorkloadManager(MessageQueueHandler* mCallback_, MessageQueue* messageQueue_);
	~WorkloadManager();

	void restart();
	void stop();

	void addTask(std::uint64_t number_, std::uint32_t priority_);

	WorkloadManager(const WorkloadManager&) = delete;
	WorkloadManager& operator=(const WorkloadManager&) = delete;
};

