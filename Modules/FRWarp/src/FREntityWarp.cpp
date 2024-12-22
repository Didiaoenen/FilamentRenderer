#include "FREntityWarp.h"
#include "FREntityManagerWarp.h"

FR::FREntityWarp::FREntityWarp(FREntityManagerWarp* pEntityManager)
{
	mValue = FRObjValue(PtrValue(pEntityManager).create());
}
