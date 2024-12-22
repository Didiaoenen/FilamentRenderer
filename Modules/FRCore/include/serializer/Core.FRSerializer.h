#pragma once

#include <string>
#include <Color.h>
#include <tinyxml2.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace FR
{
	class FRModel;
	class FRShader;
	class FRTexture;
	class FRMaterial;

	class FRSerializer
	{
	public:
#pragma region SERIALIZATION_HELPERS
		static void SerializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, bool pValue);
		static void SerializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const std::string& pValue);
		static void SerializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, float pValue);
		static void SerializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, double pValue);
		static void SerializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int pValue);
		static void SerializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, unsigned pValue);
		static void SerializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int64_t pValue);
		static void SerializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec2& pValue);
		static void SerializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec3& pValue);
		static void SerializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec4& pValue);
		static void SerializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::quat& pValue);
		static void SerializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const Color& pValue);
		static void SerializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRModel* pValue);
		static void SerializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRTexture* pValue);
		static void SerializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRShader* pValue);
		static void SerializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRMaterial* pValue);
#pragma endregion

#pragma region DESERIALIZATION_HELPERS
		static void DeserializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, bool& pOut);
		static bool DeserializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, std::string& pOut);
		static std::string DeserializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);
		
		static void DeserializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, float& pOut);
		static float DeserializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, double& pOut);
		static double DeserializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int& pOut);
		static int DeserializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, unsigned& pOut);
		static unsigned DeserializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int64_t& pOut);
		static int64_t DeserializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec2& pOut);
		static glm::vec2 DeserializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec3& pOut);
		static glm::vec3 DeserializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec4& pOut);
		static glm::vec4 DeserializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::quat& pOut);
		static glm::quat DeserializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, Color& pOut);
		static Color DeserializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRModel*& pOut);
		static FRModel* DeserializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRShader*& pOut);
		static FRShader* DeserializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRMaterial*& pOut);
		static FRMaterial* DeserializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);

		static void DeserializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRTexture*& pOut);
		static FRTexture* DeserializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName);
#pragma endregion
	};
}

