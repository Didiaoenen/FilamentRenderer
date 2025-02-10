#include "FREngineWarp.h"

template<typename T>
void FR::FREngineWarp::Destroy(T* pPtr)
{
	if (pPtr)
	{
		PtrValue(this)->destroy(PtrValue(pPtr));
	}
}