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
	class AnimationClip;

	class FROzzAnimationLoader
	{
	public:
		static AnimationClip* Create(const std::string& pFilePath);

		static void Reload(AnimationClip& pAniamtin, const std::string& pFilePath);

		static void Destroy(AnimationClip*& pAniamtin);

	private:
		static bool LoadAnimation(const std::string& pFileName, ozz::animation::Animation& pAnimation);

	};
}

