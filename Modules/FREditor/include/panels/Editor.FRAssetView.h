#pragma once

#include <memory>
#include <variant>
#include <Core.FRScene.h>
#include <Core.FRMaterial.h>
#include <Core.FRGuiDrawer.h>
#include "Editor.FRAViewController.h"

namespace FR
{
	class FRActor;
	class FRModel;
	class CompModelRenderer;

	class FRAssetView
		: public FRAViewController
	{
	public:
		using ViewableResource = std::variant<FRModel*, FRTexture2D*, FRMaterial*>;

		FRAssetView(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		virtual FRScene* GetScene();

		void SetResource(ViewableResource pResource);

		void ClearResource();

		void SetTexture(FRTexture2D& pTexture);

		void SetModel(FRModel& pModel);

		void SetMaterial(FRMaterial& pMaterial);

		const ViewableResource& GetResource() const;

	private:
		FRScene mScene;
		ViewableResource mResource;

		FRMaterial mDefaultMaterial;
		FRMaterial mTextureMaterial;

		FRActor* mAssetActor{ nullptr };
		CompModelRenderer* mModelRenderer{ nullptr };

	};
}
