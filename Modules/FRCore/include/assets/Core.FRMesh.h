#pragma once

#include "Core.FRObject.h"

#include <BoundingBox.h>
#include <FRTransformManagerWarp.h>
#include <FRRenderableManagerWarp.h>

#include <vector>

namespace FR
{
	class FRModel;
	class FRMaterial;

	class FRIndexBufferWarp;
	class FRVertexBufferWarp;

	struct FRVertex
	{
		glm::vec4 Position;
		glm::vec4 Tangent;
		glm::vec2 TexCoord0;
		glm::vec2 TexCoord1;
		glm::vec4 Colors;
	};

	struct FRMeshData
	{
		std::vector<FRVertex> vertexs;
		std::vector<uint32_t> indices;

		std::vector<glm::vec4> positions;
		std::vector<glm::vec4> tangents;
		std::vector<glm::vec4> normals;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec2> texCoords0;
		std::vector<glm::vec2> texCoords1;

		std::vector<glm::u16vec4> jointIndexs;
		std::vector<glm::vec4> jointWeights;
	};

	class FRMesh
		: public FRObject
	{
	public:
		FRMesh();

		void Build(FREntityWarp* pEntity);

		uint32_t GetIndexCount() const;

		uint32_t GetVertexCount() const;

		uint32_t GetMaterialIndex() const;

		void SetMaterial(FRMaterial* pMaterial);

		void SetTransform(glm::mat4 pMatrix);

		void SetAxisAlignedBoundingBox();

		FRTransformManagerWarp::Instance GetTransInstance();

		FRRenderableManagerWarp::Instance GetRenderInstance();

		void UpdateSkinning(std::vector<glm::mat4> pTrans);

		void UpdateAttachment(glm::mat4 pTrans);

		FREntityWarp* GetEntity();

		FRMesh* Create();

	private:
		void BuildBuffers();

	public:
		virtual ~FRMesh();

	public:
		std::string name;

		uint32_t indexCount{ 0 };
		uint32_t indexOffset{ 0 };
		std::vector<FRVertex> vertexs;
		std::vector<uint32_t> indices;
		
		std::vector<uint16_t> jointRemaps;
		std::vector<glm::mat4> inverseBindPoses;

		uint32_t materialIndex{ 0 };

		BoundingBox boundingBox;

		std::string attachmentName;

		int32_t attachmentJoint{ -1 };

		glm::mat4 transform{ 1.0f };

		glm::mat4 inverseTrans{ 1.0f };

		FRModel* model{ nullptr };

		FRMeshData meshData;

	private:
		FRMaterial* mMaterial{ nullptr };

		FREntityWarp* mEntity{ nullptr };
		FRIndexBufferWarp* mIndexBuffer{ nullptr };
		FRVertexBufferWarp* mVertexBuffer{ nullptr };
		FRSkinningBufferWarp* mSkinningBuffer{ nullptr };

	};
}

