#include "Core.FRCamera.h"

#include <MathDefine.h>
#include <FRCameraWarp.h>
#include <FREngineWarp.h>
#include <FRFilamentHelper.h>

FR::FRCamera::FRCamera(FREntityWarp* pEntity, FROptRef<FRTransform> pTransform)
	: FREntity(pEntity, pTransform)
{
	mCamera = FRFilamentHelper::CreateCamera(mEntity);
	mCamera->SetExposure(16.0f, 1 / 125.0f, 100.0f);
	mCamera->SetScaling({ 1.0, 1.0 });
}

void FR::FRCamera::CacheMatrices(uint16_t pWidth, uint16_t pHeight)
{
	CacheProjectionMatrix(pWidth, pHeight);
	CacheViewMatrix();
}

void FR::FRCamera::CacheProjectionMatrix(uint16_t pWindowWidth, uint16_t pWindowHeight)
{
	mProjectionMatrix = CalculateProjectionMatrix(pWindowWidth, pWindowHeight);
}

void FR::FRCamera::CacheViewMatrix()
{
	mViewMatrix = CalculateViewMatrix();
}

const glm::vec3& FR::FRCamera::GetPosition() const
{
	return mTransform->GetWorldPosition();
}

const glm::quat& FR::FRCamera::GetRotation() const
{
	return mTransform->GetWorldRotation();
}

const glm::mat4& FR::FRCamera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}

const glm::mat4& FR::FRCamera::GetViewMatrix() const
{
	return mViewMatrix;
}

void FR::FRCamera::SetPosition(const glm::vec3& pPosition)
{
	mTransform->SetWorldPosition(pPosition);
}

void FR::FRCamera::SetRotation(const glm::quat& pRotation)
{
	mTransform->SetWorldRotation(pRotation);
}

void FR::FRCamera::SetViewport(const glm::vec4& pViewport)
{
	mViewport = pViewport;
}

glm::mat4 FR::FRCamera::CalculateProjectionMatrix(uint16_t pWidth, uint16_t pHeight) const
{
	const auto ratio = pWidth / static_cast<float>(pHeight);

	switch (projectionMode)
	{
	case EProjectionMode::ORTHOGRAPHIC:
	{
		const auto right = size * ratio;
		const auto left = -right;

		const auto bottom = -size;
		const auto top = -bottom;

		mCamera->SetProjection(FRCameraWarp::EProjection::ORTHO, left, right, bottom, top, near, far);
		return mCamera->GetProjectionMatrix();
	}

	case EProjectionMode::PERSPECTIVE:
	{
		mCamera->SetProjection(fov, ratio, near, far, FRCameraWarp::EFov::VERTICAL);
		return mCamera->GetProjectionMatrix();
	}
	default:
		return glm::identity<glm::mat4>();
	}
}

glm::mat4 FR::FRCamera::CalculateViewMatrix() const
{
	const auto& position = mTransform->GetWorldPosition();
	const auto& forward = mTransform->GetWorldForward();
	const auto& up = mTransform->GetWorldUp();
	mCamera->LookAt(position, position + forward, up);
	return mCamera->GetViewMatrix();
}

const FR::Ray FR::FRCamera::ClickPointToRay(glm::vec2 pPosition)
{
	glm::vec3 start = mTransform->GetWorldPosition();
	glm::vec3 direction = GetRayDirection(pPosition, 1.0f);
	return Ray(start, direction);
}

glm::vec3 FR::FRCamera::GetRayDirection(const glm::vec2& pScreenPos, const float z) const
{
	const glm::vec3 gaze = glm::normalize(mTransform->GetWorldForward());
	const glm::vec3 right = glm::normalize(glm::cross(gaze, mTransform->GetWorldUp()));
	const glm::vec3 upward = glm::cross(right, gaze);
	const float width = mViewport.z;
	const float height = mViewport.w;
	const float fovRad = glm::radians(fov);

	// Remap the grid coordinate into [-1, +1] and shift it to the pixel center.
	const float u = 2.0 * (0.5 + pScreenPos.x) / width - 1.0;
	const float v = 2.0 * (0.5 + pScreenPos.y) / height - 1.0;

	// Compute the tangent of the field-of-view angle as well as the aspect ratio.
	const float tangent = tan(fovRad / 2.0);
	const float aspect = width / height;

	// Adjust the gaze so it goes through the pixel of interest rather than the grid center.
	glm::vec3 dir = gaze;
	if (/*fovDir == filament::Camera::Fov::VERTICAL*/ true)
	{
		dir += right * tangent * u * aspect;
		dir += upward * tangent * v;
	}
	else
	{
		dir += right * tangent * u;
		dir += upward * tangent * v / aspect;
	}

	return normalize(dir);
}

glm::mat4 FR::FRCamera::GetOriginMatrix()
{
	const auto& position = mTransform->GetWorldPosition();
	return glm::lookAt(position, position + vec3f::forward, vec3f::up);
}

FR::FRCameraWarp* FR::FRCamera::NativePtr()
{
	return mCamera;
}

FR::FRCamera::~FRCamera()
{
	FRFilamentHelper::DestroyEntity(mEntity);
}
