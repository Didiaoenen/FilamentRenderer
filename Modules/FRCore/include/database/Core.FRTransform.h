#pragma once

#include "Tools.FREvent.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace FR
{
	class FRTransform
	{
	public:

		enum class ENotification : uint8_t
		{
			TRANSFORM_CHANGED,
			TRANSFORM_DESTROYED
		};

		FRTransform(
			const glm::vec3& pLocalPosition = {},
			const glm::quat& pLocalRotation = {},
			const glm::vec3& pLocalScale = { 1.f, 1.f, 1.f });

		void SetParent(FRTransform& pParent);

		bool RemoveParent();

		void SetLocalPosition(const glm::vec3& pNewPosition);

		void SetLocalRotation(const glm::quat& pNewRotation);

		void SetLocalScale(const glm::vec3& pNewScale);

		void SetWorldPosition(const glm::vec3& pNewPosition);

		void SetWorldRotation(const glm::quat& pNewRotation);

		void SetWorldScale(const glm::vec3& pNewScale);

		void TranslateLocal(const glm::vec3& pTranslation);

		void RotateLocal(const glm::quat& pRotation);

		void ScaleLocal(const glm::vec3& pScale);

		const glm::vec3& GetLocalPosition() const;

		const glm::quat& GetLocalRotation() const;

		const glm::vec3& GetLocalScale() const;

		const glm::vec3& GetWorldPosition() const;

		const glm::quat& GetWorldRotation() const;

		const glm::vec3& GetWorldScale() const;

		const glm::mat4& GetLocalMatrix() const;

		const glm::mat4& GetWorldMatrix() const;

		glm::vec3 GetLocalUp() const;

		glm::vec3 GetLocalRight() const;

		glm::vec3 GetLocalForward() const;

		glm::vec3 GetWorldUp() const;

		glm::vec3 GetWorldRight() const;

		glm::vec3 GetWorldForward() const;

		void UpdateLocalMatrix();

		void UpdateWorldMatrix();

		void GenerateMatricesLocal(glm::vec3 pPosition, glm::quat pRotation, glm::vec3 pScale);

		void GenerateMatricesWorld(glm::vec3 pPosition, glm::quat pRotation, glm::vec3 pScale);

	private:
		void PreDecomposeLocalMatrix();

		void PreDecomposeWorldMatrix();

		void NotificationHandler(ENotification pNotification);

	public:
		virtual ~FRTransform() = default;

	public:
		FRTransform* parent{ nullptr };

		FREvent<ENotification> Notifier;

	private:
		glm::vec3 mLocalPosition{ 0.f };
		glm::vec3 mLocalScale{ 1.f };

		glm::vec3 mWorldPosition{ 0.f };
		glm::vec3 mWorldScale{ 1.f };

		glm::quat mLocalRotation{ glm::identity<glm::quat>() };
		glm::quat mWorldRotation{ glm::identity<glm::quat>() };

		glm::mat4 mLocalMatrix{ glm::identity<glm::mat4>() };
		glm::mat4 mWorldMatrix{ glm::identity<glm::mat4>() };

		FREvent<ENotification>::ListenerID mNotificationHandlerID;
	};
}

