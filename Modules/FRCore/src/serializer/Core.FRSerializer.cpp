#include "Core.FRSerializer.h"

#include "Core.FRModel.h"
#include "Core.FRShader.h"
#include "Core.FRMaterial.h"
#include "Core.FRTexture2D.h"
#include "Core.FRModelManager.h"
#include "Core.FRShaderManager.h"
#include "Core.FRTextureManager.h"
#include "Core.FRMaterialManager.h"

#include <Tools.FRServiceLocator.h>

void FR::FRSerializer::SerializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, bool pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const std::string& pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue.c_str());
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, float pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, double pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, unsigned pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int64_t pValue)
{
	tinyxml2::XMLElement* element = pDoc.NewElement(pName.c_str());
	element->SetText(pValue);
	pNode->InsertEndChild(element);
}

void FR::FRSerializer::SerializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec2& pValue)
{
	tinyxml2::XMLNode* element = pDoc.NewElement(pName.c_str());
	pNode->InsertEndChild(element);

	tinyxml2::XMLElement* x = pDoc.NewElement("x");
	x->SetText(pValue.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = pDoc.NewElement("y");
	y->SetText(pValue.y);
	element->InsertEndChild(y);
}

void FR::FRSerializer::SerializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec3& pValue)
{
	tinyxml2::XMLNode* element = pDoc.NewElement(pName.c_str());
	pNode->InsertEndChild(element);

	tinyxml2::XMLElement* x = pDoc.NewElement("x");
	x->SetText(pValue.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = pDoc.NewElement("y");
	y->SetText(pValue.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = pDoc.NewElement("z");
	z->SetText(pValue.z);
	element->InsertEndChild(z);
}

void FR::FRSerializer::SerializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::vec4& pValue)
{
	tinyxml2::XMLNode* element = pDoc.NewElement(pName.c_str());
	pNode->InsertEndChild(element);

	tinyxml2::XMLElement* x = pDoc.NewElement("x");
	x->SetText(pValue.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = pDoc.NewElement("y");
	y->SetText(pValue.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = pDoc.NewElement("z");
	z->SetText(pValue.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = pDoc.NewElement("w");
	w->SetText(pValue.w);
	element->InsertEndChild(w);
}

void FR::FRSerializer::SerializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const glm::quat& pValue)
{
	tinyxml2::XMLNode* element = pDoc.NewElement(pName.c_str());
	pNode->InsertEndChild(element);

	tinyxml2::XMLElement* x = pDoc.NewElement("x");
	x->SetText(pValue.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = pDoc.NewElement("y");
	y->SetText(pValue.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = pDoc.NewElement("z");
	z->SetText(pValue.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = pDoc.NewElement("w");
	w->SetText(pValue.w);
	element->InsertEndChild(w);
}

void FR::FRSerializer::SerializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, const Color& pValue)
{
	tinyxml2::XMLNode* element = pDoc.NewElement(pName.c_str());
	pNode->InsertEndChild(element);

	tinyxml2::XMLElement* r = pDoc.NewElement("r");
	r->SetText(pValue.r);
	element->InsertEndChild(r);

	tinyxml2::XMLElement* g = pDoc.NewElement("g");
	g->SetText(pValue.g);
	element->InsertEndChild(g);

	tinyxml2::XMLElement* b = pDoc.NewElement("b");
	b->SetText(pValue.b);
	element->InsertEndChild(b);

	tinyxml2::XMLElement* a = pDoc.NewElement("a");
	a->SetText(pValue.a);
	element->InsertEndChild(a);
}

void FR::FRSerializer::SerializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRModel* pValue)
{
	SerializeString(pDoc, pNode, pName.c_str(), pValue ? pValue->path : "?");
}

void FR::FRSerializer::SerializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRTexture2D* pValue)
{
	SerializeString(pDoc, pNode, pName.c_str(), pValue ? pValue->path : "?");
}

void FR::FRSerializer::SerializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRShader* pValue)
{
	SerializeString(pDoc, pNode, pName.c_str(), pValue ? pValue->path : "?");
}

void FR::FRSerializer::SerializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRMaterial* pValue)
{
	SerializeString(pDoc, pNode, pName.c_str(), pValue ? pValue->path : "?");
}

void FR::FRSerializer::DeserializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, bool& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryBoolText(&pOut);
	}
}

bool FR::FRSerializer::DeserializeBoolean(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	bool result;
	DeserializeBoolean(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, std::string& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		const char* result = element->GetText();
		pOut = result ? result : "";
	}
}

std::string FR::FRSerializer::DeserializeString(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	std::string result;
	DeserializeString(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, float& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryFloatText(&pOut);
	}
}

float FR::FRSerializer::DeserializeFloat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	float result;
	DeserializeFloat(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, double& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryDoubleText(&pOut);
	}
}

double FR::FRSerializer::DeserializeDouble(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	double result;
	DeserializeDouble(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryIntText(&pOut);
	}
}

int FR::FRSerializer::DeserializeInt(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	int result;
	DeserializeInt(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, unsigned& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryUnsignedText(&pOut);
	}
}

