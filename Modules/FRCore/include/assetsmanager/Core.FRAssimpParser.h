#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct aiNode;
struct aiMesh;
struct aiScene;

namespace FR
{
	class FRMesh;
	struct FRMeshData;
	struct FRModelData;

	class FRAssimpParser
	{
	public:
		FRAssimpParser() = default;

		bool LoadModel(const std::string& pFileName, FRModelData& pOutData, std::vector<std::string>& pMaterials);

	public:
		~FRAssimpParser() = default;

	private:
		void ProcessMesh(const aiScene* pScene, aiMesh* pMesh, FRMesh& pOutMesh);
		void ProcessNode(const aiScene* pScene, aiNode* pNode, FRModelData& pOutData);
		void ProcessMaterials(const aiScene* pScene, std::vector<std::string>& pMaterials);

	};
}

