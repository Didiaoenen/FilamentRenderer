#pragma once

#include <any>
#include <typeindex>
#include <unordered_map>
#include <Tools.FROptRef.h>

namespace FR
{
	class FRDescribable
	{
	public:
		FRDescribable() = default;

		template<typename T>
		void AddDescriptor(T&& pDescriptor);

		template<typename T>
		void RemoveDescriptor();

		void ClearDescriptors();

		template<typename T>
		bool HasDescriptor() const;

		template<typename T>
		const T& GetDescriptor() const;

		template<typename T>
		bool TryGetDescriptor(FROptRef<const T>& pOutDescriptor) const;

	public:
		~FRDescribable() = default;

	private:
		std::unordered_map<std::type_index, std::any> mDescriptors;

	};
}

#include "Core.FRDescribable.inl"