#include "Core.FRRenderable.h"

#include "Core.FRMesh.h"
#include "Core.FREntity.h"
#include "Core.FRMaterial.h"

#include <FREngineWarp.h>
#include <FRFilamentHelper.h>
#include <FREntityManagerWarp.h>
#include <FRBufferDescriptorWarp.h>
#include <FRTransformManagerWarp.h>
#include <FRRenderableManagerWarp.h>

namespace
{
	template<typename T>
	struct VectorMemMove
	{
		std::vector<T> mVertor;

		explicit VectorMemMove(std::vector<T>&& pVector)
			: mVertor(std::move(pVector))
		{
		}

		static void Free(void* pBuffer, size_t pSize, void* pUser)
		{
			delete static_cast<VectorMemMove<T>*>(pUser);
		}

		const T* Data() const
		{
			return mVertor.data();
		}

		size_t Count() const
		{
			return mVertor.size();
		}

		size_t Size() const
		{
			return mVertor.size() * sizeof(T);
		}
	};

	template<typename T>
	static void Move(void* pBuffer, size_t pSize, void* pUser)
	{
		//auto& positions = static_cast<FR::FRMesh*>(pUser)->positions;
		//auto tBuffer = static_cast<T*>(pBuffer);
		//positions = std::move(std::vector<T>(tBuffer, tBuffer + pSize));
	}

	template<typename T>
	static int VectorIndexOf(std::vector<T*> pVector, T* pTemp)
	{
		if (auto find = std::find(pVector.begin(), pVector.end(), pTemp); find != pVector.end())
		{
			return std::distance(pVector.begin(), find);
		}

		return -1;
	}
}

FR::FRRenderable::FRRenderable(FREntity* pEntity)
	: mEntity(pEntity)
{
	mMaterials.resize(128);
}

void FR::FRRenderable::BuildMesh(FRMesh* pMesh)
{
	mMeshes.emplace_back(pMesh);
	mEntities.emplace_back(FRFilamentHelper::CreateEntity());

	CreateTransform();

	BuildBuffers(pMesh);
	BuildRenderable(pMesh);
}

FR::SkeletonRig* FR::FRRenderable::GetSkeletonRig()
{
	return mSkeletonRig;
}

std::vector<FR::FRMesh*>& FR::FRRenderable::GetMeshes()
{
	return mMeshes;
}

void FR::FRRenderable::FillMaterials(FRMaterial* pMaterial)
{
	for (uint8_t i = 0; i < mMeshes.size(); i++)
	{
		SetMaterialAtIndex(i, pMaterial);
	}
}

void FR::FRRenderable::SetMaterial(FRMesh* pMesh, FRMaterial* pMaterial)
{
	if (auto index = VectorIndexOf(mMeshes, pMesh); index != -1)
	{
		pMaterial->SetRefMesh(pMesh);
		auto engine = FRFilamentHelper::GetEngine();
		auto renderableManager = engine->GetRenderableManager();
		auto renderIns = FRFilamentHelper::GetRenderableManager()->GetInstance(mEntities[index]);
		for (size_t i = 0; i < renderableManager->GetPrimitiveCount(renderIns); i++)
		{
			renderableManager->SetMaterialInstanceAt(renderIns, i, pMaterial->NativePtr());
		}
	}
}

void FR::FRRenderable::SetMaterialAtIndex(uint8_t pIndex, FRMaterial* pMaterial)
{
	mMaterials[pIndex] = pMaterial;
	SetMaterial(mMeshes[pIndex], pMaterial);
}

void FR::FRRenderable::UpdateMeshSkinning(FRMesh* pMesh, std::vector<glm::mat4> pTrans)
{
	if (auto index = VectorIndexOf(mMeshes, pMesh); index != -1)
	{
		auto engine = FRFilamentHelper::GetEngine();
		mSkinningBuffers[index]->SetBones(engine, pTrans.data(), pTrans.size(), 0);
	}
}

