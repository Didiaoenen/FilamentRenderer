#include "Editor.FRCameraController.h"

#include "Editor.FRInput.h"

#include <Core.FRActor.h>
#include <Core.FRCompTransform.h>

#include <MathDefine.h>
#include <Tools.FRTimer.h>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace FR
{
	bool mFirstMouse = true;
	double mLastMousePosX = 0.0;
	double mLastMousePosY = 0.0;
	float mCameraDragSpeed = 0.03f;
	float mCameraOrbitSpeed = 0.5f;
	float mCameraMoveSpeed = 5.0f;
	float mMouseSensitivity = 0.12f;
	float mFocusLerpCoefficient = 8.0f;

	const glm::vec3 kDefaultClearColor{ 0.098f, 0.098f, 0.098f };

	float GetActorFocusDist(FRActor* pActor)
	{
		float distance = 4.0f;

		if (pActor->IsActive())
		{
			for (auto child : pActor->GetChildren())
			{
				distance = std::max(distance, GetActorFocusDist(child));
			}
		}

		return distance;
	}
	
	glm::vec3 RemoveRoll(const glm::vec3& pYPR)
	{
		glm::vec3 result = pYPR;

		if (result.z >= 179.0f || result.z <= -179.0f)
		{
			result.x += result.z;
			result.y = 180.0f - result.y;
			result.z = 0.0f;
		}

		if (result.x > 180.0f)
			result.x -= 360.0f;

		if (result.x < -180.0f)
			result.x += 360.0f;

		return result;
	}
}

FR::FRCameraController::FRCameraController()
{
	mCamera.clearColor = kDefaultClearColor;
}

void FR::FRCameraController::HandleInputs()
{
	UpdateMouseState();

	if (auto target = GetTargetActor())
	{
		auto targetPos = target->transform.GetWorldPosition();

		float dist = GetActorFocusDist(target);

		if (FRInput::GetKeyDown(EKeyCode::F))
		{
			MoveToTarget(target);
		}

		auto focusObjectFromAngle = [this, &targetPos, &dist](const glm::vec3& offset)
			{
				auto camPos = targetPos + offset * dist;
				auto direction = normalize(targetPos - camPos);
				mCamera.SetRotation(glm::quatLookAt(direction, abs(direction.y) == 1.0f ? vec3f::right : vec3f::up));
				mCameraDestinations.push({ camPos, mCamera.GetRotation() });
			};

		if (FRInput::GetKeyDown(EKeyCode::ArrowUp)) focusObjectFromAngle(vec3f::up);
		if (FRInput::GetKeyDown(EKeyCode::ArrowDown)) focusObjectFromAngle(-vec3f::up);
		if (FRInput::GetKeyDown(EKeyCode::ArrowLeft)) focusObjectFromAngle(-vec3f::right);
		if (FRInput::GetKeyDown(EKeyCode::ArrowRight)) focusObjectFromAngle(vec3f::right);
	}

	if (!mCameraDestinations.empty())
	{
		mCurrentMovementSpeed = {};

		while (mCameraDestinations.size() != 1)
		{
			mCameraDestinations.pop();
		}

		auto& [destPos, destRotation] = mCameraDestinations.front();

		float t = mFocusLerpCoefficient * FRTimer::GetDeltaTimeSec();

		if (glm::distance(mCamera.GetPosition(), destPos) <= 0.03f)
		{
			mCamera.SetPosition(destPos);
			mCamera.SetRotation(destRotation);
			mCameraDestinations.pop();
		}
		else
		{
			mCamera.SetPosition(glm::lerp(mCamera.GetPosition(), destPos, t));
			mCamera.SetRotation(glm::lerp(mCamera.GetRotation(), destRotation, t));
		}
	}
	else
	{
		if (mRightMousePressed || mMiddleMousePressed || mLeftMousePressed)
		{
			glm::vec2 mousePos = FRInput::GetMousePosition();

			bool wasFirstMouse = mFirstMouse;

			if (mFirstMouse)
			{
				mLastMousePosX = mousePos.x;
				mLastMousePosY = mousePos.y;
				mFirstMouse = false;
			}

			glm::vec2 mouseOffset
			{
				static_cast<float>(mousePos.x - mLastMousePosX),
				static_cast<float>(mLastMousePosY - mousePos.y)
			};

			mLastMousePosX = mousePos.x;
			mLastMousePosY = mousePos.y;

			if (mRightMousePressed)
			{
				HandleCameraFPSMouse(mouseOffset, wasFirstMouse);
			}
			else
			{
				if (mMiddleMousePressed)
				{
					if (FRInput::GetKey(EKeyCode::AltLeft))
					{
						if (auto target = GetTargetActor())
						{
							HandleCameraOrbit(target, mouseOffset, wasFirstMouse);
						}
					}
					else
					{
						HandleCameraPanning(mouseOffset, wasFirstMouse);
					}
				}
			}
		}

		HandleCameraZoom();

		HandleCameraFPSKeyboard();
	}
}

