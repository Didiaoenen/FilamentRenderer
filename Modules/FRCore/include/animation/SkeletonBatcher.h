#pragma once

#include "Core.FRObject.h"

namespace FR
{
	class SkeletonBatcher
		: public FRObject
	{
	public:

		enum class EJointMeshType
		{
			QuadSphere,
			Cube,
		};

		SkeletonBatcher();

	public:
		~SkeletonBatcher();

	};
}

