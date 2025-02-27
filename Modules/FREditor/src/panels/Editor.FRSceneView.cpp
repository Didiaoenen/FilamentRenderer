#include "Editor.FRSceneView.h"

#include "Editor.FRInput.h"
#include "Editor.FRApplication.h"
#include "Editor.FREditorActions.h"

#include <Core.FRMesh.h>
#include <Core.FRModel.h>
#include <Core.FRActor.h>
#include <Core.FRScene.h>
#include <Core.FRCompTransform.h>
#include <Core.FRCompRendererable.h>
#include <Core.FRSceneManager.h>

#include <MathDefine.h>
#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <imgui_internal.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

using namespace FR::GUI;

namespace
{
	using GroupPair = std::pair<std::string, FRGroup*>;
}

FR::FRSceneView::FRSceneView(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSetting)
	: FRAViewController(ICON_MDI_GAMEPAD_VARIANT " " + pTitle, pOpened, pSetting)
{
	mView.SetName("SceneView");
	mView.SetFrustumCullingEnabled(false);
	mView.SetPostProcessingEnabled(false);

	ImGuizmo::Enable(true);
	ImGuizmo::SetGizmoSizeClipSpace(0.2f);

	auto& ddTarget = mImage->AddPlugin<FRPluginTarget<GroupPair>>("File");
	{
		ddTarget.DataReceivedEvent += [this](auto pData)
			{
				std::string path = pData.first;
				switch (FRPathUtils::GetFileType(path))
				{
					case EFileType::SCENE:
						//FRServiceLocator::Get<FREditorActions>().LoadSceneFromDisk(path);
						break;
					case EFileType::MODEL:
						GetService(FREditorActions).CreateActorWithModel(path, true);
						break;
					case EFileType::OZZMODEL:
						GetService(FREditorActions).CreateActorWithModel(path, true);
						break;
				}
			};
	}
}

void FR::FRSceneView::Update()
{
	FRAViewController::Update();

	if (IsHovered() && !FRInput::GetKeyDown(EKeyCode::ClickRight))
	{
		if (FRInput::GetKeyDown(EKeyCode::W))
		{
			mCurrentOperation = ImGuizmo::OPERATION::TRANSLATE;
		}

		if (FRInput::GetKeyDown(EKeyCode::E))
		{
			mCurrentOperation = ImGuizmo::OPERATION::ROTATE;
		}

		if (FRInput::GetKeyDown(EKeyCode::R))
		{
			mCurrentOperation = ImGuizmo::OPERATION::SCALE;
		}
	}

	HandleActorPicking();
}

FR::FRScene* FR::FRSceneView::GetScene()
{
	return FRSceneManager::Instance()->GetCurrentScene();
}

void FR::FRSceneView::DrawGizmo()
{
	auto offset = mViewportOffset;

	auto camera = GetCamera();
	auto windowSize = GetSafeSize();
	glm::mat4 view = camera->CalculateViewMatrix();
	glm::mat4 proj = camera->CalculateProjectionMatrix(windowSize.x, windowSize.y);

	glm::vec3 skew;
	glm::vec4 perspective;
	
	float delta[16];
	glm::mat4 model(1.0f);
	FRCompTransform* transform = nullptr;
	auto sceneViewPosition = GetPosition() + offset;

	ImGuizmo::SetOrthographic(false);

	ImGuizmo::SetDrawlist();

	ImGuizmo::SetRect(sceneViewPosition.x, sceneViewPosition.y, windowSize.x, windowSize.y);

	if (mHighlightedActor)
	{
		transform = mHighlightedActor->GetComponent<FRCompTransform>();
		auto& worldMatrix = transform->GetWorldMatrix();
		model = worldMatrix;

		ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(proj), mCurrentOperation, ImGuizmo::LOCAL, glm::value_ptr(model), delta, nullptr);
	}

	if (ImGuizmo::IsUsing())
	{
		glm::vec3 localScale;
		glm::quat localRotation;
		glm::vec3 localPosition;

		glm::decompose(model, localScale, localRotation, localPosition, skew, perspective);

		if (mCurrentOperation == ImGuizmo::SCALE)
		{
			transform->SetWorldScale(localScale);
		}
		else if (mCurrentOperation == ImGuizmo::ROTATE)
		{
			transform->SetWorldRotation(localRotation);
		}
		else if (mCurrentOperation == ImGuizmo::TRANSLATE)
		{
			transform->SetWorldPosition(localPosition);
		}
	}

	auto viewManipulateTop = GetPosition().y + offset.y;
	auto viewManipulateRight = GetPosition().x + GetSize().x;
	auto distance = glm::distance(camera->GetPosition(), transform ? transform->GetWorldPosition() : vec3f::zero);

	auto identity = glm::mat4(1.0);
	ImGuizmo::ViewManipulate(glm::value_ptr(view), glm::value_ptr(proj), ImGuizmo::OPERATION::ROTATE_SCREEN, ImGuizmo::MODE::WORLD, glm::value_ptr(identity), 5, { viewManipulateRight - 100.0f, viewManipulateTop }, { 100.0f, 100.0f }, 0x10101010);

	auto inversed = glm::inverse(view);
	auto origin = camera->GetOriginMatrix();
	camera->SetRotation(glm::quat(inversed * origin));
}

void FR::FRSceneView::HandleActorPicking()
{
	FRActor* selectedActor = nullptr;

	if (GetService(FREditorActions).IsAnyActorSelected())
	{
		mHighlightedActor = GetService(FREditorActions).GetSelectedActor();
	}
	else
	{
		mHighlightedActor = selectedActor;
	}

	if (IsHovered())
	{
		if (!ImGuizmo::IsUsing() && !ImGuizmo::GetHoveredOperation() && FRInput::GetKeyDown(EKeyCode::ClickLeft))
		{
			auto safeSize = GetSafeSize();
			glm::vec2 offsetPosition = FRApplication::GuiHelper()->GetMousePositionRelativeToWindow() - GetPosition();
			glm::vec2 screenPos = { offsetPosition.x, safeSize.y + 22.0f - offsetPosition.y };

			if (screenPos.x > safeSize.x - 100.0f && screenPos.y > safeSize.y - 100.0f)
			{
				return;
			}

			mHighlightedActor = nullptr;

			float closestDist = FLT_MAX;
			Ray ray = GetCamera()->ClickPointToRay(screenPos);
			for (const auto& modelRenderer : GetScene()->GetFastAccessComponents().modelRenderers)
			{
				auto& renderable = modelRenderer->GetRenderable();
				for (const auto& mesh : renderable.GetMeshes())
				{
					auto transform = modelRenderer->owner.GetComponent<FRCompTransform>();

					auto worldMatrix = transform->GetWorldMatrix();
					auto bbx = mesh->boundingBox.Transformed(worldMatrix);

					float distance = FLT_MAX;
					ray.Intersects(bbx, distance);
					if (distance < closestDist)
					{
						closestDist = distance;
						mHighlightedActor = &modelRenderer->owner;
						break;
					}
				}
			}
		}

		if (mHighlightedActor)
		{
			GetService(FREditorActions).SelectActor(mHighlightedActor);
		}
		else
		{
			GetService(FREditorActions).UnselectActor();
		}
	}
}
