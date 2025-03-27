#include "Core.FRCompAniTest.h"
#include "Core.FROzzSkeletonManager.h"
#include "Core.FROzzAnimationManager.h"

#include "Core.FRActor.h"
#include "Core.FRInput.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRCompAnimancer.h"

#include "AnimationClip.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <typeinfo>

FR::FRCompAniTest::FRCompAniTest(FRActor& pOwner)
    : FRComponent(pOwner)
{
	mClips.resize(2);
}

void FR::FRCompAniTest::OnStart()
{
}

void FR::FRCompAniTest::OnUpdate(float pDeltaTime)
{
	if (auto animancer = owner.GetComponent<FRCompAnimancer>())
	{
		if (FRInput::GetKey(EKeyCode::W))
		{
			if (mClips[1])
			{
				animancer->Play(mClips[1], 0.25f);
			}
		}
		else
		{
			if (mClips[0])
			{
				animancer->Play(mClips[0], 0.25f);
			}
		}
	}
}

void FR::FRCompAniTest::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAniTest::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAniTest::OnInspector(GUI::FRWidgetContainer& pRoot)
{
	if (mClips.size() > 0)
	{
		FRGuiDrawer::CreateTitle(pRoot, "AnimationClips");

		for (int i = 0; i < mClips.size(); i++)
		{
			FRGuiDrawer::DrawItemSelect(pRoot, mClips[i] ? mClips[i]->path : "", FRItemSelect::EItemType::ANIMATION, this, &FRCompAniTest::DataReceivedChangeCallback, i);
		}
	}
}

const std::string FR::FRCompAniTest::GetName()
{
    return std::string(typeid(*this).name());
}

FR::FRComponent::EComponentType FR::FRCompAniTest::GetType()
{
    return EComponentType();
}

void FR::FRCompAniTest::DataReceivedChangeCallback(std::string& pContext, std::pair<std::string, GUI::FRGroup*> pDataReceived, int pIndex)
{
	if (FRPathUtils::GetFileType(pDataReceived.first) == EFileType::ANIMATION)
	{
		if (auto resource = GetService(FROzzAnimationManager).GetResource(pDataReceived.first))
		{
			mClips[pIndex] = resource;
			pContext = pDataReceived.first;
		}
	}
}
