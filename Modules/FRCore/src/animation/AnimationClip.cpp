#include "AnimationClip.h"

FR::AnimationClip::AnimationClip(ozz::animation::Animation&& pAnimation)
	: mAnimation(std::move(pAnimation))
{
}

float FR::AnimationClip::GetDuration()
{
	return mAnimation.duration();
}

const std::string FR::AnimationClip::GetName()
{
	return std::string(mAnimation.name());
}

ozz::animation::Animation& FR::AnimationClip::NativePtr()
{
	return mAnimation;
}

FR::AnimationClip::~AnimationClip() = default;