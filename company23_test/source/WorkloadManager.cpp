#include "WorkloadManager.h"
#include "PrimeFactorSearch.h"
#include "Messages.h"
#include "MessageQueueHandler.h"
#include "MessageQueue.h"

WorkloadManager::WorkloadManager(MessageQueueHandler* callback_, MessageQueue* messageQueue_)
	: mThreadsCount(std::thread::hardware_concurrency() + 1)
	, mCallback(callback_)
	, mMessageQueue(messageQueue_)
	, mThreadPool(std::make_unique<ThreadPool>(mThreadsCount))
{
}

WorkloadManager::~WorkloadManager()
{
	stop();

	mMessageQueue->push(new LogMessage("All work stopped."));
}

void WorkloadManager::restart()
{
	std::lock_guard<std::mutex> guard(mMutex);

	mThreadPool->stop();
	mThreadPool->join();
	mThreadPool = std::make_unique<ThreadPool>(++mThreadsCount);
	
	mMessageQueue->push(new LogMessage("All work stopped. ThreadPool restarted with " + std::to_string(mThreadsCount) + " threads"));
}

void WorkloadManager::stop()
{
	std::lock_guard<std::mutex> guard(mMutex);

	mThreadPool->stop();
	mThreadPool->join();
}

void WorkloadManager::addTask(std::uint64_t number_, std::uint32_t priority_)
{
	std::lock_guard<std::mutex> guard(mMutex);

	mThreadPool->schedule(PrimeFactorsSearch(number_, mMessageQueue), priority_);
	
	mMessageQueue->push(new LogMessage("Add prime factorization task. Number = " + std::to_string(number_) + " priority = " + std::to_string(priority_)));
}