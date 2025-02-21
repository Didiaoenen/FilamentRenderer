#include "FRSkinningBufferWarp.h"
#include "FREngineWarp.h"
#include <MathConvert.h>
#include <math/mat4.h>
#include <vector>

FR::FRSkinningBufferWarp::FRSkinningBufferWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}

void FR::FRSkinningBufferWarp::SetBones(FREngineWarp* pEngine, glm::mat4* pTransforms, size_t pCount, size_t pOffset)
{
	std::vector<filament::math::mat4f> temp;
	for (size_t i = 0; i < pCount; i++)
	{
		temp.push_back(MathConvert::ToFMat4(pTransforms[i]));
	}
	PtrValue(this)->setBones(*PtrValue(pEngine), temp.data(), temp.size(), pOffset);
}

FR::FRSkinningBufferWarp::~FRSkinningBufferWarp() = default;
