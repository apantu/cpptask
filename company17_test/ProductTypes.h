#pragma once

#include "ProductGeneral.h"

#include <string>

namespace product
{
	namespace attribute
	{
		struct Vendor : public general::KeyAttribute<std::string>
		{
			explicit Vendor(const std::string& value_) noexcept
				: KeyAttribute<std::string>(value_)
			{};
		};
		struct Code : public general::HashedKeyAttribute<std::string>
		{
			explicit Code(const std::string& value_) noexcept
				: HashedKeyAttribute<std::string>(value_)
			{};
		};
		struct Name : public general::GeneralAttribute<std::string>
		{
			explicit Name(const std::string& value_) noexcept
				: GeneralAttribute<std::string>(value_)
			{};
		};
		struct Price : public general::GeneralAttribute<std::uint32_t>
		{
			explicit Price(uint32_t value_) noexcept
				: GeneralAttribute<uint32_t>(value_)
			{};
		};

		namespace hash
		{
			struct Code
			{
				size_t operator()(const attribute::Code& key_) const noexcept
				{
					return std::hash<std::string>{}(key_.value);
				}
			};
		}
	}

	struct Record
	{
		attribute::Vendor vendor;
		attribute::Code code;
		attribute::Name name;
		attribute::Price price;
	};

}