void FR::FRRenderable::SetAxisAlignedBoundingBox(FRBoxWarp&& pBox)
{
	//auto engine = FRFilamentHelper::GetEngine();
	//auto renderableManager = engine->GetRenderableManager();
	//renderableManager->SetAxisAlignedBoundingBox(GetRenderInstance(), std::move(pBox));
}

void FR::FRRenderable::SetTransform(uint8_t pIndex, const glm::mat4& pMatrix)
{
	if (auto& mesh = mMeshes[pIndex]; auto& entity = mEntities[pIndex])
	{
		auto engine = FRFilamentHelper::GetEngine();
		auto transformManager = engine->GetTransformManager();
		auto transIns = transformManager->GetInstance(entity);
		transformManager->SetTransform(transIns, pMatrix);
	}
}

void FR::FRRenderable::SetTransform(const glm::mat4& pMatrix)
{
	auto engine = FRFilamentHelper::GetEngine();
	auto transformManager = engine->GetTransformManager();
	auto transIns = transformManager->GetInstance(mEntity->NatrivePtr());
	transformManager->SetTransform(transIns, pMatrix);
}

std::vector<FR::FRMaterial*>& FR::FRRenderable::GetMaterials()
{
	return mMaterials;
}

std::vector<FR::FREntityWarp*>& FR::FRRenderable::GetNativePtrs()
{
	return mEntities;
}

FR::FREntity* FR::FRRenderable::GetEntity()
{
	return mEntity;
}

void FR::FRRenderable::CreateTransform()
{
	auto engine = FRFilamentHelper::GetEngine();

	auto transformManager = engine->GetTransformManager();
	auto transIns = transformManager->GetInstance(mEntity->NatrivePtr());
	transformManager->Create(mEntities.back(), transIns, glm::mat4(1.0f));
}

void FR::FRRenderable::BuildBuffers(FRMesh* pMesh)
{
	auto engine = FRFilamentHelper::GetEngine();

	auto vertexBufferBuilder = FRVertexBufferWarp::Builder()
		.VertexCount(static_cast<uint32_t>(pMesh->vertexs.size())).BufferCount(6)
		.Attribute(FRVertexBufferWarp::EVertexAttribute::POSITION, 0, FRVertexBufferWarp::EAttributeType::FLOAT4, 0, sizeof(float) * 4)
		.Attribute(FRVertexBufferWarp::EVertexAttribute::TANGENTS, 1, FRVertexBufferWarp::EAttributeType::FLOAT4, 0, sizeof(float) * 4)
		.Normalized(FRVertexBufferWarp::EVertexAttribute::TANGENTS);

	vertexBufferBuilder
		.Attribute(FRVertexBufferWarp::EVertexAttribute::UV0, 2, FRVertexBufferWarp::EAttributeType::FLOAT2, 0, sizeof(float) * 2)
		.Normalized(FRVertexBufferWarp::EVertexAttribute::UV0);

	vertexBufferBuilder
		.Attribute(FRVertexBufferWarp::EVertexAttribute::UV1, 3, FRVertexBufferWarp::EAttributeType::FLOAT2, 0, sizeof(float) * 2)
		.Normalized(FRVertexBufferWarp::EVertexAttribute::UV1);

	vertexBufferBuilder
		.Attribute(FRVertexBufferWarp::EVertexAttribute::BONE_INDICES, 4, FRVertexBufferWarp::EAttributeType::USHORT4, 0, sizeof(uint16_t) * 4);

	vertexBufferBuilder
		.Attribute(FRVertexBufferWarp::EVertexAttribute::BONE_WEIGHTS, 5, FRVertexBufferWarp::EAttributeType::FLOAT4, 0, sizeof(float) * 4);

	mVertexBuffers.emplace_back(vertexBufferBuilder.Build(engine));

	mVertexBuffers.back()->SetBufferAt(engine, 0, FRBufferDescriptorWarp(std::move(pMesh->positions.data()), pMesh->positions.size() * sizeof(glm::vec4)));
	mVertexBuffers.back()->SetBufferAt(engine, 1, FRBufferDescriptorWarp(std::move(pMesh->tangents.data()), pMesh->tangents.size() * sizeof(glm::vec4)));
	mVertexBuffers.back()->SetBufferAt(engine, 2, FRBufferDescriptorWarp(std::move(pMesh->texCoords0.data()), pMesh->texCoords0.size() * sizeof(glm::vec2)));
	mVertexBuffers.back()->SetBufferAt(engine, 3, FRBufferDescriptorWarp(std::move(pMesh->texCoords1.data()), pMesh->texCoords1.size() * sizeof(glm::vec2)));

	if (pMesh->jointIndexs.size() > 0 && pMesh->jointWeights.size() > 0)
	{
		mVertexBuffers.back()->SetBufferAt(engine, 4, FRBufferDescriptorWarp(std::move(pMesh->jointIndexs.data()), pMesh->jointIndexs.size() * sizeof(glm::u16vec4)));
		mVertexBuffers.back()->SetBufferAt(engine, 5, FRBufferDescriptorWarp(std::move(pMesh->jointWeights.data()), pMesh->jointWeights.size() * sizeof(glm::vec4)));
	}

	mIndexBuffers.emplace_back(FRIndexBufferWarp::Builder().IndexCount(pMesh->indices.size()).Build(engine));
	mIndexBuffers.back()->SetBuffer(engine, FRBufferDescriptorWarp(std::move(pMesh->indices.data()), pMesh->indices.size() * sizeof(uint32_t)));

	if (pMesh->jointRemaps.size() > 0)
	{
		mSkinningBuffers.emplace_back(FRSkinningBufferWarp::Builder().BoneCount(pMesh->jointRemaps.size()).Initialize().Build(engine));
	}
}

