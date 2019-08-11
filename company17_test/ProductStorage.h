#pragma once

#include "ProductTypes.h"

#include <list>
#include <map>
#include <unordered_map>

#include <mutex>

namespace product
{
	class Storage
	{
		static const char* codeNotFound;
		static const char* vendorNotFound;

		std::mutex mMutex;

		typedef std::list<Record> ProductList;
		typedef std::map<attribute::Vendor, ProductList> VendorStorage;
		typedef std::unordered_map<attribute::Code, Record*, attribute::hash::Code> CodeStorage;

		VendorStorage mVendorStorage;
		CodeStorage mCodeStorage;

		Storage(const Storage& ) = delete;
		Storage& operator=(const Storage& ) = delete;

		CodeStorage::iterator find(const attribute::Code& code_);
		VendorStorage::iterator find(const attribute::Vendor& vendor_);

		Record* addToVendorStorage(const Record& record_);
		void addToCodeStorage(Record* record_);

		attribute::Vendor removeFromCodeStorage(const attribute::Code& code_);
		void removeFromVendorStorage(const attribute::Code& code_, const attribute::Vendor& vendor_);

	public:
		Storage() = default;
		~Storage() = default;

		void add(const Record& record_);
		Record get(const attribute::Code& code_);
		std::vector<Record> get(const attribute::Vendor& vendor_);
		void remove(const attribute::Code& code_);
	};
}

