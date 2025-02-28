#pragma once

#include "Core.FRAsset.h"

#include <BoundingBox.h>

#include <vector>

namespace FR
{
	struct FRVertex
	{
		glm::vec4 Position;
		glm::vec4 Tangent;
		glm::vec2 TexCoord0;
		glm::vec2 TexCoord1;
		glm::vec4 Colors;
	};

	class FRMesh
		: public FRAsset
	{
	public:
		FRMesh() = default;

	public:
		virtual ~FRMesh();

	public:
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

		std::vector<uint16_t> jointRemaps;
		std::vector<glm::mat4> inverseBindPoses;

		std::string attachmentName;

		int32_t attachmentJoint{ -1 };

		uint32_t materialIndex{ 0 };

		uint32_t indexCount{ 0 };

		uint32_t indexOffset{ 0 };

		BoundingBox boundingBox;

	};
}

