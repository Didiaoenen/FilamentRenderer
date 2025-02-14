#pragma once

#include <string>

namespace ozz
{
	namespace animation
	{
		class Animation;
	}
}

namespace FR
{
	class Animation;

	class FROzzAnimationLoader
	{
	public:
		static Animation* Create(const std::string& pFilePath);

	private:
		static bool LoadAnimation(const std::string& pFileName, ozz::animation::Animation* pAnimation);

	};
}

