#include "Core.FRMaterial.h"

#include "Core.FRMesh.h"
#include "Core.FRShader.h"
#include "Core.FRTexture.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRSerializer.h"

#include <MathConvert.h>
#include <FRMaterialWarp.h>
#include <FRMaterialInstanceWarp.h>

FR::FRMaterial::FRMaterial(FRShader* pShader)
{
	SetShader(pShader);
}

void FR::FRMaterial::SetShader(FRShader* pShader, bool pClearProps)
{
	mShader = pShader;

	if (mShader)
	{
		mShader->material = this;
		mMaterialInstance = mShader->CreateInstance();

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

FR::FRShader*& FR::FRMaterial::GetShader()
{
	return mShader;
}

bool FR::FRMaterial::HasShader() const
{
	return mShader;
}

bool FR::FRMaterial::IsValid() const
{
	return HasShader();
}

void FR::FRMaterial::SetTransparencyMode(FRMaterialInstanceWarp::ETransparencyMode pModel)
{
	mMaterialInstance->SetTransparencyMode(pModel);
}

void FR::FRMaterial::SetCullingMode(FRMaterialInstanceWarp::ECullingMode pModel)
{
	mMaterialInstance->SetCullingMode(pModel);
}

void FR::FRMaterial::SetDepthCulling(bool pCulling)
{
	mMaterialInstance->SetDepthCulling(pCulling);
}

void FR::FRMaterial::SetDepthWrite(bool pWrite)
{
	mMaterialInstance->SetDepthWrite(pWrite);
}

void FR::FRMaterial::SetColorWrite(bool pWrite)
{
	mMaterialInstance->SetColorWrite(pWrite);
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
					mMaterialInstance->SetParameter(prop.name.c_str(), std::any_cast<bool>(prop.data));
				}
				break;
			case FRMaterialWarp::EUniformType::INT:
				if (prop.data.type() == typeid(int))
				{
					mMaterialInstance->SetParameter(prop.name.c_str(), std::any_cast<int>(prop.data));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT:
				if (prop.data.type() == typeid(float))
				{
					mMaterialInstance->SetParameter(prop.name.c_str(), std::any_cast<float>(prop.data));
				}
			break;
			case FRMaterialWarp::EUniformType::FLOAT2:
				if (prop.data.type() == typeid(glm::vec2))
				{
					mMaterialInstance->SetParameter(prop.name.c_str(), MathConvert::ToFVec2(std::any_cast<glm::vec2>(prop.data)));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT3:
				if (prop.data.type() == typeid(glm::vec3))
				{
					mMaterialInstance->SetParameter(prop.name.c_str(), MathConvert::ToFVec3(std::any_cast<glm::vec3>(prop.data)));
				}
				break;
			case FRMaterialWarp::EUniformType::FLOAT4:
				if (prop.data.type() == typeid(glm::vec4))
				{
					mMaterialInstance->SetParameter(prop.name.c_str(), MathConvert::ToFVec4(std::any_cast<glm::vec4>(prop.data)));
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
						mMaterialInstance->SetParameter(prop.name.c_str(), tex->NativePtr(), tex->GetSampler());
					}
					else if (auto emptyTex = FRGuiDrawer::GetEmptyTexture())
					{
						mMaterialInstance->SetParameter(prop.name.c_str(), emptyTex->NativePtr(), emptyTex->GetSampler());
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

std::vector<FR::FRPropInfo>& FR::FRMaterial::GetPropInfos()
{
	return mPropInfos;
}

FR::FRPropInfo* FR::FRMaterial::GetPropInfo(const std::string& pName)
{
	auto found = std::find_if(mPropInfos.begin(), mPropInfos.end(), [&pName](const FRPropInfo& pElement)
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

	FRShader* deserializedShader = FRSerializer::DeserializeShader(pDoc, pNode, "shader");

	if (deserializedShader)
	{
		SetShader(deserializedShader);

		tinyxml2::XMLNode* uniformsNode = pNode->FirstChildElement("properties");

		if (uniformsNode)
		{
			for (auto property = uniformsNode->FirstChildElement("property"); property; property = property->NextSiblingElement("property"))
			{
				if (auto uniformNameElement = property->FirstChildElement("name"))
				{
					auto propInfo = GetPropInfo(uniformNameElement->GetText());

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

FR::FRMaterialInstanceWarp* FR::FRMaterial::GetMaterialInstance()
{
	return mMaterialInstance;
}

std::map<uint64_t, FR::FRMesh*> FR::FRMaterial::GetRefMeshs()
{
	return mRefMeshs;
}

void FR::FRMaterial::SetRefMesh(FRMesh* pMesh)
{
	mRefMeshs.emplace(pMesh->mUUID, pMesh);
}
