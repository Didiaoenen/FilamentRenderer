#pragma once

#include "Core.FRComponent.h"
#include "Core.FRTransform.h"

namespace FR
{
	class FRCompTransform
		: public FRComponent
	{
	public:
		FRCompTransform(FRActor& pOwner);

		void SetParent(FRCompTransform& pParent);

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

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual EComponentType GetType() override;

		virtual const std::string GetName() override;

		FRTransform& GetFRTransform();

	private:
		FRTransform mTransform;

	};
}

