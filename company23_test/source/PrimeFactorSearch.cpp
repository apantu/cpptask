#include "PrimeFactorSearch.h"
#include "MessageQueue.h"

void PrimeFactorsSearch::operator()()
{
	auto number = mNumber;
	std::vector<decltype(number)> primeFactors;
	primeFactors.push_back(number);

	decltype(number) tmp = 2;
	while (tmp * tmp <= number) 
	{
		if (number % tmp == 0)
		{
			primeFactors.push_back(tmp);
			number = static_cast<decltype(number)>(number / tmp);
		}
		else 
		{
			++tmp;
		}
	}
	if (number > 1) 
	{
		primeFactors.push_back(number);
	}

	std::unique_ptr<PrimeFactorsResult> result = std::make_unique<PrimeFactorsResult>();
	for (const auto& factor : primeFactors)
		result->add(factor);

	mCallback->push(result.release());
}