#include "Core.FRComponent.h"
#include "Core.FRActor.h"

FR::FRComponent::FRComponent(FRActor& pOwner)
	: owner(pOwner)
{
}

FR::FRComponent::~FRComponent()
{
	if (owner.IsActive())
	{
		OnDisable();
		OnDestroy();
	}
}
