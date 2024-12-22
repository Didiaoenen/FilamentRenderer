#include "Core.FRImageParser.h"

#include <stb_image.h>

bool FR::FRImageParser::LoadImage(const std::string& pFileName, uint8_t** pData, uint32_t* pSize, uint32_t* pWidth, uint32_t* pHeight)
{
	int texChannels = 0;
	if (stbi_uc* pixels = stbi_load(pFileName.c_str(), (int*)pWidth, (int*)pHeight, &texChannels, STBI_rgb_alpha))
	{
		*pSize = (*pWidth) * (*pHeight) * 4;
		*pData = new uint8_t[*pSize];
		memcpy(*pData, pixels, *pSize);

		stbi_image_free(pixels);
		return true;
	}
	return false;
}
