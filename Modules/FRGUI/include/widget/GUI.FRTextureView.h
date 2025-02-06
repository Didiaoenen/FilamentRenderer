#pragma once

#include "GUI.FRAWidget.h"

namespace FR
{
	class FRTexture;
}

namespace FR::GUI
{
    class FRTextureView
        : public FRAWidget
    {
    public:
        FRTextureView(const glm::vec2& pSize, FRTexture* pBackgroud);

        void SetClickedEvent(std::function<void()> pEvent);

        void SetTexture(FRTexture* pBackgroud);

        void _Draw_Impl() override;

    private:
		FRTexture* backgroud{ nullptr };

        FREvent<> mClickedEvent;
    };
}