void FR::FRCameraController::MoveToTarget(FRActor* pTarget)
{
	mCameraDestinations.push({
		pTarget->transform.GetWorldPosition() - mCamera.GetRotation() * vec3f::forward * GetActorFocusDist(pTarget), mCamera.GetRotation()
	});
}

void FR::FRCameraController::SetSpeed(float pSpeed)
{
	mCameraMoveSpeed = pSpeed;
}

float FR::FRCameraController::GetSpeed() const
{
	return mCameraMoveSpeed;
}

void FR::FRCameraController::SetPosition(const glm::vec3& pPosition)
{
	mCamera.SetPosition(pPosition);
}

void FR::FRCameraController::SetRotation(const glm::quat& pRotation)
{
	mCamera.SetRotation(pRotation);
}

const glm::vec3& FR::FRCameraController::GetPosition() const
{
	return mCamera.GetPosition();
}

const glm::quat& FR::FRCameraController::GetRotation() const
{
	return mCamera.GetRotation();
}

bool FR::FRCameraController::IsRightMousePressed() const
{
	return mRightMousePressed;
}

void FR::FRCameraController::LockTargetActor(FRActor* pActor)
{
	mLockedActor = pActor;
}

void FR::FRCameraController::UnlockTargetActor()
{
	mLockedActor = nullptr;
}

FR::FRCamera* FR::FRCameraController::GetCamera()
{
	return &mCamera;
}

FR::FRCameraController::~FRCameraController()
{

}

FR::FRActor* FR::FRCameraController::GetTargetActor() const
{
	return mLockedActor;
}

void FR::FRCameraController::HandleCameraPanning(const glm::vec2& pMouseOffset, bool pFirstMouse)
{
	auto mouseOffset = pMouseOffset * mCameraDragSpeed;
	mCamera.SetPosition(mCamera.GetPosition() + mCamera.transform->GetWorldRight() * mouseOffset.x);
	mCamera.SetPosition(mCamera.GetPosition() - mCamera.transform->GetWorldUp() * mouseOffset.y);
}

void FR::FRCameraController::HandleCameraOrbit(FRActor* pTarget, const glm::vec2& pMouseOffset, bool pFirstMouse)
{
	auto mouseOffset = pMouseOffset * mCameraOrbitSpeed;

	if (pFirstMouse)
	{
		mOrbitTarget = &pTarget->transform.GetFRTransform();
		mOrbitStartOffset = -vec3f::forward * glm::distance(mOrbitTarget->GetWorldPosition(), mCamera.GetPosition());
		
		mYPR = RemoveRoll(glm::degrees(glm::eulerAngles(mCamera.GetRotation())));
	}

	mYPR.y += -mouseOffset.x;
	mYPR.x += -mouseOffset.y;
	mYPR.x = std::max(std::min(mYPR.x, 90.0f), -90.0f);

	auto& target = pTarget->transform.GetFRTransform();
	FRTransform pivotTransform(target.GetWorldPosition());
	FRTransform cameraTransform(mOrbitStartOffset);
	cameraTransform.SetParent(pivotTransform);

	auto ypr = glm::radians(mYPR);
	pivotTransform.RotateLocal(glm::quat(glm::eulerAngleYXZ(ypr.y, ypr.x, ypr.z)));
	mCamera.SetPosition(cameraTransform.GetWorldPosition());
	mCamera.SetRotation(cameraTransform.GetWorldRotation());
}

