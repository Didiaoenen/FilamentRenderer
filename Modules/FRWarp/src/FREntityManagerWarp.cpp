#include "FREntityManagerWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"

FR::FREntityManagerWarp::FREntityManagerWarp(FR::FREngineWarp* pEngine)
{
	mValue = FRRefValue(PtrValue(pEngine)->getEntityManager());
}

void FR::FREntityManagerWarp::Create(int pCount, std::vector<FREntityWarp*> pEntities)
{
}

void FR::FREntityManagerWarp::Destroy(int pCount, std::vector<FREntityWarp*> pEntities)
{
}

void FR::FREntityManagerWarp::Destroy(FREntityWarp* pEntity)
{
}

bool FR::FREntityManagerWarp::IsAlive(FREntityWarp* pEntity)
{
	return false;
}

size_t FR::FREntityManagerWarp::GetEntityCount()
{
	return size_t();
}

FR::FREntityWarp* FR::FREntityManagerWarp::Create()
{
	auto entity = new FREntityWarp(this);
	mEntities.push_back(entity);
	return entity;
}
