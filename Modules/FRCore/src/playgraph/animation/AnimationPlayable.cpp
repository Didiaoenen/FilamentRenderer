#include "AnimationPlayable.h"

#include "APlayableParent.h"
#include "AnimationPlayableOutput.h"

FR::AnimationPlayable* FR::AnimationPlayable::GetRootPlayable()
{
	AnimationPlayable* root = nullptr;

	APlayableParent* tempParent = parent;

	while (tempParent)
	{
		if (auto playable = dynamic_cast<AnimationPlayable*>(tempParent))
		{
			root = playable;
			tempParent = playable->parent;
		}
	}

	return root;
}

FR::AnimationPlayableOutput* FR::AnimationPlayable::GetOutput()
{
	return dynamic_cast<AnimationPlayableOutput*>(mOutput);
}

void FR::AnimationPlayable::SetOutput(AnimationPlayableOutput* pOutput)
{
    mOutput = pOutput;
}

const ozz::vector<ozz::math::SoaTransform>& FR::AnimationPlayable::GetLocalTrans()
{
	return mLocalTrans;
}
