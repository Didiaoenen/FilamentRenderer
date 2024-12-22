#pragma once

#include "Core.FRMaterial.h"
#include <FRMaterialInstanceWarp.h>

namespace FR
{
	template<typename T>
	inline const T& FRMaterial::Get(const std::string pKey) const
	{
		for (auto& property : mPropInfos)
		{
			if (property.name == pKey)
			{
				return std::any_cast<T>();
			}
		}
		return T();
	}

	template<typename T>
	inline void FRMaterial::Set(const std::string pKey, const T& pValue)
	{
		if (HasShader())
		{
			for (auto& prop : mPropInfos)
			{
				if (prop.name == pKey)
				{
					prop.data = std::any(pValue);
					return;
				}
			}
		}
	}

	template<typename T>
	void FRMaterial::SetParameter(const std::string& pName, const T& pValue)
	{
		mMaterialInstance->SetParameter<T>(pName, pValue);
	}
}