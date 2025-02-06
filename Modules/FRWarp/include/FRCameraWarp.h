#pragma once

#include "FRPtrWarp.h"
#include <glm/glm.hpp>
#include <utils/Entity.h>
#include <filament/Camera.h>

namespace FR
{
	class FREntityWarp;
	class FREngineWarp;

	class FRCameraWarp
		: public FRPtrWarp<filament::Camera>
	{
	public:
		using EFov = filament::Camera::Fov;

		using EProjection = filament::Camera::Projection;

		FRCameraWarp() = default;

		FRCameraWarp(FREngineWarp* pEngine, FREntityWarp* pEntity);

		void LookAt(const glm::vec3& pEye, const glm::vec3& pCenter, const glm::vec3& pUp = { 0, 1, 0 });

		void SetProjection(EProjection pProjection, double pLeft, double pRight, double pBottom, double pTop, double pNear, double pFar);

		void SetProjection(double pFovInDegrees, double pAspect, double pNear, double pFar, EFov pDirection = EFov::VERTICAL);

		void SetExposure(float pAperture, float pShutterSpeed, float pSensitivity);

		void SetScaling(const glm::vec2& pScaling);

		glm::mat4 GetProjectionMatrix();

		glm::mat4 GetViewMatrix();

		FREntityWarp* GetEntity();

	private:
		FREntityWarp* mEntity{ nullptr };

	};
}

