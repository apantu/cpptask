#pragma once
#include <mutex>
#include <queue>
#include <atomic>

class TaskQueque
{
	using task_t = std::function<void()>;

	std::mutex mMutex;
	std::condition_variable mIsNotEmpty;
	std::condition_variable mIsNotFull;
	std::atomic<bool> mIsClosed;

	const std::uint64_t mMaxQueueSize;

	using taskPair = std::pair<std::uint32_t, task_t>;

	struct taskPairComparsion
	{
		bool operator()(const taskPair& pair1_, const taskPair& pair2_)
		{
			return pair1_.first < pair2_.first;
		}
	};

	std::priority_queue<taskPair, std::vector<taskPair>, taskPairComparsion> mTaskQueue;

public:
	TaskQueque(const TaskQueque&) = delete;
	TaskQueque& operator=(const TaskQueque&) = delete;

	TaskQueque(std::uint64_t maxQueueSize_);
	~TaskQueque();

	void push(const task_t& task_, std::uint32_t priority_);
	task_t pop();

	void close();
};

