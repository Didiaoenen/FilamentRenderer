#pragma once

#include <string>
#include <cstdint>
#include <glm/glm.hpp>

namespace FR
{
	class FRScene;
	class FRCamera;
	class FRViewWarp;
	class FRRenderTarget;

	class FRView
	{
	public:
		FRView();

		void SetScene(FRScene* pScene);

		void SetCamera(FRCamera* pCamera);

		void SetViewport(glm::vec4 pViewPort);

		void SetRenderTarget(FRRenderTarget* pRenderTarget);

		void SetVisibleLayers(uint8_t pSelect, uint8_t pValue);

		void SetFrustumCullingEnabled(bool bEnabled);

		void SetPostProcessingEnabled(bool bEnabled);

		void SetName(const std::string& pName);

		const std::string GetName();

		FRCamera* GetCamera();

		FRViewWarp* NativePtr();

	public:
		~FRView();

	private:
		FRViewWarp* mView{ nullptr };

		FRScene* mScene{ nullptr };
		FRCamera* mCamera{ nullptr };
		FRRenderTarget* mRenderTarget{ nullptr };
	};
}

