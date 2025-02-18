#pragma once

#include "Core.FRObject.h"
#include "Core.FRTransform.h"

#include <FREntityWarp.h>
#include <FRFilamentHelper.h>
#include <Tools.FROptRefVal.h>

namespace FR
{
    class FREntity
        : public FRObject
    {
    public:
		FREntity(FREntityWarp* pEntity, FROptRef<FRTransform> pTransform = std::nullopt)
            : mEntity(pEntity)
            , mTransform(pTransform)
        {
        };

		FREntity()
		{
			mEntity = FRFilamentHelper::CreateEntity();
		};

        FREntityWarp* GetEntity() const
        {
            return mEntity;
        }

        FRTransform& GetTransform()
		{
			return mTransform;
		}

    public:
        virtual ~FREntity()
        {

        }

    protected:
        FREntityWarp* mEntity{ nullptr };
		FROptRefVal<FRTransform> mTransform;

    };
}