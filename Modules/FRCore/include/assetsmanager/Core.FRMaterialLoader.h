#pragma once

#include <string>

namespace FR
{
	class FRMaterial;

	class FRMaterialLoader
	{
	public:
		FRMaterialLoader() = default;

		static FRMaterial* Create(const std::string& pPath);

		static void Reload(FRMaterial& pMaterial, const std::string& pPath);

		static void Save(FRMaterial& pMaterial, const std::string& pPath);

		static bool Destroy(FRMaterial*& pMaterial);

	public:
		~FRMaterialLoader() = default;

	};
}

