#include "FREntityWarp.h"
#include "FRFilamentHelper.h"
#include "FREntityManagerWarp.h"

FR::FREntityWarp::FREntityWarp(FREntityManagerWarp* pEntityManager)
{
	mValue = FRObjValue(PtrValue(pEntityManager).create());
}

FR::FREntityWarp::~FREntityWarp()
{
	FRFilamentHelper::GetEntityManager()->Destroy(this);
}