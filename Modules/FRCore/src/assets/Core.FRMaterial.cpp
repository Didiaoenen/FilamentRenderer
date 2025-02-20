#include "Core.FRMaterial.h"

#include "Core.FRMesh.h"
#include "Core.FRShader.h"
#include "Core.FRTexture.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRSerializer.h"

#include <MathConvert.h>
#include <FRMaterialWarp.h>
#include <FRMaterialInstanceWarp.h>
#include <FRFilamentHelper.h>

FR::FRMaterial::FRMaterial(FRShader* pShader)
{
	SetShader(pShader);
}

void FR::FRMaterial::SetShader(FRShader* pShader, bool pClearProps)
{
	mShader = pShader;

	if (mShader)
	{
		mShader->SetRefMaterial(this);
		mMaterial = mShader->NativePtr()->CreateInstance();

		if (pClearProps)
		{
			mPropInfos.clear();
			for (const auto& property : pShader->propInfos)
			{
				mPropInfos.emplace_back(property);
			}
		}
		else
		{
			std::vector<FRPropInfo> temp;
			for (const auto& property : mPropInfos)
			{
				auto it = std::find_if(pShader->propInfos.begin(), pShader->propInfos.end(), [property](FR::FRPropInfo& prop)
					{
						return prop.name == property.name;
					});

				if (it == pShader->propInfos.end())
				{
					temp.push_back(property);
				}
			}
			
			for (const auto& property : temp)
			{
				auto it = std::find_if(mPropInfos.begin(), mPropInfos.end(), [property](FR::FRPropInfo& prop)
					{
						return prop.name == property.name;
					});

				if (it != mPropInfos.end())
				{
					mPropInfos.erase(it);
				}
			}

			for (const auto& property : pShader->propInfos)
			{
				auto it = std::find_if(mPropInfos.begin(), mPropInfos.end(), [property](FR::FRPropInfo& prop)
					{
						return prop.name == property.name;
					});

				if (it == mPropInfos.end())
				{
					mPropInfos.emplace_back(property);
				}
			}
		}
	}
}

void FR::FRMaterial::SetTransparencyMode(FRMaterialInstanceWarp::ETransparencyMode pModel)
{
	mMaterial->SetTransparencyMode(pModel);
}

void FR::FRMaterial::SetCullingMode(FRMaterialInstanceWarp::ECullingMode pModel)
{
	mMaterial->SetCullingMode(pModel);
}

void FR::FRMaterial::SetDepthCulling(bool pCulling)
{
	mMaterial->SetDepthCulling(pCulling);
}

void FR::FRMaterial::SetDepthWrite(bool pWrite)
{
	mMaterial->SetDepthWrite(pWrite);
}

void FR::FRMaterial::SetColorWrite(bool pWrite)
{
	mMaterial->SetColorWrite(pWrite);
}

