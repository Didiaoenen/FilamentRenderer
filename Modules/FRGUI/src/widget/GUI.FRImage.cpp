#include "GUI.FRImage.h"
#include <Core.FRTexture2D.h>

FR::GUI::FRImage::FRImage(void* pTextureID, const glm::vec2& pSize, const glm::vec2& pUV0, const glm::vec2& pUV1)
	: textureID(pTextureID)
	, uv0(pUV0)
	, uv1(pUV1)
{
	size = pSize;
}

void FR::GUI::FRImage::_Draw_Impl()
{
	if (textureID)
	{
		SetItemLayout();

		FR::FRTexture2D* texture = static_cast<FR::FRTexture2D*>(textureID);
		ImGui::Image(texture->NativePtr(), MathConvert::ToImVec2(size), MathConvert::ToImVec2(uv0), MathConvert::ToImVec2(uv1));
	}
}
