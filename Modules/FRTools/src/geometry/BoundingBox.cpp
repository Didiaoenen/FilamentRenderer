#include "BoundingBox.h"

FR::BoundingBox::~BoundingBox()
{
}

FR::BoundingBox::BoundingBox()
{
	mMin = glm::vec3(FLT_MAX);
	mMax = glm::vec3(-FLT_MAX);
}

FR::BoundingBox::BoundingBox(const glm::vec3& pMin, const glm::vec3& pMax)
{
	mMin = pMin;
	mMax = pMax;
}

FR::BoundingBox::BoundingBox(const BoundingBox& pOther)
{
	mMin = pOther.mMin;
	mMax = pOther.mMax;
}

FR::BoundingBox::BoundingBox(BoundingBox&& pOther)
{
	mMin = pOther.mMin;
	mMax = pOther.mMax;
}

void FR::BoundingBox::Set(const glm::vec3& pMin, const glm::vec3& pMax)
{
	mMin = pMin;
	mMax = pMax;
}

void FR::BoundingBox::Translate(const glm::vec3& pTranslation)
{
	mMin += pTranslation;
	mMax += pTranslation;
}

void FR::BoundingBox::Translate(float pX, float pY, float pZ)
{
	Translate(glm::vec3(pX, pY, pZ));
}

void FR::BoundingBox::Scale(const glm::vec3& scale)
{
	mMin *= scale;
	mMax *= scale;
}

void FR::BoundingBox::Scale(float x, float y, float z)
{
	mMin.x *= x;
	mMin.y *= y;
	mMin.z *= z;

	mMax.x *= x;
	mMax.y *= y;
	mMax.z *= z;
}

void FR::BoundingBox::Rotate(const glm::mat3& rotation)
{
	glm::vec3 center = Center();
	glm::vec3 extents = GetExtents();

	glm::vec3 rotatedExtents = glm::vec3(rotation * glm::vec4(extents, 1.0f));

	mMin = center - rotatedExtents;
	mMax = center + rotatedExtents;
}

void FR::BoundingBox::Transform(const glm::mat4& transform)
{
	glm::vec3 newCenter = transform * glm::vec4(Center(), 1.0f);
	glm::vec3 oldEdge = Size() * 0.5f;
	glm::vec3 newEdge = glm::vec3(
		glm::abs(transform[0][0]) * oldEdge.x + glm::abs(transform[1][0]) * oldEdge.y + glm::abs(transform[2][0]) * oldEdge.z,
		glm::abs(transform[0][1]) * oldEdge.x + glm::abs(transform[1][1]) * oldEdge.y + glm::abs(transform[2][1]) * oldEdge.z,
		glm::abs(transform[0][2]) * oldEdge.x + glm::abs(transform[1][2]) * oldEdge.y + glm::abs(transform[2][2]) * oldEdge.z
	);

	mMin = newCenter - newEdge;
	mMax = newCenter + newEdge;
}

FR::BoundingBox FR::BoundingBox::Transformed(const glm::mat4& transform) const
{
	BoundingBox box(*this);
	box.Transform(transform);
	return box;
}

void FR::BoundingBox::Merge(const BoundingBox& other)
{
	if (other.mMin.x < mMin.x)
	{
		mMin.x = other.mMin.x;
	}
	if (other.mMin.y < mMin.y)
	{
		mMin.y = other.mMin.y;
	}
	if (other.mMin.z < mMin.z)
	{
		mMin.z = other.mMin.z;
	}

	if (other.mMax.x > mMax.x)
	{
		mMax.x = other.mMax.x;
	}
	if (other.mMax.y > mMax.y)
	{
		mMax.y = other.mMax.y;
	}
	if (other.mMax.z > mMax.z)
	{
		mMax.z = other.mMax.z;
	}
}

void FR::BoundingBox::Merge(const glm::vec3& point)
{
	if (point.x < mMin.x)
	{
		mMin.x = point.x;
	}
	if (point.y < mMin.y)
	{
		mMin.y = point.y;
	}
	if (point.z < mMin.z)
	{
		mMin.z = point.z;
	}

	if (point.x > mMax.x)
	{
		mMax.x = point.x;
	}
	if (point.y > mMax.y)
	{
		mMax.y = point.y;
	}
	if (point.z > mMax.z)
	{
		mMax.z = point.z;
	}
}

FR::EIntersection FR::BoundingBox::IsInside(const glm::vec3& point) const
{
	if (point.x < mMin.x || point.x > mMax.x || point.y < mMin.y || point.y > mMax.y || point.z < mMin.z || point.z > mMax.z)
	{
		return OUTSIDE;
	}
	return INSIDE;
}

FR::EIntersection FR::BoundingBox::IsInside(const BoundingBox& box) const
{
	if (box.mMax.x < mMin.x || box.mMin.x > mMax.x || box.mMax.y < mMin.y || box.mMin.y > mMax.y || box.mMax.z < mMin.z || box.mMin.z > mMax.z)
	{
		return OUTSIDE;
	}
	else if (box.mMin.x < mMin.x || box.mMax.x > mMax.x || box.mMin.y < mMin.y || box.mMax.y > mMax.y || box.mMin.z < mMin.z || box.mMax.z > mMax.z)
	{
		return INTERSECTS;
	}
	return INSIDE;
}

glm::vec3 FR::BoundingBox::Min() const
{
	return mMin;
}

glm::vec3 FR::BoundingBox::Max() const
{
	return mMax;
}

glm::vec3 FR::BoundingBox::Size() const
{
	return mMax - mMin;
}

glm::vec3 FR::BoundingBox::Center() const
{
	return (mMax + mMin) * 0.5f;
}

glm::vec3 FR::BoundingBox::GetExtents() const
{
	return mMax - mMin;
}
