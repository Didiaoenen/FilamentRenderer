#include "Core.FRCompTransform.h"

#include "Core.FRGuiDrawer.h"
#include "Core.FRSerializer.h"

#include <MathExtension.h>

FR::FRCompTransform::FRCompTransform(FRActor& pOwner)
	: FRComponent(pOwner)
{
}

const std::string FR::FRCompTransform::GetName()
{
	return ICON_MDI_VECTOR_LINE " Transform";
}

FR::FRComponent::EComponentType FR::FRCompTransform::GetType()
{
	return FRComponent::EComponentType::TRANSFORM;
}

void FR::FRCompTransform::SetParent(FRCompTransform& pParent)
{
	mTransform.SetParent(pParent.GetFRTransform());
}

bool FR::FRCompTransform::RemoveParent()
{
	return mTransform.RemoveParent();
}

void FR::FRCompTransform::SetLocalPosition(const glm::vec3& pNewPosition)
{
	mTransform.SetLocalPosition(pNewPosition);
}

void FR::FRCompTransform::SetLocalRotation(const glm::quat& pNewRotation)
{
	mTransform.SetLocalRotation(pNewRotation);
}

void FR::FRCompTransform::SetLocalScale(const glm::vec3& pNewScale)
{
	mTransform.SetLocalScale(pNewScale);
}

void FR::FRCompTransform::SetWorldPosition(const glm::vec3& pNewPosition)
{
	mTransform.SetWorldPosition(pNewPosition);
}

void FR::FRCompTransform::SetWorldRotation(const glm::quat& pNewRotation)
{
	mTransform.SetWorldRotation(pNewRotation);
}

void FR::FRCompTransform::SetWorldScale(const glm::vec3& pNewScale)
{
	mTransform.SetWorldScale(pNewScale);
}

void FR::FRCompTransform::TranslateLocal(const glm::vec3& pTranslation)
{
	mTransform.TranslateLocal(pTranslation);
}

void FR::FRCompTransform::RotateLocal(const glm::quat& pRotation)
{
	mTransform.RotateLocal(pRotation);
}

void FR::FRCompTransform::ScaleLocal(const glm::vec3& pScale)
{
	mTransform.ScaleLocal(pScale);
}

const glm::vec3& FR::FRCompTransform::GetLocalPosition() const
{
	return mTransform.GetLocalPosition();
}

const glm::quat& FR::FRCompTransform::GetLocalRotation() const
{
	return mTransform.GetLocalRotation();
}

const glm::vec3& FR::FRCompTransform::GetLocalScale() const
{
	return mTransform.GetLocalScale();
}

const glm::vec3& FR::FRCompTransform::GetWorldPosition() const
{
	return mTransform.GetWorldPosition();
}

const glm::quat& FR::FRCompTransform::GetWorldRotation() const
{
	return mTransform.GetWorldRotation();
}

const glm::vec3& FR::FRCompTransform::GetWorldScale() const
{
	return mTransform.GetWorldScale();
}

const glm::mat4& FR::FRCompTransform::GetLocalMatrix() const
{
	return mTransform.GetLocalMatrix();
}

const glm::mat4& FR::FRCompTransform::GetWorldMatrix() const
{
	return mTransform.GetWorldMatrix();
}

glm::vec3 FR::FRCompTransform::GetWorldForward() const
{
	return mTransform.GetWorldForward();
}

glm::vec3 FR::FRCompTransform::GetWorldUp() const
{
	return mTransform.GetWorldUp();
}

glm::vec3 FR::FRCompTransform::GetWorldRight() const
{
	return mTransform.GetWorldRight();
}

glm::vec3 FR::FRCompTransform::GetLocalForward() const
{
	return mTransform.GetLocalForward();
}

glm::vec3 FR::FRCompTransform::GetLocalUp() const
{
	return mTransform.GetLocalUp();
}

glm::vec3 FR::FRCompTransform::GetLocalRight() const
{
	return mTransform.GetLocalRight();
}

void FR::FRCompTransform::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompTransform::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompTransform::OnInspector(FRWidgetContainer& pRoot)
{
	auto getRotation = [this]()
		{
			glm::mat4 mat4 = glm::mat4(GetLocalRotation());
			glm::vec3 vec3 = MatrixToEuler(mat4);
			vec3 = glm::degrees(vec3);
			return vec3;
		};

	auto setRotation = [this](glm::vec3 result)
		{
			auto ryp = glm::radians(result);
			SetLocalRotation(glm::quat(glm::eulerAngleYXZ(ryp.y, ryp.x, ryp.z)));
		};

	FRGuiDrawer::DrawVec3(pRoot, "Position", std::bind(&FRCompTransform::GetLocalPosition, this), std::bind(&FRCompTransform::SetLocalPosition, this, std::placeholders::_1), 0.01f);

	FRGuiDrawer::DrawVec3(pRoot, "Rotation", getRotation, setRotation, 0.01f);

	FRGuiDrawer::DrawVec3(pRoot, "Scale", std::bind(&FRCompTransform::GetLocalScale, this), std::bind(&FRCompTransform::SetLocalScale, this, std::placeholders::_1), 0.01f);
}

FR::FRTransform& FR::FRCompTransform::GetFRTransform()
{
	return mTransform;
}