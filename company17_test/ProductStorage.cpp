#include "ProductStorage.h"

namespace product
{
	const char* Storage::codeNotFound = "Code of product is not presented in the storage.";
	const char* Storage::vendorNotFound = "Vendor is not presented in the storage.";

	Storage::CodeStorage::iterator Storage::find(const attribute::Code& code_)
	{
		const auto& it = mCodeStorage.find(code_);
		if (mCodeStorage.end() == it)
		{
			throw std::out_of_range(codeNotFound);
		}

		return it;
	}

	Storage::VendorStorage::iterator Storage::find(const attribute::Vendor& vendor_)
	{
		const auto& it = mVendorStorage.find(vendor_);
		if (mVendorStorage.end() == it)
		{
			throw std::out_of_range(vendorNotFound);
		}

		return it;
	}

	Record* Storage::addToVendorStorage(const Record& record_)
	{
		auto item = mVendorStorage.find(record_.vendor);
		if (mVendorStorage.end() == item)
		{
			const auto& pair = std::make_pair(record_.vendor, ProductList{ record_ });
			const auto& result = mVendorStorage.emplace(pair);
			item = result.first;
		}
		else
		{
			item->second.emplace_back(record_);
		}

		return& item->second.back();
	}

	void Storage::addToCodeStorage(Record* record_)
	{
		mCodeStorage.emplace(std::make_pair(record_->code, record_));
	}

	attribute::Vendor Storage::removeFromCodeStorage(const attribute::Code& code_)
	{
		const auto& it = find(code_);

		auto vendor = it->second->vendor;
		mCodeStorage.erase(it);

		return vendor;
	}

	void Storage::removeFromVendorStorage(const attribute::Code& code_, const attribute::Vendor& vendor_)
	{
		auto* list = &find(vendor_)->second;
		list->remove_if([code_](const product::Record& record_)
		{ return code_ == record_.code; });

		if (list->empty())
		{
			mVendorStorage.erase(vendor_);
		}
	}

	void Storage::add(const Record& record_)
	{
		std::lock_guard<std::mutex> guard(mMutex);

		const auto& item = addToVendorStorage(record_);
		addToCodeStorage(item);
	}

	product::Record Storage::get(const attribute::Code& code_)
	{
		std::lock_guard<std::mutex> guard(mMutex);

		const auto& it = find(code_);

		return Record(*it->second);
	}

	std::vector<Record> Storage::get(const attribute::Vendor& vendor_)
	{
		std::lock_guard<std::mutex> guard(mMutex);

		const auto& list = find(vendor_)->second;

		return std::vector<Record>(list.begin(), list.end());
	}

	void Storage::remove(const attribute::Code& code_)
	{
		std::lock_guard<std::mutex> guard(mMutex);

		const auto& vendor = removeFromCodeStorage(code_);
		removeFromVendorStorage(code_, vendor);
	}

}