#include "FREngineWarp.h"
#include "FRMaterialWarp.h"
#include "FRRenderTargetWarp.h"

template<typename T>
void FR::FREngineWarp::Destroy(T* pPtr)
{
	if (pPtr)
	{
		PtrValue(this)->destroy(PtrValue(pPtr));
	}
}