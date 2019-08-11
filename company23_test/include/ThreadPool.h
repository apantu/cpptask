#pragma once
#include <queue>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>

#include "TaskQueque.h"

class ThreadPool
{
public:
	using task_t = std::function<void()>;

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	ThreadPool(std::size_t threadCount_);
	~ThreadPool();

	void stop();
	bool isStoped() const;
	void join();
	void schedule(task_t task_, std::uint32_t priority_);

private:
	TaskQueque mTaskQueue;

	std::vector<std::thread> mThreads;

	std::atomic<bool> mIsStopped;

	std::mutex mMutex;

	void work();
};