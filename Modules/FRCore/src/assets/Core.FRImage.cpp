#include "Core.FRImage.h"

FR::FRImage::FRImage(uint8_t* pData, uint32_t pSize, uint32_t pWidth, uint32_t pHeight)
	: data(pData)
	, size(pSize)
	, width(pWidth)
	, height(pHeight)
{
}

FR::FRImage::~FRImage()
{
	delete data; data = nullptr;
}
