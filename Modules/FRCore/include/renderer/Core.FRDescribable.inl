#pragma once

#include "Core.FRDescribable.h"

namespace FR
{
	template<typename T>
	inline void FRDescribable::AddDescriptor(T&& pDescriptor)
	{
		mDescriptors.emplace(typeid(T), std::move(pDescriptor));
	}

	template<typename T>
	inline void FRDescribable::RemoveDescriptor()
	{
		if (auto it = mDescriptors.find(typeid(T)); it != mDescriptors.end())
		{
			mDescriptors.erase(it);
		}
	}

	template<typename T>
	inline bool FRDescribable::HasDescriptor() const
	{
		return mDescriptors.find(typeid(T)) != mDescriptors.end();
	}

	template<typename T>
	inline const T& FRDescribable::GetDescriptor() const
	{
		auto it = mDescriptors.find(typeid(T));
		return std::any_cast<const T&>(it->second);
	}

	template<typename T>
	inline bool FRDescribable::TryGetDescriptor(FROptRef<const T>& pOutDescriptor) const
	{
		if (auto it = mDescriptors.find(typeid(T)); it != mDescriptors.end())
		{
			pOutDescriptor = std::any_cast<const T&>(it->second);
			return true;
		}

		return false;
	}
}