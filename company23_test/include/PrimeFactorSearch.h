#pragma once
#include <cstdint>
#include <vector>
#include <memory>

class MessageQueue;

class PrimeFactorsSearch
{
	std::uint64_t mNumber;
	MessageQueue* mCallback;

public:
	PrimeFactorsSearch(std::uint64_t number_, MessageQueue* callback_)
		: mNumber(number_)
		, mCallback(callback_)
	{
	}

	void operator()();
};
