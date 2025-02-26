#pragma once

#include "Core.FRObject.h"

#include <glm/ext.hpp>

#include <vector>

namespace FR
{
	class FRMesh;
	class FREntity;
	class FRMaterial;
	class SkeletonRig;

	class FRBoxWarp;
	class FREntityWarp;
	class FRIndexBufferWarp;
	class FRVertexBufferWarp;
	class FRSkinningBufferWarp;

	class FRRenderable
		: public FRObject
	{
	public:
		FRRenderable(FREntity* pEntity);

		void BuildMesh(FRMesh* pMesh);

		SkeletonRig* GetSkeletonRig();

		std::vector<FRMesh*>& GetMeshes();

		void FillMaterials(FRMaterial* pMaterial);

		void SetMaterial(FRMesh* pMesh, FRMaterial* pMaterial);

		void SetMaterialAtIndex(uint8_t pIndex, FRMaterial* pMaterial);

		void UpdateMeshSkinning(FRMesh* pMesh, std::vector<glm::mat4> pTrans);

		void SetAxisAlignedBoundingBox(FRBoxWarp&& pBox);

		void SetTransform(uint8_t pIndex, const glm::mat4& pMatrix);

		void SetTransform(const glm::mat4& pMatrix);

		std::vector<FRMaterial*>& GetMaterials();

		std::vector<FREntityWarp*>& GetNativePtrs();

		//const BoundingSphere& GetBoundingSphere();
		
		//void ComputeBoundingSphere();

		FREntity* GetEntity();

	private:
		void CreateTransform();

		void BuildBuffers(FRMesh* pMesh);
		
		void BuildRenderable(FRMesh* pMesh);

	public:
		virtual ~FRRenderable();

	public:
		std::string name;

	private:
		FREntity* mEntity{ nullptr };
		
		std::vector<FRMesh*> mMeshes;
		std::vector<FRMaterial*> mMaterials;
		std::vector<FREntityWarp*> mEntities;

		SkeletonRig* mSkeletonRig{ nullptr };

		std::vector<FRIndexBufferWarp*> mIndexBuffers;
		std::vector<FRVertexBufferWarp*> mVertexBuffers;
		std::vector<FRSkinningBufferWarp*> mSkinningBuffers;

		//BoundingSphere mBoundingSphere;

	};
}

