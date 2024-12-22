#include "Core.FRAssimpParser.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"

#include <assimp/scene.h>
#include <assimp/config.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace FR
{
	size_t indicesOffset = 0;

    const unsigned int parserFlags =
        // normals and tangents
        aiProcess_GenSmoothNormals |
        aiProcess_CalcTangentSpace |
        // UV Coordinates
        aiProcess_GenUVCoords |
        // topology optimization
        aiProcess_FindInstances |
        aiProcess_OptimizeMeshes |
        aiProcess_JoinIdenticalVertices |
        // misc optimization
        aiProcess_ImproveCacheLocality |
        aiProcess_SortByPType |
        // we only support triangles
        aiProcess_Triangulate;
}

bool FR::FRAssimpParser::LoadModel(const std::string& pFileName, FRModelData& pOutData, std::vector<std::string>& pMaterials)
{
	indicesOffset = 0;

    Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
	importer.SetPropertyBool(AI_CONFIG_IMPORT_COLLADA_IGNORE_UP_DIRECTION, true);
	importer.SetPropertyBool(AI_CONFIG_PP_PTV_KEEP_HIERARCHY, true);

	const aiScene* scene = importer.ReadFile(pFileName, parserFlags);

	if (!scene)
    {
        return false;
    }

	if (!scene->mRootNode)
	{
		return false;
	}

	ProcessMaterials(scene, pMaterials);

	ProcessNode(scene, scene->mRootNode, pOutData);

    return true;
}

void FR::FRAssimpParser::ProcessMaterials(const aiScene* pScene, std::vector<std::string>& pMaterials)
{
	for (uint32_t i = 0; i < pScene->mNumMaterials; ++i)
	{
		aiMaterial* material = pScene->mMaterials[i];
		if (material)
		{
			aiString name;
			aiGetMaterialString(material, AI_MATKEY_NAME, &name);
			pMaterials.push_back(name.C_Str());
		}
	}
}

void FR::FRAssimpParser::ProcessNode(const aiScene* pScene, aiNode* pNode, FRModelData& pOutData)
{
	glm::mat4 transform = glm::transpose(*reinterpret_cast<glm::mat4 const*>(&pNode->mTransformation));

	for (uint32_t i = 0; i < pNode->mNumMeshes; ++i)
	{
		pOutData.meshs.push_back(new FRMesh());
		auto& meshPtr = pOutData.meshs.back();
		aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
		ProcessMesh(pScene, mesh, *meshPtr);

		indicesOffset += mesh->mNumVertices;
	}

	for (uint32_t i = 0; i < pNode->mNumChildren; ++i)
	{
		ProcessNode(pScene, pNode->mChildren[i], pOutData);
	}
}

void FR::FRAssimpParser::ProcessMesh(const aiScene* pScene, aiMesh* pMesh, FRMesh& pOutMesh)
{
	pOutMesh.name = pMesh->mName.C_Str();

	glm::vec3 const* positions = reinterpret_cast<glm::vec3 const*>(pMesh->mVertices);
	glm::vec3 const* normals = reinterpret_cast<glm::vec3 const*>(pMesh->mNormals);
	glm::vec3 const* tangents = reinterpret_cast<glm::vec3 const*>(pMesh->mTangents);
	glm::vec3 const* bitangents = reinterpret_cast<glm::vec3 const*>(pMesh->mBitangents);
	glm::vec3 const* texCoords0 = reinterpret_cast<glm::vec3 const*>(pMesh->mTextureCoords[0]);
	glm::vec3 const* texCoords1 = reinterpret_cast<glm::vec3 const*>(pMesh->mTextureCoords[1]);

	FRMeshData meshData;
	for (size_t j = 0; j < pMesh->mNumVertices; j++)
	{
		glm::vec4 position = { positions[j], 1.f };
		glm::vec3 normal = normals ? normals[j] : glm::vec3{ 0.f };
		glm::vec3 tangent = tangents ? tangents[j] : glm::vec3{ 0.f };
		glm::vec3 bitangent = bitangents ? bitangents[j] : glm::vec3{ 0.f };
		glm::vec2 texCoord0 = texCoords0 ? glm::vec2(texCoords0[j]) : glm::vec2{ 0.f };
		glm::vec2 texCoord1 = texCoords1 ? glm::vec2(texCoords1[j]) : glm::vec2{ 0.f };
		glm::quat quatBTN = glm::normalize(glm::quat(glm::mat3{ tangent, glm::cross(normal, tangent), normal }));
		glm::vec4 tangents = glm::vec4{ quatBTN.x, quatBTN.y, quatBTN.z, quatBTN.w };

		meshData.positions.push_back(position);
		meshData.tangents.push_back(tangents);
		meshData.texCoords0.push_back(texCoord0);
		meshData.texCoords1.push_back(texCoord1);

		pOutMesh.boundingBox.Merge(position);

		pOutMesh.vertexs.push_back({ position, tangents, texCoord0, texCoord1 });
	}

	pOutMesh.indexOffset = pOutMesh.indices.size();

	//
	for (size_t j = 0; j < pMesh->mNumFaces; ++j)
	{
		const aiFace& face = pMesh->mFaces[j];
		for (size_t k = 0; k < face.mNumIndices; ++k)
		{
			meshData.indices.push_back(face.mIndices[k] + 0);
			pOutMesh.indices.push_back(face.mIndices[k] + 0);
		}
	}

	pOutMesh.indexCount = pMesh->mNumFaces * 3;
	pOutMesh.materialIndex = pMesh->mMaterialIndex;

	//
	pOutMesh.CreateBuffers(meshData);
}
