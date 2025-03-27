#include "APlayableOutput.h"

#include "APlayable.h"

void FR::APlayableOutput::SetSourcePlayable(APlayable* pPlayable)
{
	mSourcePlayable = pPlayable;
}

FR::APlayable* FR::APlayableOutput::GetSourcePlayable() const
{
	return mSourcePlayable;
}