void FR::FRMaterial::UploadData() const
{
	for (auto& prop : mPropInfos)
	{
		if (!prop.sampler)
		{
			switch (prop.uniformType)
			{
			case FRMaterialWarp::EUniformType::BOOL:
				if (prop.data.type() == typeid(bool))
				{
					mMaterial->SetParameter(prop.name.c_str(), std::any_cast<bool>(prop.data));
				}
				break;
			case FRMaterialWarp::EUniformType::INT:
				if (prop.data.type() == typeid(int))
				{
					mMaterial->SetParameter(prop.name.c_str(), std::any_cast<int>(prop.data));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT:
				if (prop.data.type() == typeid(float))
				{
					mMaterial->SetParameter(prop.name.c_str(), std::any_cast<float>(prop.data));
				}
			break;
			case FRMaterialWarp::EUniformType::FLOAT2:
				if (prop.data.type() == typeid(glm::vec2))
				{
					mMaterial->SetParameter(prop.name.c_str(), MathConvert::ToFVec2(std::any_cast<glm::vec2>(prop.data)));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT3:
				if (prop.data.type() == typeid(glm::vec3))
				{
					mMaterial->SetParameter(prop.name.c_str(), MathConvert::ToFVec3(std::any_cast<glm::vec3>(prop.data)));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT4:
				if (prop.data.type() == typeid(glm::vec4))
				{
					mMaterial->SetParameter(prop.name.c_str(), MathConvert::ToFVec4(std::any_cast<glm::vec4>(prop.data)));
				}
				break;
			default:
				break;
			}
		}
		else
		{
			switch (prop.samplerType)
			{
			case FRMaterialWarp::ESamplerType::SAMPLER_2D:
				if (prop.data.type() == typeid(FRTexture*))
				{
					if (auto tex = std::any_cast<FRTexture*>(prop.data))
					{
						mMaterial->SetParameter(prop.name.c_str(), tex->NativePtr(), tex->GetSampler());
					}
					else if (auto emptyTex = FRGuiDrawer::GetEmptyTexture())
					{
						mMaterial->SetParameter(prop.name.c_str(), emptyTex->NativePtr(), emptyTex->GetSampler());
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

FR::FRShader* FR::FRMaterial::GetShader()
{
	return mShader;
}

std::vector<FR::FRPropInfo>& FR::FRMaterial::GetPropInfos()
{
	return mPropInfos;
}

FR::FRPropInfo* FR::FRMaterial::GetPropInfo(const std::string& pName)
{
	auto found = std::find_if(mPropInfos.begin(), mPropInfos.end(), [pName](const FRPropInfo& pElement)
		{
			return pName == pElement.name;
		});

	if (found != mPropInfos.end())
	{
		return &(*found);
	}

	return nullptr;
}

void FR::FRMaterial::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
	FRSerializer::SerializeShader(pDoc, pNode, "shader", mShader);

	tinyxml2::XMLNode* settingsNode = pDoc.NewElement("settings");
	pNode->InsertEndChild(settingsNode);

	tinyxml2::XMLNode* propertiesNode = pDoc.NewElement("properties");
	pNode->InsertEndChild(propertiesNode);

	for (const auto& prop : mPropInfos)
	{
		tinyxml2::XMLNode* property = pDoc.NewElement("property");
		propertiesNode->InsertEndChild(property);

		FRSerializer::SerializeString(pDoc, property, "name", prop.name);

		if (prop.data.has_value())
		{
			if (!prop.sampler)
			{
				switch (prop.uniformType)
				{
				case FRMaterialWarp::EUniformType::BOOL:
					if (prop.data.type() == typeid(bool))
					{
						FRSerializer::SerializeInt(pDoc, property, "value", std::any_cast<bool>(prop.data));
					}
					break;
				case FRMaterialWarp::EUniformType::INT:
					if (prop.data.type() == typeid(int))
					{
						FRSerializer::SerializeInt(pDoc, property, "value", std::any_cast<int>(prop.data));
					}
					break;
				case FRMaterialWarp::EUniformType::FLOAT:
					if (prop.data.type() == typeid(float))
					{
						FRSerializer::SerializeFloat(pDoc, property, "value", std::any_cast<float>(prop.data));
					}
					break;
				case FRMaterialWarp::EUniformType::FLOAT2:
					if (prop.data.type() == typeid(glm::vec2))
					{
						FRSerializer::SerializeVec2(pDoc, property, "value", std::any_cast<glm::vec2>(prop.data));
					}
					break;
				case FRMaterialWarp::EUniformType::FLOAT3:
					if (prop.data.type() == typeid(glm::vec3))
					{
						FRSerializer::SerializeVec3(pDoc, property, "value", std::any_cast<glm::vec3>(prop.data));
					}
					break;
				case FRMaterialWarp::EUniformType::FLOAT4:
					if (prop.data.type() == typeid(glm::vec4))
					{
						FRSerializer::SerializeVec4(pDoc, property, "value", std::any_cast<glm::vec4>(prop.data));
					}
					break;
				default:
					break;
				}
			}
			else
			{
				switch (prop.samplerType)
				{
				case FRMaterialWarp::ESamplerType::SAMPLER_2D:
					if (prop.data.type() == typeid(FRTexture*))
					{
						FRSerializer::SerializeTexture(pDoc, property, "value", std::any_cast<FRTexture*>(prop.data));
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void FR::FRMaterial::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
	tinyxml2::XMLNode* settingsNode = pNode->FirstChildElement("settings");

	if (settingsNode)
	{

	}

	FRShader* shader = FRSerializer::DeserializeShader(pDoc, pNode, "shader");

	if (shader)
	{
		SetShader(shader);

		tinyxml2::XMLNode* propertiesNode = pNode->FirstChildElement("properties");

		if (propertiesNode)
		{
			tinyxml2::XMLNode* property = propertiesNode->FirstChildElement("property");
			for (; property; property = property->NextSiblingElement("property"))
			{
				if (auto nameElement = property->FirstChildElement("name"))
				{
					auto propInfo = GetPropInfo(nameElement->GetText());

					if (propInfo)
					{
						FRPropInfo& prop = *propInfo;

						if (!prop.sampler)
						{
							switch (prop.uniformType)
							{
							case FRMaterialWarp::EUniformType::BOOL:
								prop.data = std::any_cast<bool>(FRSerializer::DeserializeBoolean(pDoc, property, "value"));
								break;
							case FRMaterialWarp::EUniformType::INT:
								prop.data = std::any_cast<int>(FRSerializer::DeserializeInt(pDoc, property, "value"));
								break;
							case FRMaterialWarp::EUniformType::FLOAT:
								prop.data = std::any_cast<float>(FRSerializer::DeserializeFloat(pDoc, property, "value"));
								break;
							case FRMaterialWarp::EUniformType::FLOAT2:
								prop.data = std::any_cast<glm::vec2>(FRSerializer::DeserializeVec2(pDoc, property, "value"));
								break;
							case FRMaterialWarp::EUniformType::FLOAT3:
								prop.data = std::any_cast<glm::vec3>(FRSerializer::DeserializeVec3(pDoc, property, "value"));
								break;
							case FRMaterialWarp::EUniformType::FLOAT4:
								prop.data = std::any_cast<glm::vec4>(FRSerializer::DeserializeVec4(pDoc, property, "value"));
								break;
							default:
								break;
							}
						}
						else
						{
							switch (prop.samplerType)
							{
							case FRMaterialWarp::ESamplerType::SAMPLER_2D:
								prop.data = std::any_cast<FRTexture*>(FRSerializer::DeserializeTexture(pDoc, property, "value"));
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
}

FR::FRMaterialInstanceWarp* FR::FRMaterial::NativePtr()
{
	return mMaterial;
}

std::map<uint64_t, FR::FRMesh*> FR::FRMaterial::GetRefMeshs()
{
	return mRefMeshs;
}

void FR::FRMaterial::SetRefMesh(FRMesh* pMesh)
{
	mRefMeshs.emplace(pMesh->mUUID, pMesh);
}

FR::FRMaterial::~FRMaterial()
{
	FRFilamentHelper::GetEngine()->Destroy(mMaterial);
	delete mMaterial; mMaterial = nullptr;
}
