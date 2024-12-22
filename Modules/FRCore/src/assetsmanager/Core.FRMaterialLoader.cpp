#include "Core.FRMaterialLoader.h"
#include "Core.FRMaterial.h"

#include <Log.FRLogger.h>

FR::FRMaterial* FR::FRMaterialLoader::Create(const std::string& pPath)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(pPath.c_str());
	if (!doc.Error())
	{
		tinyxml2::XMLNode* root = doc.FirstChild();

		FRMaterial* material = new FRMaterial();

		material->OnDeserialize(doc, root);

		return material;
	}
	return nullptr;
}

void FR::FRMaterialLoader::Reload(FRMaterial& pMaterial, const std::string& pPath)
{
}

void FR::FRMaterialLoader::Save(FRMaterial& pMaterial, const std::string& pPath)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("root");
	doc.InsertFirstChild(node);
	pMaterial.OnSerialize(doc, node);
	if (auto res = doc.SaveFile(pPath.c_str()); res == tinyxml2::XML_SUCCESS)
	{
		FRLogger::Log("Save Material Success", FRILogHandler::ELogLevel::LOG_INFO);
		return;
	}
	FRLogger::Log("Save Material Failed", FRILogHandler::ELogLevel::LOG_INFO);
}

bool FR::FRMaterialLoader::Destroy(FRMaterial*& pMaterial)
{
	return false;
}
