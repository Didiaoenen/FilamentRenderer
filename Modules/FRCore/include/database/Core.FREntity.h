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
		FREntity(FROptRef<FRTransform> pTransform = std::nullopt)
			: transform(pTransform)
        {
            mEntity = FRFilamentHelper::CreateEntity();
        };

        FREntityWarp* GetEntity() const
        {
            return mEntity;
        }

    public:
        ~FREntity() = default;

    protected:
        FREntityWarp* mEntity{ nullptr };

    public:
        FROptRefVal<FRTransform> transform;

    };
}