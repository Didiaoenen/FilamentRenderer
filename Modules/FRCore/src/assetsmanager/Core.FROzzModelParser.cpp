#include "Core.FROzzModelParser.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"

#include <MathConvert.h>

#include <glm/ext.hpp>

#include <ozzmesh.h>
#include <ozz/base/io/archive.h>

bool FR::FROzzModelParser::LoadMesh(const std::string& pFilePath, FRModelData& pOutData, std::vector<std::string>& pMaterials)
{
	ozz::io::File file(pFilePath.c_str(), "rb");
	if (!file.opened())
	{
		return false;
	}

	ozz::io::IArchive archive(&file);

	ozz::vector<ozz::sample::Mesh> meshes;
	{
		while (archive.TestTag<ozz::sample::Mesh>())
		{
			meshes.resize(meshes.size() + 1);
			archive >> meshes.back();
		}
	}

	for (const auto& mesh : meshes)
	{
		pOutData.meshs.push_back(new FRMesh());
		auto& meshPtr = pOutData.meshs.back();

		const auto part = mesh.parts[0];
		
		for (uint32_t i = 0; i < part.positions.size(); i += 3)
		{
			meshPtr->positions.push_back(glm::vec4(part.positions[i], part.positions[i + 1], part.positions[i + 2], 1.0f));
			meshPtr->vertexs.push_back({ meshPtr->positions.back() });
		}

		std::vector<glm::vec3> normals;
		for (uint32_t i = 0; i < part.normals.size(); i += 3)
		{
			normals.push_back(glm::vec3(part.normals[i], part.normals[i + 1], part.normals[i + 2]));
		}

		std::vector<glm::vec3> tangents;
		for (uint32_t i = 0; i < part.tangents.size(); i += 4)
		{
			tangents.push_back(glm::vec3(part.tangents[i], part.tangents[i + 1], part.tangents[i + 2]));
		}

		if (normals.size() == tangents.size())
		{
			for (uint32_t i = 0; i < normals.size(); i++)
			{
				glm::quat quatBTN = glm::normalize(glm::quat(glm::mat3{ tangents[i], glm::cross(normals[i], tangents[i]), normals[i] }));
				meshPtr->tangents.push_back(glm::vec4{ quatBTN.x, quatBTN.y, quatBTN.z, quatBTN.w });
				meshPtr->vertexs[i].Tangent = meshPtr->tangents.back();
			}
		}

		for (uint32_t i = 0; i < part.uvs.size(); i += 2)
		{
			meshPtr->texCoords0.push_back(glm::vec2(part.uvs[i], part.uvs[i + 1]));
			if (i % 2 == 0)
			{
				meshPtr->vertexs[i / 2].TexCoord0 = meshPtr->texCoords0.back();
			}
		}

		for (uint32_t i = 0; i < part.colors.size(); i += 4)
		{
			meshPtr->colors.push_back(glm::vec4(part.colors[i], part.colors[i + 1], part.colors[i + 2], part.colors[i + 3]));
			if (i % 4 == 0)
			{
				meshPtr->vertexs[i / 4].Colors = meshPtr->colors.back();
			}
		}

		//
		auto count = part.influences_count();
		for (uint32_t i = 0; i < part.joint_indices.size(); i += count)
		{
			if (count >= 4)
			{
				meshPtr->jointIndexs.push_back(glm::u16vec4(part.joint_indices[i], part.joint_indices[i + 1], part.joint_indices[i + 2], part.joint_indices[i + 3]));
			}
			else
			{
				std::vector<uint16_t> temp;
				for (uint32_t j = 0; j < 4; j++)
				{
					temp.push_back(j < count ? part.joint_indices[i + j] : 0);
				}
				meshPtr->jointIndexs.push_back(glm::u16vec4(temp[0], temp[1], temp[2], temp[3]));
			}
		}

		//
		for (uint32_t i = 0; i < part.joint_weights.size(); i += count)
		{
			if (count >= 4)
			{
				meshPtr->jointWeights.push_back(glm::vec4(part.joint_weights[i], part.joint_weights[i + 1], part.joint_weights[i + 2], part.joint_weights[i + 3]));
			}
			else
			{
				std::vector<float> temp;
				for (uint32_t j = 0; j < 4; j++)
				{
					temp.push_back(j < count ? part.joint_weights[i + j] : 0.0f);
				}
				meshPtr->jointWeights.push_back(glm::vec4(temp[0], temp[1], temp[2], temp[3]));
			}
		}

		for (uint32_t i = 0; i < mesh.triangle_indices.size(); i++)
		{
			meshPtr->indices.push_back(mesh.triangle_indices[i]);
		}

		for (size_t i = 0; i < mesh.joint_remaps.size(); i++)
		{
			meshPtr->jointRemaps.push_back(mesh.joint_remaps[i]);
		}

		for (size_t i = 0; i < mesh.inverse_bind_poses.size(); i++)
		{
			meshPtr->inverseBindPoses.push_back(MathConvert::ToGlmMat4(mesh.inverse_bind_poses[i]));
		}

		meshPtr->name = std::string(reinterpret_cast<const char*>(part.names.data()), part.names.size());
		meshPtr->attachmentName = std::string(reinterpret_cast<const char*>(mesh.attachment_names.data()), mesh.attachment_names.size());
		meshPtr->boundingBox.Merge(meshPtr->positions.back());
		meshPtr->indexCount = meshPtr->indices.size();
	}

	return true;
}