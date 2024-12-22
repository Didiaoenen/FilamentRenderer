#include "Core.FRTransform.h"

#include <MathDefine.h>
#include <MathExtension.h>

FR::FRTransform::FRTransform(glm::vec3 pLocalPosition, glm::quat pLocalRotation, glm::vec3 pLocalScale)
{
	GenerateMatricesLocal(pLocalPosition, pLocalRotation, pLocalScale);
}

void FR::FRTransform::SetParent(FRTransform& pParent)
{
	parent = &pParent;
	UpdateWorldMatrix();
	//m_notificationHandlerID = mParent->Notifier.AddNotificationHandler(std::bind(&FTransform::NotificationHandler, this, std::placeholders::_1));
}

bool FR::FRTransform::RemoveParent()
{
	if (parent != nullptr)
	{
		parent = nullptr;
		UpdateWorldMatrix();
		//mParent->Notifier.RemoveNotificationHandler(m_notificationHandlerID);

		return true;
	}
	return false;
}

void FR::FRTransform::GenerateMatricesWorld(glm::vec3 pPosition, glm::quat pRotation, glm::vec3 pScale)
{
	auto t = glm::identity<glm::mat4>();
	mWorldMatrix = glm::translate(t, pPosition) * glm::mat4(glm::normalize(pRotation)) * glm::scale(t, pScale);
	mWorldPosition = pPosition;
	mWorldRotation = pRotation;
	mWorldScale = pScale;

	UpdateLocalMatrix();
}

void FR::FRTransform::GenerateMatricesLocal(glm::vec3 pPosition, glm::quat pRotation, glm::vec3 pScale)
{
	mLocalMatrix = glm::translate(glm::mat4(1.0f), pPosition) * glm::mat4(normalize(pRotation)) * glm::scale(glm::mat4(1.0f), pScale);
	mLocalPosition = pPosition;
	mLocalRotation = pRotation;
	mLocalScale = pScale;

	UpdateWorldMatrix();
}

void FR::FRTransform::UpdateWorldMatrix()
{
	mWorldMatrix = parent ? parent->mWorldMatrix * mLocalMatrix : mLocalMatrix;
	PreDecomposeWorldMatrix();

	//Notifier.NotifyChildren(Internal::TransformNotifier::ENotification::TRANSFORM_CHANGED);
}

void FR::FRTransform::UpdateLocalMatrix()
{
	mLocalMatrix = parent ? inverse(parent->mWorldMatrix) * mWorldMatrix : mWorldMatrix;
	PreDecomposeLocalMatrix();

	//Notifier.NotifyChildren(Internal::TransformNotifier::ENotification::TRANSFORM_CHANGED);
}

void FR::FRTransform::SetLocalPosition(const glm::vec3& pNewPosition)
{
	GenerateMatricesLocal(pNewPosition, mLocalRotation, mLocalScale);
}

void FR::FRTransform::SetLocalRotation(const glm::quat& pNewRotation)
{
	GenerateMatricesLocal(mLocalPosition, pNewRotation, mLocalScale);
}

void FR::FRTransform::SetLocalScale(const glm::vec3& pNewScale)
{
	GenerateMatricesLocal(mLocalPosition, mLocalRotation, pNewScale);
}

void FR::FRTransform::SetWorldPosition(const glm::vec3& pNewPosition)
{
	GenerateMatricesWorld(pNewPosition, mWorldRotation, mWorldScale);
}

void FR::FRTransform::SetWorldRotation(const glm::quat& pNewRotation)
{
	GenerateMatricesWorld(mWorldPosition, pNewRotation, mWorldScale);
}

void FR::FRTransform::SetWorldScale(const glm::vec3& pNewScale)
{
	GenerateMatricesWorld(mWorldPosition, mWorldRotation, pNewScale);
}

void FR::FRTransform::TranslateLocal(const glm::vec3& pTranslation)
{
	SetLocalPosition(mLocalPosition + pTranslation);
}

void FR::FRTransform::RotateLocal(const glm::quat& pRotation)
{
	SetLocalRotation(mLocalRotation * pRotation);
}

void FR::FRTransform::ScaleLocal(const glm::vec3& pScale)
{
	SetLocalScale({ mLocalScale.x * pScale.x, mLocalScale.y * pScale.y, mLocalScale.z * pScale.z });
}

