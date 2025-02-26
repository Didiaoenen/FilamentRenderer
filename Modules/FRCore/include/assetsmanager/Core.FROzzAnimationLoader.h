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

		static void Reload(Animation& pAniamtin, const std::string& pFilePath);

		static void Destroy(Animation*& pAniamtin);

	private:
		static bool LoadAnimation(const std::string& pFileName, ozz::animation::Animation& pAnimation);



	};
}

