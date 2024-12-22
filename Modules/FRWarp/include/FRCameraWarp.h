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
		FRCameraWarp() = default;

		FRCameraWarp(FREngineWarp* pEngine, FREntityWarp* pEntity);

		void LookAt(glm::vec3 const& pEye, glm::vec3 const& pCenter, glm::vec3 const& pUp = { 0, 1, 0 });

		void SetProjection(filament::Camera::Projection pProjection, double pLeft, double pRight, double pBottom, double pTop, double pNear, double pFar);

		void SetProjection(double pFovInDegrees, double pAspect, double pNear, double pFar, filament::Camera::Fov pDirection = filament::Camera::Fov::VERTICAL);

		void SetExposure(float pAperture, float pShutterSpeed, float pSensitivity);

		void SetScaling(glm::vec2 pScaling);

		FREntityWarp* GetEntity();

		glm::mat4 GetViewMatrix();

		glm::mat4 GetProjectionMatrix();

	private:
		FREntityWarp* mEntity{ nullptr };

	};
}