const glm::vec3& FR::FRTransform::GetLocalPosition() const
{
	return mLocalPosition;
}

const glm::quat& FR::FRTransform::GetLocalRotation() const
{
	return mLocalRotation;
}

const glm::vec3& FR::FRTransform::GetLocalScale() const
{
	return mLocalScale;
}

const glm::vec3& FR::FRTransform::GetWorldPosition() const
{
	return mWorldPosition;
}

const glm::quat& FR::FRTransform::GetWorldRotation() const
{
	return mWorldRotation;
}

const glm::vec3& FR::FRTransform::GetWorldScale() const
{
	return mWorldScale;
}

const glm::mat4& FR::FRTransform::GetLocalMatrix() const
{
	return mLocalMatrix;
}

const glm::mat4& FR::FRTransform::GetWorldMatrix() const
{
	return mWorldMatrix;
}

glm::vec3 FR::FRTransform::GetWorldForward() const
{
	return mWorldRotation * vec3f::forward;
}

glm::vec3 FR::FRTransform::GetWorldUp() const
{
	return mWorldRotation * vec3f::up;
}

glm::vec3 FR::FRTransform::GetWorldRight() const
{
	return mWorldRotation * vec3f::right;
}

glm::vec3 FR::FRTransform::GetLocalForward() const
{
	return mLocalRotation * vec3f::forward;
}

glm::vec3 FR::FRTransform::GetLocalUp() const
{
	return mLocalRotation * vec3f::up;
}

glm::vec3 FR::FRTransform::GetLocalRight() const
{
	return mLocalRotation * vec3f::right;
}

void FR::FRTransform::PreDecomposeWorldMatrix()
{
	glm::mat4 worldMaterix = glm::transpose(mWorldMatrix);

	mWorldPosition.x = worldMaterix[0][3];
	mWorldPosition.y = worldMaterix[1][3];
	mWorldPosition.z = worldMaterix[2][3];

	glm::vec3 columns[3] =
	{
		{ worldMaterix[0][0], worldMaterix[1][0], worldMaterix[2][0]},
		{ worldMaterix[0][1], worldMaterix[1][1], worldMaterix[2][1]},
		{ worldMaterix[0][2], worldMaterix[1][2], worldMaterix[2][2]},
	};

	mWorldScale.x = glm::length(columns[0]);
	mWorldScale.y = glm::length(columns[1]);
	mWorldScale.z = glm::length(columns[2]);

	if (mWorldScale.x)
	{
		columns[0] /= mWorldScale.x;
	}
	if (mWorldScale.y)
	{
		columns[1] /= mWorldScale.y;
	}
	if (mWorldScale.z)
	{
		columns[2] /= mWorldScale.z;
	}

	glm::mat3 rotationMatrix(
		columns[0].x, columns[1].x, columns[2].x,
		columns[0].y, columns[1].y, columns[2].y,
		columns[0].z, columns[1].z, columns[2].z);

	mWorldRotation = glm::quat(rotationMatrix);
}

void FR::FRTransform::PreDecomposeLocalMatrix()
{
	glm::mat4 localMaterix = glm::transpose(mLocalMatrix);

	mLocalPosition.x = localMaterix[0][3];
	mLocalPosition.y = localMaterix[1][3];
	mLocalPosition.z = localMaterix[2][3];

	glm::vec3 columns[3] =
	{
		{ localMaterix[0][0], localMaterix[1][0], localMaterix[2][0]},
		{ localMaterix[0][1], localMaterix[1][1], localMaterix[2][1]},
		{ localMaterix[0][2], localMaterix[1][2], localMaterix[2][2]},
	};

	mLocalScale.x = length(columns[0]);
	mLocalScale.y = length(columns[1]);
	mLocalScale.z = length(columns[2]);

	if (mLocalScale.x)
	{
		columns[0] /= mLocalScale.x;
	}
	if (mLocalScale.y)
	{
		columns[1] /= mLocalScale.y;
	}
	if (mLocalScale.z)
	{
		columns[2] /= mLocalScale.z;
	}

	glm::mat3 rotationMatrix(
		columns[0].x, columns[1].x, columns[2].x,
		columns[0].y, columns[1].y, columns[2].y,
		columns[0].z, columns[1].z, columns[2].z);

	mLocalRotation = glm::quat(rotationMatrix);
}
