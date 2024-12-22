#pragma once

#include <string>
#include <vector>

namespace FR
{
	class FRShader;
	struct FRPropInfo;

	class FRShaderLoader
	{
	public:
		FRShaderLoader() = default;

		static FRShader* Create(const std::string& pFilePath);

		static void	Recompile(FRShader& pShader, const std::string& pFilePath);

		static bool Destroy(FRShader*& pShader);

	public:
		~FRShaderLoader() = default;

	private:
		static std::vector<FRPropInfo> ParseProperty(const std::string& pFilePath);

	};
}

