#include "Core.FRMesh.h"

#include "SkeletonRig.h"
#include "Core.FRModel.h"
#include "Core.FRShader.h"
#include "Core.FRMaterial.h"

#include <MathConvert.h>
#include <FRFilamentHelper.h>
#include <FRIndexBufferWarp.h>
#include <FRVertexBufferWarp.h>
#include <FRSkinningBufferWarp.h>
#include <FRBufferDescriptorWarp.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <ozz/animation/runtime/skeleton_utils.h>

namespace FR
{
	template<typename T>
	struct VectorMemMove
	{
		std::vector<T> vec;

		explicit VectorMemMove(std::vector<T>&& vec)
			: vec(std::move(vec))
		{
		}

		static void free(void* buffer, size_t size, void* user)
		{
			delete static_cast<VectorMemMove<T>*>(user);
		}

		const T* data() const
		{
			return vec.data();
		}

		size_t count() const
		{
			return vec.size();
		}

		size_t size() const
		{
			return vec.size() * sizeof(T);
		}
	};
}

FR::FRMesh::FRMesh()
{

}

void FR::FRMesh::Build(FREntityWarp* pEntity)
{
	BuildBuffers();

	mEntity = pEntity;

	auto engine = FRFilamentHelper::GetEngine();
	auto tcm = engine->GetTransformManager();
	tcm->Create(mEntity, model->GetTransInstance(), glm::mat4(1.0f));

	FRRenderableManagerWarp::Builder builder(1);
	builder.BoundingBox({ { -0.5f, -0.5f , -0.5f }, { 0.5f ,0.5f ,0.5f } });
	builder.Geometry(0, FRRenderableManagerWarp::EPrimitiveType::TRIANGLES, mVertexBuffer, mIndexBuffer, 0, indexCount);

	if (jointRemaps.size() > 0)
	{
		mSkinningBuffer = FRSkinningBufferWarp::Builder()
			.BoneCount(jointRemaps.size())
			.Initialize()
			.Build(engine);

		builder.EnableSkinningBuffers(true);
		builder.Skinning(mSkinningBuffer, jointRemaps.size(), 0);
	}

	builder.Build(engine, mEntity);
}

uint32_t FR::FRMesh::GetIndexCount() const
{
	return 0;
}

uint32_t FR::FRMesh::GetVertexCount() const
{
	return 0;
}

uint32_t FR::FRMesh::GetMaterialIndex() const
{
	return 0;
}

void FR::FRMesh::SetMaterial(FRMaterial* pMaterial)
{
	if (auto materialInstance = pMaterial->GetMaterialInstance())
	{
		pMaterial->SetRefMesh(this);
		auto instance = GetRenderInstance();
		auto engine = FRFilamentHelper::GetEngine();
		auto rcm = engine->GetRenderableManager();
		for (size_t i = 0; i < rcm->GetPrimitiveCount(instance); i++)
		{
			rcm->SetMaterialInstanceAt(instance, i, materialInstance);
		}
	}
}

void FR::FRMesh::SetTransform(glm::mat4 pMatrix)
{
	auto engine = FRFilamentHelper::GetEngine();
	auto tcm = engine->GetTransformManager();
	tcm->SetTransform(GetTransInstance(), pMatrix);
}

void FR::FRMesh::SetAxisAlignedBoundingBox()
{
	auto engine = FRFilamentHelper::GetEngine();
	auto rcm = engine->GetRenderableManager();
	rcm->SetAxisAlignedBoundingBox(GetRenderInstance(), { { -500.0f, -500.0f, -500.0f }, { 500.0f, 500.0f, 500.0f } });
}

FR::FRTransformManagerWarp::Instance FR::FRMesh::GetTransInstance()
{
	return FRFilamentHelper::GetTransformManager()->GetInstance(mEntity);
}

FR::FRRenderableManagerWarp::Instance FR::FRMesh::GetRenderInstance()
{
	return FRFilamentHelper::GetRenderableManager()->GetInstance(mEntity);
}

void FR::FRMesh::UpdateSkinning(std::vector<glm::mat4> pTrans)
{
	if (mSkinningBuffer)
	{
		auto engine = FRFilamentHelper::GetEngine();
		mSkinningBuffer->SetBones(engine, pTrans.data(), pTrans.size(), 0);
	}
}

void FR::FRMesh::UpdateAttachment(glm::mat4 pTrans)
{
	if (jointRemaps.size() == 0)
	{
		SetTransform(pTrans);
	}
}

FR::FREntityWarp* FR::FRMesh::GetEntity()
{
	return mEntity;
}

