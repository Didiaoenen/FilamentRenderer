#pragma once

#include "Core.FRARenderFeature.h"
#include "Core.FRCompositeRenderer.h"

namespace FR
{
	template <typename T, typename... Args>
	T& FRCompositeRenderer::AddFeature(Args&&... pArgs)
	{
		static_assert(std::is_base_of<ARenderFeature, T>::value, "T must inherit from ARenderFeature");
		T* feature = new T(*this, std::forward<Args>(pArgs)...);
		mFeatures.emplace(typeid(T), feature);
		return *feature;
	}

	template<typename T>
	inline bool FRCompositeRenderer::RemoveFeature()
	{
		static_assert(std::is_base_of<ARenderFeature, T>::value, "T should derive from ARenderFeature");
		if (auto it = mFeatures.find(typeid(T)); it != mFeatures.end())
		{
			mFeatures.erase(it);
			return true;
		}

		return false;
	}

	template<typename T>
	inline T& FRCompositeRenderer::GetFeature() const
	{
		static_assert(std::is_base_of<ARenderFeature, T>::value, "T should derive from ARenderFeature");
		auto it = mFeatures.find(typeid(T));
		return *dynamic_cast<T*>(it->second.get());
	}

	template<typename T>
	inline bool FRCompositeRenderer::HasFeature() const
	{
		static_assert(std::is_base_of<ARenderFeature, T>::value, "T should derive from ARenderFeature");
		auto it = mFeatures.find(typeid(T));
		return it != mFeatures.end();
	}
}