#pragma once

#include <glm/glm.hpp>

namespace FR
{
	class BoundingBox;

	class Ray
	{
	public:
		Ray() = default;
		
		Ray(const glm::vec3& pStart, const glm::vec3& pDirection);

		bool Intersects(const BoundingBox& pBB) const;
		bool Intersects(const BoundingBox& pBB, float& pT) const;
		bool IntersectsTriangle(const glm::vec3& pA, const glm::vec3& pB, const glm::vec3& pC, float& pT) const;

		glm::vec3 origin = glm::vec3{ 0.0f };
		glm::vec3 direction = glm::vec3{ 0.0f };
	};
}

