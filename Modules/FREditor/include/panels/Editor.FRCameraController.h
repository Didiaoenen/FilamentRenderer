#pragma once

#include <queue>
#include <optional>
#include <Core.FRCamera.h>

namespace FR
{
	class Window;
	class FRInput;
	class FRAPanelView;

	class FRActor;

	class FRCameraController
	{
	public:
		FRCameraController();

		void HandleInputs();

		void MoveToTarget(FRActor* pTarget);

		void SetSpeed(float pSpeed);

		float GetSpeed() const;

		void SetPosition(const glm::vec3& pPosition);

		void SetRotation(const glm::quat& pRotation);

		const glm::vec3& GetPosition() const;

		const glm::quat& GetRotation() const;

		bool IsRightMousePressed() const;

		void LockTargetActor(FRActor* pActor);

		void UnlockTargetActor();

		FRCamera* GetCamera();

	public:
		virtual ~FRCameraController();

	private:
		FRActor* GetTargetActor() const;
		void HandleCameraPanning(const glm::vec2& pMouseOffset, bool pFirstMouse);
		void HandleCameraFPSMouse(const glm::vec2& pMouseOffset, bool pFirstMouse);
		void HandleCameraOrbit(FRActor* pTarget, const glm::vec2& pMouseOffset, bool pFirstMouse);

		void HandleCameraZoom();
		void HandleCameraFPSKeyboard();
		void UpdateMouseState();

	private:
		FREntityWarp* mEntity{ nullptr };

		FRTransform mTransform;

		FRCamera mCamera;

		glm::vec3 mTargetSpeed{};
		glm::vec3 mCurrentMovementSpeed{};

		glm::vec3 mYPR{};
		glm::vec3 mOrbitStartOffset{};
		
		FRTransform* mOrbitTarget{ nullptr };

		bool mLeftMousePressed{ false };
		bool mRightMousePressed{ false };
		bool mMiddleMousePressed{ false };

		std::queue<std::tuple<glm::vec3, glm::quat>> mCameraDestinations;

		FRActor* mLockedActor{ nullptr };

	};
}

