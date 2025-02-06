#include "GUI.FRImage.h"
#include <Core.FRTexture.h>

FR::GUI::FRImage::FRImage(void* pTextureID, const glm::vec2& pSize, glm::vec2 pUV0, glm::vec2 pUV1)
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

		FR::FRTexture* texture = static_cast<FR::FRTexture*>(textureID);
		ImGui::Image(texture->NativePtr(), MathConvert::ToImVec2(size), MathConvert::ToImVec2(uv0), MathConvert::ToImVec2(uv1));
	}
}
