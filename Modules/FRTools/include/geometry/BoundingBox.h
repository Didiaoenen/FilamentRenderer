#pragma once

#include <glm/glm.hpp>

namespace FR
{
	enum EIntersection
	{
		OUTSIDE,
		INTERSECTS,
		INSIDE,
	};

	class BoundingBox
	{
	public:
		BoundingBox();

		BoundingBox(const glm::vec3& pMin, const glm::vec3& pMax);

		BoundingBox(const BoundingBox& pOther);

		void Set(const glm::vec3& pMin, const glm::vec3& pMax);

		void Translate(const glm::vec3& pTranslation);
		void Translate(float pX, float pY, float pZ);

		void Scale(const glm::vec3& pScale);
		void Scale(float pX, float pY, float pZ);

		void Rotate(const glm::mat3& pRotation);

		void Transform(const glm::mat4& pTransform);
		BoundingBox Transformed(const glm::mat4& transform) const;

		void Merge(const BoundingBox& pOther);

		void Merge(const glm::vec3& point);

		EIntersection IsInside(const glm::vec3& pPoint) const;

		EIntersection IsInside(const BoundingBox& pBox) const;

		glm::vec3 Min() const;

		glm::vec3 Max() const;

		glm::vec3 Size() const;

		glm::vec3 Center() const;

		glm::vec3 GetExtents() const;

	public:
		virtual ~BoundingBox();

	private:
		glm::vec3 mMin;
		glm::vec3 mMax;

	};
}