void FR::FRCameraController::HandleCameraFPSMouse(const glm::vec2& pMouseOffset, bool pFirstMouse)
{
	auto mouseOffset = pMouseOffset * mMouseSensitivity;

	if (pFirstMouse)
	{
		mYPR = RemoveRoll(glm::degrees(glm::eulerAngles(mCamera.GetRotation())));
	}

	mYPR.y -= mouseOffset.x;
	mYPR.x += -mouseOffset.y;
	mYPR.x = std::max(std::min(mYPR.x, 90.0f), -90.0f);

	auto ypr = glm::radians(mYPR);
	mCamera.SetRotation(glm::quat(glm::eulerAngleYXZ(ypr.y, ypr.x, ypr.z)));
}

void FR::FRCameraController::HandleCameraZoom()
{
	auto delta = FRInput::GetMouseWheelDelta();
	mCamera.SetPosition(mCamera.GetPosition() + mCamera.transform->GetWorldForward() * delta.y);
}

void FR::FRCameraController::HandleCameraFPSKeyboard()
{
	mTargetSpeed = glm::vec3{};

	if (mRightMousePressed)
	{
		bool run = FRInput::GetKey(EKeyCode::ShiftLeft);
		float velocity = mCameraMoveSpeed * FRTimer::GetDeltaTimeSec() * (run ? 2.0f : 1.0f);

		if (FRInput::GetKey(EKeyCode::W))
		{
			mTargetSpeed += mCamera.transform->GetWorldForward() * velocity;
		}
		if (FRInput::GetKey(EKeyCode::S))
		{
			mTargetSpeed += mCamera.transform->GetWorldForward() * -velocity;
		}
		if (FRInput::GetKey(EKeyCode::A))
		{
			mTargetSpeed += mCamera.transform->GetWorldRight() * velocity;
		}
		if (FRInput::GetKey(EKeyCode::D))
		{
			mTargetSpeed += mCamera.transform->GetWorldRight() * -velocity;
		}
		if (FRInput::GetKey(EKeyCode::E))
		{
			mTargetSpeed += glm::vec3{ 0.0f, velocity, 0.0f };
		}
		if (FRInput::GetKey(EKeyCode::Q))
		{
			mTargetSpeed += glm::vec3{ 0.0f, -velocity, 0.0f };
		}
	}

	mCurrentMovementSpeed = glm::lerp(mCurrentMovementSpeed, mTargetSpeed, static_cast<float>(10 * FRTimer::GetDeltaTimeSec()));
	mCamera.SetPosition(mCamera.GetPosition() + mCurrentMovementSpeed);
}

void FR::FRCameraController::UpdateMouseState()
{
	if (FRInput::GetKeyDown(EKeyCode::ClickLeft))
	{
		mLeftMousePressed = true;
	}

	if (FRInput::GetKeyUp(EKeyCode::ClickLeft))
	{
		mLeftMousePressed = false;
		mFirstMouse = true;
	}

	if (FRInput::GetKeyDown(EKeyCode::ClickMiddle))
	{
		mMiddleMousePressed = true;
		mFirstMouse = true;
	}

	if (FRInput::GetKeyUp(EKeyCode::ClickMiddle))
	{
		mMiddleMousePressed = false;
	}

	if (FRInput::GetKeyDown(EKeyCode::ClickRight))
	{
		mRightMousePressed = true;
		mFirstMouse = true;
	}

	if (FRInput::GetKeyUp(EKeyCode::ClickRight))
	{
		mRightMousePressed = false;
	}
}
