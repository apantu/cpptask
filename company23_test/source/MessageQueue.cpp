#include "MessageQueue.h"


MessageQueue::MessageQueue(std::uint64_t maxQueueSize_)
	: mMaxQueueSize(maxQueueSize_)
	, mIsClosed(false)
{
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::push(Message* message_)
{
	std::unique_lock<std::mutex> lock(mMutex);
	if (mMaxQueueSize == mTaskQueue.size())
	{
		mIsNotFull.wait(lock);
	}

	if (!mIsClosed)
	{
		mTaskQueue.push(std::unique_ptr<Message>(message_));

		lock.unlock();
		mIsNotEmpty.notify_one();
	}
}

Message* MessageQueue::pop()
{
	std::unique_lock<std::mutex> lock(mMutex);
	if (mTaskQueue.empty())
	{
		mIsNotEmpty.wait(lock);
	}

	if (mIsClosed)
		return nullptr;

	Message* message = mTaskQueue.front().release();
	mTaskQueue.pop();

	lock.unlock();
	mIsNotFull.notify_one();

	return message;
}

void MessageQueue::close()
{
	std::lock_guard<std::mutex> lock(mMutex);
	mIsClosed = true;

	mIsNotEmpty.notify_all();
	mIsNotFull.notify_all();
}