FR::FRMesh* FR::FRMesh::Create()
{
	auto mesh = new FRMesh();

	mesh->name = name;
	mesh->vertexs = vertexs;
	mesh->indices = indices;
	mesh->indexCount = indexCount;
	mesh->indexOffset = indexOffset;
	mesh->materialIndex = materialIndex;
	mesh->attachmentName = attachmentName;
	mesh->meshData = meshData;

	mesh->jointRemaps = jointRemaps;
	mesh->inverseBindPoses = inverseBindPoses;
	mesh->attachmentJoint = attachmentJoint;

	mesh->transform = transform;
	mesh->inverseTrans = inverseTrans;

	mesh->boundingBox = BoundingBox(boundingBox);

	return mesh;
}

void FR::FRMesh::BuildBuffers()
{
	auto engine = FRFilamentHelper::GetEngine();

	auto vertexBufferBuilder = FRVertexBufferWarp::Builder()
		.VertexCount(static_cast<uint32_t>(vertexs.size())).BufferCount(6)
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

	mVertexBuffer = vertexBufferBuilder.Build(engine);

	VectorMemMove<glm::vec4>* vecPositions = new VectorMemMove<glm::vec4>(std::move(meshData.positions));
	VectorMemMove<glm::vec4>* vecTangents = new VectorMemMove<glm::vec4>(std::move(meshData.tangents));
	VectorMemMove<glm::vec2>* vecTexCoords0 = new VectorMemMove<glm::vec2>(std::move(meshData.texCoords0));
	VectorMemMove<glm::vec2>* vecTexCoords1 = new VectorMemMove<glm::vec2>(std::move(meshData.texCoords1));

	mVertexBuffer->SetBufferAt(engine, 0, FRBufferDescriptorWarp(vecPositions->data(), vecPositions->size(), VectorMemMove<glm::vec4>::free, vecPositions));
	mVertexBuffer->SetBufferAt(engine, 1, FRBufferDescriptorWarp(vecTangents->data(), vecTangents->size(), VectorMemMove<glm::vec4>::free, vecTangents));
	mVertexBuffer->SetBufferAt(engine, 2, FRBufferDescriptorWarp(vecTexCoords0->data(), vecTexCoords0->size(), VectorMemMove<glm::vec2>::free, vecTexCoords0));
	mVertexBuffer->SetBufferAt(engine, 3, FRBufferDescriptorWarp(vecTexCoords1->data(), vecTexCoords1->size(), VectorMemMove<glm::vec2>::free, vecTexCoords1));

	if (meshData.jointIndexs.size() > 0 && meshData.jointWeights.size() > 0)
	{
		VectorMemMove<glm::u16vec4>* vecJointIndexs = new VectorMemMove<glm::u16vec4>(std::move(meshData.jointIndexs));
		VectorMemMove<glm::vec4>* vecJointWeights = new VectorMemMove<glm::vec4>(std::move(meshData.jointWeights));

		mVertexBuffer->SetBufferAt(engine, 4, FRBufferDescriptorWarp(vecJointIndexs->data(), vecJointIndexs->size(), VectorMemMove<glm::u16vec4>::free, vecJointIndexs));
		mVertexBuffer->SetBufferAt(engine, 5, FRBufferDescriptorWarp(vecJointWeights->data(), vecJointWeights->size(), VectorMemMove<glm::vec4>::free, vecJointWeights));
	}

	mIndexBuffer = FRIndexBufferWarp::Builder().IndexCount(indices.size()).Build(engine);
	mIndexBuffer->SetBuffer(engine, FRBufferDescriptorWarp(indices.data(), indices.size() * sizeof(uint32_t)));
}

FR::FRMesh::~FRMesh()
{
	FRFilamentHelper::GetEngine()->Destroy(mIndexBuffer);
	FRFilamentHelper::GetEngine()->UnRegisterIndexBuffer(mIndexBuffer);
	delete mIndexBuffer; mIndexBuffer = nullptr;

	FRFilamentHelper::GetEngine()->Destroy(mVertexBuffer);
	FRFilamentHelper::GetEngine()->UnRegisterVertexBuffer(mVertexBuffer);
	delete mVertexBuffer; mVertexBuffer = nullptr;

	FRFilamentHelper::GetEngine()->Destroy(mSkinningBuffer);
	FRFilamentHelper::GetEngine()->UnRegisterSknningBuffer(mSkinningBuffer);
	delete mSkinningBuffer; mSkinningBuffer = nullptr;
}
