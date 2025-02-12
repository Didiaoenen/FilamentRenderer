#include "Core.FRCompAnimator.h"

#include "Animation.h"
#include "SkeletonRig.h"
#include "AnimationManager.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "Core.FRActor.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRCompModelRenderer.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRCompAnimator::FRCompAnimator(FRActor& pActor)
	: FRComponent(pActor)
{
	mMotions.resize(1);
}

const std::string FR::FRCompAnimator::GetName()
{
	return ICON_MDI_MERGE " Animator";
}

FR::FRComponent::EComponentType FR::FRCompAnimator::GetType()
{
	return FRComponent::EComponentType::ANIMATOR;
}

void FR::FRCompAnimator::OnStart()
{
	if (FRCompModelRenderer* modelRenderer = owner.GetComponent<FRCompModelRenderer>())
	{
		if (FRModel* model = modelRenderer->GetModel(); mMotions[0])
		{
			mSkeletonRig = model->GetSkeletonRig();
			mAnimator.SetSkeletonRig(mSkeletonRig);
			mAnimator.Play(mMotions[0]);
		}
	}
}

void FR::FRCompAnimator::OnUpdate(float pDeltaTime)
{
	if (mSkeletonRig)
	{
		mAnimator.Update(pDeltaTime);

		if (FRCompModelRenderer* modelRenderer = owner.GetComponent<FRCompModelRenderer>())
		{
			if (FRModel* model = modelRenderer->GetModel())
			{
				ozz::vector<ozz::math::Float4x4> skinningMat;
				for (auto& mesh : model->GetMeshes())
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

						mesh->UpdateSkinning(temps);
					}
					else
					{
						if (mesh->attachmentJoint >= 0)
						{
							skinningMat.resize(1);
							int32_t attachmentJoint = mesh->attachmentJoint;
							skinningMat[0] = mAnimator.GetJointWorldMatNoScale(attachmentJoint);
							mesh->UpdateAttachment(MathConvert::ToGlmMat4(skinningMat[0]));
						}
					}
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
	FRGuiDrawer::CreateTitle(pRoot, "Animation").lineBreak = false;

	for (int i = 0; i < mMotions.size(); i++)
	{
		FRGuiDrawer::DrawItemSelect(pRoot, mMotions[i] ? mMotions[i]->path : "", FRItemSelect::EItemType::ANIMATION, this, &FRCompAnimator::DataReceivedChangeCallback, i);
	}
}

void FR::FRCompAnimator::DataReceivedChangeCallback(std::string& pContext, std::pair<std::string, FRGroup*> pDataReceived, int pIndex)
{
	if (FRPathUtils::GetFileType(pDataReceived.first) == EFileType::ANIMATION)
	{
		if (auto resource = GetService(AnimationManager).GetResource(pDataReceived.first))
		{
			mMotions[pIndex] = resource;
			pContext = pDataReceived.first;
		}
	}
}