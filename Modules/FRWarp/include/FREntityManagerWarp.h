#pragma once

#include "FRRefWarp.h"
#include <utils/EntityManager.h>

#include <vector>

namespace FR
{
	class FREntityWarp;
	class FREngineWarp;

	class FREntityManagerWarp
		: public FRRefWarp<utils::EntityManager>
	{
	public:
		FREntityManagerWarp() = default;

		FREntityManagerWarp(FREngineWarp* pEngine);

		void Create(int pCount, std::vector<FREntityWarp*> pEntities);

		void Destroy(int pCount, std::vector<FREntityWarp*> pEntities);

		void Destroy(FREntityWarp* pEntity);

		bool IsAlive(FREntityWarp* pEntity);

		bool FindEntity(FREntityWarp* pEntity);

		bool RemoveEntity(FREntityWarp* pEntity);

		size_t GetEntityCount();

		FREntityWarp* Create();

	public:
		virtual ~FREntityManagerWarp();

	private:
		std::vector<FREntityWarp*> mEntities;

	};
}

