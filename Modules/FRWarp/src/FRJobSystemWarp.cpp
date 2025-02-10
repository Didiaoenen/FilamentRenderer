#include "FRJobSystemWarp.h"

#include "FREngineWarp.h"

FR::FRJobSystemWarp::FRJobSystemWarp(FREngineWarp* pEngine)
	: FRRefWarp(PtrValue(pEngine)->getJobSystem())
{
}
