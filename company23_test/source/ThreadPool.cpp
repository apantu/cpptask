#include "ThreadPool.h"

void ThreadPool::work()
{
	try
	{
		while (!mIsStopped)
		{
			task_t task = mTaskQueue.pop();
			task();
		}
	}
	catch (...)
	{
		//tbd: rethrow?
		return;
	}
}

ThreadPool::ThreadPool(std::size_t threadCount_)
	: mIsStopped(false)
	, mTaskQueue(100)
{
	mThreads.reserve(threadCount_);
	try
	{
		for (unsigned i = 0; i < threadCount_; ++i)
		{
			mThreads.push_back(std::thread(&ThreadPool::work, this));
		}
	}
	catch (...)
	{
		std::terminate();
	}
};

ThreadPool::~ThreadPool()
{
};

void ThreadPool::stop()
{
	mTaskQueue.close();
	mIsStopped = true;
};

bool ThreadPool::isStoped() const
{
	return mIsStopped;
};

void ThreadPool::join()
{
	for (auto& it : mThreads)
	{
		if (it.joinable())
		{
			it.join();
		}
	}
};

void ThreadPool::schedule(task_t task_, std::uint32_t priority_)
{
	if (!mIsStopped)
	{
		mTaskQueue.push(task_, priority_);
	}
};