#include "Core.FRCompAnimator.h"
#include "Core.FROzzSkeletonManager.h"
#include "Core.FROzzAnimationManager.h"

#include "Core.FRMesh.h"
#include "Core.FRActor.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRCompRendererable.h"

#include "Animation.h"
#include "AnimationClip.h"
#include "SkeletonRig.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

int i = 0;

FR::FRCompAnimator::FRCompAnimator(FRActor& pOwner)
	: FRComponent(pOwner)
{
	//mMotions.resize(1);
}

const std::string FR::FRCompAnimator::GetName()
{
	return ICON_MDI_MERGE " Animator";
}

FR::FRComponent::EComponentType FR::FRCompAnimator::GetType()
{
	return FRComponent::EComponentType::ANIMATOR;
}

FR::Animator& FR::FRCompAnimator::GetAnimator()
{
	return mAnimator;
}

void FR::FRCompAnimator::OnStart()
{
	if (auto modelRenderer = owner.GetComponent<FRCompRendererable>())
	{
		mAnimator.SetSkeletonRig(mSkeletonRig);

		if (mMotions.size() > 0 && mMotions[0])
		{
			mAnimator.Play(mMotions[0]);
		}
	}
}

void FR::FRCompAnimator::OnUpdate(float pDeltaTime)
{
	if (mSkeletonRig)
	{
		mAnimator.Update(pDeltaTime);

		if (auto modelRenderer = owner.GetComponent<FRCompRendererable>())
		{
			auto& renderable = modelRenderer->GetRenderable();
			ozz::vector<ozz::math::Float4x4> skinningMat;
			for (auto& mesh : renderable.GetMeshes())
			{
				if (mesh->jointRemaps.size() > 0)
				{
					skinningMat.resize(mesh->jointRemaps.size());
					for (size_t i = 0; i < mesh->jointRemaps.size(); i++)
					{
						skinningMat[i] = mAnimator.GetJointWorldMatNoScale(mesh->jointRemaps[i]) * MathConvert::ToOzzMat4(mesh->inverseBindPoses[i]);
					}

					std::vector<glm::mat4> temps;
					for (size_t i = 0; i < skinningMat.size(); i++)
					{
						temps.push_back(MathConvert::ToGlmMat4(skinningMat[i]));
					}

					renderable.UpdateMeshSkinning(mesh, temps);
				}
			}
		}
	}
}

void FR::FRCompAnimator::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAnimator::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAnimator::OnInspector(FRWidgetContainer& pRoot)
{
	FRGuiDrawer::CreateTitle(pRoot, "Skeleton");

	FRGuiDrawer::DrawItemSelect(pRoot, mSkeletonRig ? mSkeletonRig->path : "", FRItemSelect::EItemType::SKELETON, this, &FRCompAnimator::DataReceivedChangeCallback, 0);

	if (mMotions.size() > 0)
	{
		FRGuiDrawer::CreateTitle(pRoot, "Animation");

		for (int i = 0; i < mMotions.size(); i++)
		{
			FRGuiDrawer::DrawItemSelect(pRoot, mMotions[i] ? mMotions[i]->path : "", FRItemSelect::EItemType::ANIMATION, this, &FRCompAnimator::DataReceivedChangeCallback, i);
		}
	}
}

void FR::FRCompAnimator::DataReceivedChangeCallback(std::string& pContext, std::pair<std::string, FRGroup*> pDataReceived, int pIndex)
{
	if (FRPathUtils::GetFileType(pDataReceived.first) == EFileType::ANIMATION)
	{
		if (auto resource = GetService(FROzzAnimationManager).GetResource(pDataReceived.first))
		{
			if (!mMotions[pIndex])
			{
				mMotions[pIndex] = new Animation(resource);
			}
			else
			{
				if (auto animtion = dynamic_cast<Animation*>(mMotions[pIndex]))
				{
					animtion->clip = resource;
				}
			}

			pContext = pDataReceived.first;
		}
	}
	else if (FRPathUtils::GetFileType(pDataReceived.first) == EFileType::OZZSKELETON)
	{
		if (auto resource = GetService(FROzzSkeletonManager).GetResource(pDataReceived.first))
		{
			mSkeletonRig = resource;
			pContext = pDataReceived.first;
		}
	}
}

FR::FRCompAnimator::~FRCompAnimator()
{
	for (auto& motion : mMotions)
	{
		if (motion)
		{
			delete motion; motion = nullptr;
		}
	}
}