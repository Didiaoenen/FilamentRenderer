#include "Ray.h"

#include "BoundingBox.h"

FR::Ray::Ray(const glm::vec3& pStart, const glm::vec3& pDirection)
{
	origin = pStart;
	direction = pDirection;
}

bool FR::Ray::Intersects(const BoundingBox& pBB) const
{
	float distance;
	return Intersects(pBB, distance);
}

bool FR::Ray::Intersects(const BoundingBox& pBB, float& pT) const
{
	pT = 0.0f;

	if (pBB.IsInside(origin))
	{
		return true;
	}

	float dist = FLT_MAX;

	if (origin.x < pBB.Min().x && direction.x > 0.0f)
	{
		float x = (pBB.Min().x - origin.x) / direction.x;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.y >= pBB.Min().y && point.y <= pBB.Max().y && point.z >= pBB.Min().z && point.z <= pBB.Max().z)
			{
				dist = x;
			}
		}
	}

	if (origin.x > pBB.Max().x && direction.x < 0.0f)
	{
		float x = (pBB.Max().x - origin.x) / direction.x;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.y >= pBB.Min().y && point.y <= pBB.Max().y && point.z >= pBB.Min().z && point.z <= pBB.Max().z)
			{
				dist = x;
			}
		}
	}

	if (origin.y < pBB.Min().y && direction.y > 0.0f)
	{
		float x = (pBB.Min().y - origin.y) / direction.y;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.x >= pBB.Min().x && point.x <= pBB.Max().x && point.z >= pBB.Min().z && point.z <= pBB.Max().z)
			{
				dist = x;
			}
		}
	}
	if (origin.y > pBB.Max().y && direction.y < 0.0f)
	{
		float x = (pBB.Max().y - origin.y) / direction.y;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.x >= pBB.Min().x && point.x <= pBB.Max().x && point.z >= pBB.Min().z && point.z <= pBB.Max().z)
			{
				dist = x;
			}
		}
	}

	if (origin.z < pBB.Min().z && direction.z > 0.0f)
	{
		float x = (pBB.Min().z - origin.z) / direction.z;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.x >= pBB.Min().x && point.x <= pBB.Max().x && point.y >= pBB.Min().y && point.y <= pBB.Max().y)
			{
				dist = x;
			}
		}
	}
	if (origin.z > pBB.Max().z && direction.z < 0.0f)
	{
		float x = (pBB.Max().z - origin.z) / direction.z;
		if (x < dist)
		{
			glm::vec3 point = origin + x * direction;
			if (point.x >= pBB.Min().x && point.x <= pBB.Max().x && point.y >= pBB.Min().y && point.y <= pBB.Max().y)
			{
				dist = x;
			}
		}
	}

	pT = dist;

	return dist < FLT_MAX;
}

bool FR::Ray::IntersectsTriangle(const glm::vec3& pA, const glm::vec3& pB, const glm::vec3& pC, float& pT) const
{
	const glm::vec3 E1 = pB - pA;
	const glm::vec3 E2 = pC - pA;
	const glm::vec3 N = cross(E1, E2);

	const float det = -glm::dot(direction, N);
	const float invdet = 1.f / det;

	const glm::vec3 AO = origin - pA;
	const glm::vec3 DAO = glm::cross(AO, direction);
	
	const float u = glm::dot(E2, DAO) * invdet;
	const float v = -glm::dot(E1, DAO) * invdet;
	
	pT = glm::dot(AO, N) * invdet;
	
	return (det >= 1e-6f && pT >= 0.0f && u >= 0.0f && v >= 0.0f && (u + v) <= 1.0f);
}
