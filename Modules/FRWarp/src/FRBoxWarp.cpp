#include "FRBoxWarp.h"
#include <MathConvert.h>

FR::FRBoxWarp::FRBoxWarp(const glm::vec3& pCenter, const glm::vec3& pHalfExtent)
	: FRObjWarp({ .center = MathConvert::ToFVec3(pCenter), .halfExtent = MathConvert::ToFVec3(pHalfExtent) })
{
}
