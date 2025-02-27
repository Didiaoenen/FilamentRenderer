#pragma once

#include "Core.FRAsset.h"
#include "Core.FRShader.h"
#include "Core.FRISerializable.h"
#include <FRMaterialInstanceWarp.h>

#include <any>
#include <map>
#include <string>
#include <vector>

namespace FR
{
	class FRMesh;
	class FRRenderable;

	class FRMaterial
		: public FRAsset, public FRISerializable
	{
	public:
		FRMaterial(FRShader* pShader = nullptr);

		void SetShader(FRShader* pShader, bool pClearProps = true);

		void SetTransparencyMode(FRMaterialInstanceWarp::ETransparencyMode pModel);

		void SetCullingMode(FRMaterialInstanceWarp::ECullingMode pModel);

		void SetDepthCulling(bool pCulling);

		void SetDepthWrite(bool pWrite);

		void SetColorWrite(bool pWrite);

		void UploadData() const;

		FRShader* GetShader();

		std::vector<FRPropInfo>& GetPropInfos();

		FRPropInfo* GetPropInfo(const std::string& pName);

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		FRMaterialInstanceWarp* NativePtr();

		std::map<FRRenderable*, FRMesh*> GetRefMeshs();

		void SetRefMesh(FRRenderable* pRenderable, FRMesh* pMesh);

		template<typename T>
		const T& Get(const std::string pKey) const;

		template<typename T>
		void Set(const std::string pKey, const T& pValue);

		template<typename T>
		void SetParameter(const std::string& pName, const T& pValue);

	private:
		void DestroyNativePtr();

	public:
		virtual ~FRMaterial();

	private:
		FRMaterialInstanceWarp* mMaterial{ nullptr };

		FRShader* mShader{ nullptr };

		bool mBlendable{ false };
		bool mDepthTest{ true };
		bool mDepthWriting{ true };
		bool mColorWriting{ true };
		bool mBackfaceCulling{ true };
		bool mFrontfaceCulling{ false };

		std::vector<FRPropInfo> mPropInfos;

		std::map<FRRenderable*, FRMesh*> mRefMeshs;

	};
}

#include "Core.FRMaterial.inl"