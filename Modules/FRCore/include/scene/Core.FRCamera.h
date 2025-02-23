#pragma once

#include "Core.FRObject.h"

#include <Ray.h>
#include <Color.h>

#include <glm/ext.hpp>

namespace FR
{
	class FREntity;
	class FRCameraWarp;

	class FRCamera
		: public FRObject
	{
	public:

		enum class EProjectionMode : uint8_t
		{
			ORTHOGRAPHIC,
			PERSPECTIVE,
		};

		FRCamera(FREntity* pEntity);

		void CacheMatrices(uint16_t pWidth, uint16_t pHeight);

		void CacheProjectionMatrix(uint16_t pWidth, uint16_t pHeight);

		void CacheViewMatrix();

		const glm::mat4& GetProjectionMatrix() const;

		const glm::mat4& GetViewMatrix() const;

		glm::mat4 CalculateProjectionMatrix(uint16_t pWidth, uint16_t pHeight) const;

		glm::mat4 CalculateViewMatrix() const;

		glm::mat4 GetOriginMatrix();

		const Ray ClickPointToRay(glm::vec2 pPosition);

		glm::vec3 GetRayDirection(const glm::vec2& pScreenPos, const float pZ) const;

		const glm::vec3& GetPosition() const;

		const glm::quat& GetRotation() const;

		void SetPosition(const glm::vec3& pPosition);

		void SetRotation(const glm::quat& pRotation);

		void SetViewport(const glm::vec4& pViewport);

		FRCameraWarp* NativePtr();

		FREntity* GetEntity();

	public:
		virtual ~FRCamera();

	public:
		EProjectionMode projectionMode{ EProjectionMode::PERSPECTIVE };

		float fov{ 60.f };
		float size{ 5.f };
		float near{ 0.01f };
		float far{ 1000.f };
		Color clearColor{ 0.f };

		bool clearColorBuffer{ true };
		bool clearDepthBuffer{ true };
		bool clearStencilBuffer{ true };

	private:
		FREntity* mEntity{ nullptr };
		FRCameraWarp* mCamera{ nullptr };

		glm::vec4 mViewport{ 0.f };
		glm::mat4 mViewMatrix{ 1.f };
		glm::mat4 mProjectionMatrix{ 1.f };

	};
}

