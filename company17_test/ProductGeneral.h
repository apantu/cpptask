#pragma once

namespace product
{
	namespace general
	{
		template<typename T>
		struct GeneralAttribute
		{
			T value;
			explicit GeneralAttribute(T value_)
				: value(value_)
			{}
		};

		template<typename T>
		struct KeyAttribute : public GeneralAttribute<T>
		{
			explicit KeyAttribute(T value_)
				: GeneralAttribute<T>(value_)
			{}

			bool operator<(const KeyAttribute<T>& key_) const noexcept
			{
				return GeneralAttribute<T>::value < key_.value;
			}
		};

		template<typename T>
		struct HashedKeyAttribute : public GeneralAttribute<T>
		{
			explicit HashedKeyAttribute(T value_)
				: GeneralAttribute<T>(value_)
			{}

			bool operator==(const HashedKeyAttribute& key_) const noexcept
			{
				return GeneralAttribute<T>::value == key_.value;
			}
		};
	} 
}
