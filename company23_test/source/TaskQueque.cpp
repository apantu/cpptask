#include "TaskQueque.h"

TaskQueque::TaskQueque(std::uint64_t maxQueueSize_)
	: mMaxQueueSize(maxQueueSize_)
	, mIsClosed(false)
{
}

TaskQueque::~TaskQueque()
{
}

void TaskQueque::push(const task_t & task_, std::uint32_t priority_)
{
	std::unique_lock<std::mutex> lock(mMutex);
	if (mMaxQueueSize == mTaskQueue.size())
	{
		mIsNotFull.wait(lock);
	}

	if (mIsClosed)
	{
		return;
	}
	
	mTaskQueue.push(std::make_pair(priority_, task_));

	lock.unlock();
	mIsNotEmpty.notify_one();
}

TaskQueque::task_t TaskQueque::pop()
{
	std::unique_lock<std::mutex> lock(mMutex);
	if (mTaskQueue.empty())
	{
		mIsNotEmpty.wait(lock);
	}
	
	if (mIsClosed)
	{
		return [] {};
	}

	task_t task = mTaskQueue.top().second;
	mTaskQueue.pop();

	lock.unlock();
	mIsNotFull.notify_one();

	return task;
}

void TaskQueque::close()
{
	std::lock_guard<std::mutex> lock(mMutex);
	mIsClosed = true;

	mIsNotFull.notify_all();
	mIsNotEmpty.notify_all();
}