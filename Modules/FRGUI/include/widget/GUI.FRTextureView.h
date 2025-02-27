#pragma once

#include "GUI.FRAWidget.h"

namespace FR
{
	class FRTexture2D;
}

namespace FR::GUI
{
    class FRTextureView
        : public FRAWidget
    {
    public:
        FRTextureView(const glm::vec2& pSize, FRTexture2D* pBackgroud);

        void SetClickedEvent(std::function<void()> pEvent);

        void SetTexture(FRTexture2D* pBackgroud);

        void _Draw_Impl() override;

    private:
		FRTexture2D* backgroud{ nullptr };

        FREvent<> mClickedEvent;
    };
}