unsigned FR::FRSerializer::DeserializeUint(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	unsigned result;
	DeserializeUint(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, int64_t& pOut)
{
	if (auto element = pNode->FirstChildElement(pName.c_str()); element)
	{
		element->QueryInt64Text(&pOut);
	}
}

int64_t FR::FRSerializer::DeserializeInt64(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	int64_t result;
	DeserializeInt64(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec2& pOut)
{
	if (auto node = pNode->FirstChildElement(pName.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
		{
			element->QueryFloatText(&pOut.x);
		}

		if (auto element = node->FirstChildElement("y"); element)
		{
			element->QueryFloatText(&pOut.y);
		}
	}
}

glm::vec2 FR::FRSerializer::DeserializeVec2(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	glm::vec2 result;
	DeserializeVec2(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec3& pOut)
{
	if (auto node = pNode->FirstChildElement(pName.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
		{
			element->QueryFloatText(&pOut.x);
		}

		if (auto element = node->FirstChildElement("y"); element)
		{
			element->QueryFloatText(&pOut.y);
		}

		if (auto element = node->FirstChildElement("z"); element)
		{
			element->QueryFloatText(&pOut.z);
		}
	}
}

glm::vec3 FR::FRSerializer::DeserializeVec3(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	glm::vec3 result;
	DeserializeVec3(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::vec4& pOut)
{
	if (auto node = pNode->FirstChildElement(pName.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
		{
			element->QueryFloatText(&pOut.x);
		}

		if (auto element = node->FirstChildElement("y"); element)
		{
			element->QueryFloatText(&pOut.y);
		}

		if (auto element = node->FirstChildElement("z"); element)
		{
			element->QueryFloatText(&pOut.z);
		}

		if (auto element = node->FirstChildElement("w"); element)
		{
			element->QueryFloatText(&pOut.w);
		}
	}
}

glm::vec4 FR::FRSerializer::DeserializeVec4(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	glm::vec4 result;
	DeserializeVec4(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, glm::quat& pOut)
{
	if (auto node = pNode->FirstChildElement(pName.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
		{
			element->QueryFloatText(&pOut.x);
		}

		if (auto element = node->FirstChildElement("y"); element)
		{
			element->QueryFloatText(&pOut.y);
		}

		if (auto element = node->FirstChildElement("z"); element)
		{
			element->QueryFloatText(&pOut.z);
		}

		if (auto element = node->FirstChildElement("w"); element)
		{
			element->QueryFloatText(&pOut.w);
		}
	}
}

glm::quat FR::FRSerializer::DeserializeQuat(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	glm::quat result;
	DeserializeQuat(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, Color& pOut)
{
	if (auto node = pNode->FirstChildElement(pName.c_str()); node)
	{
		if (auto element = node->FirstChildElement("r"); element)
		{
			element->QueryFloatText(&pOut.r);
		}

		if (auto element = node->FirstChildElement("g"); element)
		{
			element->QueryFloatText(&pOut.g);
		}

		if (auto element = node->FirstChildElement("b"); element)
		{
			element->QueryFloatText(&pOut.b);
		}

		if (auto element = node->FirstChildElement("q"); element)
		{
			element->QueryFloatText(&pOut.a);
		}
	}
}

FR::Color FR::FRSerializer::DeserializeColor(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	Color result;
	DeserializeColor(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRModel*& pOut)
{
	if (std::string path = DeserializeString(pDoc, pNode, pName.c_str()); path != "?" && path != "")
	{
		pOut = GetService(FRModelManager).GetResource(path);
	}
	else
	{
		pOut = nullptr;
	}
}

FR::FRModel* FR::FRSerializer::DeserializeModel(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	FRModel* result;
	DeserializeModel(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRShader*& pOut)
{
	if (std::string path = DeserializeString(pDoc, pNode, pName.c_str()); path != "?" && path != "")
	{
		pOut = GetService(FRShaderManager).GetResource(path);
	}
	else
	{
		pOut = nullptr;
	}
}

FR::FRShader* FR::FRSerializer::DeserializeShader(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	FRShader* result;
	DeserializeShader(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRMaterial*& pOut)
{
	if (std::string path = DeserializeString(pDoc, pNode, pName.c_str()); path != "?" && path != "")
	{
		pOut = GetService(FRMaterialManager).GetResource(path);
	}
	else
	{
		pOut = nullptr;
	}
}

FR::FRMaterial* FR::FRSerializer::DeserializeMaterial(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	FRMaterial* result;
	DeserializeMaterial(pDoc, pNode, pName, result);
	return result;
}

void FR::FRSerializer::DeserializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName, FRTexture2D*& pOut)
{
	if (std::string path = DeserializeString(pDoc, pNode, pName.c_str()); path != "?" && path != "")
	{
		pOut = GetService(FRTextureManager).GetResource(path);
	}
	else
	{
		pOut = nullptr;
	}
}

FR::FRTexture2D* FR::FRSerializer::DeserializeTexture(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode, const std::string& pName)
{
	FRTexture2D* result;
	DeserializeTexture(pDoc, pNode, pName, result);
	return result;
}