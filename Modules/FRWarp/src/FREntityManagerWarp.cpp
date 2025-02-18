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
	PtrValue(this).destroy(PtrValue(pEntity));
	RemoveEntity(pEntity);
}

bool FR::FREntityManagerWarp::IsAlive(FREntityWarp* pEntity)
{
	return PtrValue(this).isAlive(PtrValue(pEntity));
}

bool FR::FREntityManagerWarp::FindEntity(FREntityWarp* pEntity)
{
	auto found = std::find_if(mEntities.begin(), mEntities.end(), [pEntity](FREntityWarp* pElement)
		{
			return pElement == pEntity;
		});

	if (found != mEntities.end())
	{
		return true;
	}

	return false;
}

void FR::FREntityManagerWarp::RemoveEntity(FREntityWarp* pEntity)
{
	mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), pEntity), mEntities.end());
}

size_t FR::FREntityManagerWarp::GetEntityCount()
{
	return PtrValue(this).getEntityCount();
}

FR::FREntityWarp* FR::FREntityManagerWarp::Create()
{
	auto entity = new FREntityWarp(this);
	mEntities.emplace_back(entity);
	return entity;
}

FR::FREntityManagerWarp::~FREntityManagerWarp()
{
	//for (const auto entity : mEntities)
	//{
	//	Destroy(entity);
	//	delete entity;
	//}
	//mEntities.clear();
}