void FR::FRRenderable::BuildRenderable(FRMesh* pMesh)
{
	auto engine = FRFilamentHelper::GetEngine();

	FRRenderableManagerWarp::Builder builder(1);
	builder.BoundingBox({ { -0.5f, -0.5f , -0.5f }, { 0.5f ,0.5f ,0.5f } });
	builder.Geometry(0, FRRenderableManagerWarp::EPrimitiveType::TRIANGLES, mVertexBuffers.back(), mIndexBuffers.back(), 0, pMesh->indexCount);

	if (pMesh->jointRemaps.size() > 0)
	{
		builder.EnableSkinningBuffers(true);
		builder.Skinning(mSkinningBuffers.back(), pMesh->jointRemaps.size(), 0);
	}

	builder.Build(engine, mEntities.back());
}

FR::FRRenderable::~FRRenderable()
{
	for (auto& indexBuffer : mIndexBuffers)
	{
		FRFilamentHelper::GetEngine()->Destroy(indexBuffer);
		FRFilamentHelper::GetEngine()->UnRegisterIndexBuffer(indexBuffer);
		delete indexBuffer; indexBuffer = nullptr;
	}
	mIndexBuffers.clear();

	for (auto& vertexBuffer : mVertexBuffers)
	{
		FRFilamentHelper::GetEngine()->Destroy(vertexBuffer);
		FRFilamentHelper::GetEngine()->UnRegisterVertexBuffer(vertexBuffer);
		delete vertexBuffer; vertexBuffer = nullptr;
	}
	mIndexBuffers.clear();

	for (auto& skinningBuffer : mSkinningBuffers)
	{
		FRFilamentHelper::GetEngine()->Destroy(skinningBuffer);
		FRFilamentHelper::GetEngine()->UnRegisterSknningBuffer(skinningBuffer);
		delete skinningBuffer; skinningBuffer = nullptr;
	}
	mSkinningBuffers.clear();

	for (auto& entity : mEntities)
	{
		FRFilamentHelper::GetTransformManager()->Destroy(entity);
		FRFilamentHelper::GetRenderableManager()->Destroy(entity);
		FRFilamentHelper::GetEntityManager()->Destroy(entity);
	}
	mEntities.clear();
}
