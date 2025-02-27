#pragma once

#include "Core.FRAsset.h"

#include <glm/ext.hpp>
#include <vector>

namespace FR
{
	class FRMesh;
	class SkeletonRig;

	struct FRModelData
	{
		std::vector<FRMesh*> meshs;
		std::vector<FRModelData> childs;
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 accTransform = glm::mat4(1.0f);
	};

	class FRModel
		: public FRAsset
	{
		friend class FRModelLoader;
		friend class FROzzModelLoader;

	public:
		FRModel() = default;

		void SetMesh(FRMesh* pMesh);

		const std::vector<FRMesh*>& GetMeshes() const;

		const std::vector<std::string>& GetMaterialNames() const;

	public:
		virtual ~FRModel();

	private:
		std::vector<FRMesh*> mMeshes;

		std::vector<std::string> mMaterialNames;

		glm::mat4 mTransformData = glm::mat4(1.0f);

		glm::mat4 mAccTransformData = glm::mat4(1.0f);

	};
}

