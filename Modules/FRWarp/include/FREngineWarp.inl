#pragma once

#include "FREngineWarp.h"
#include "FRMaterialWarp.h"
#include "FRRenderTargetWarp.h"

template<typename T>
void FR::FREngineWarp::Destroy(T* pWarpValue)
{
	if (pWarpValue)
	{
		PtrValue(this)->destroy(PtrValue(pWarpValue));
	}
}