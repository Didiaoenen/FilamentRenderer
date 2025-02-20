#include "Core.FRTextureLoader.h"

#include "Core.FRTexture.h"

FR::FRTexture* FR::FRTextureLoader::Create(const std::string& pFilePath, FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap)
{
    uint8_t* data;
    uint32_t size, width, height;
    if (__STBI.LoadImage(pFilePath, &data, &size, &width, &height))
    {
        FRTexture* result = new FRTexture(width, height);
        result->SetData(data, size);
        result->SetSampler();
        return result;
    }
    return nullptr;
}

FR::FRTexture* FR::FRTextureLoader::CreatePixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	std::array<uint8_t, 4> colorData = { r, g, b, a };
	return FRTextureLoader::CreateFromMemory(colorData.data(), 1, 1, FRTextureSamplerWarp::EMinFilter::NEAREST, FRTextureSamplerWarp::EMagFilter::NEAREST, false);
}

FR::FRTexture* FR::FRTextureLoader::CreateFromMemory(uint8_t* pData, uint32_t pWidth, uint32_t pHeight,
    FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap)
{
    FRTexture* result = new FRTexture(pWidth, pHeight);
    result->SetData(pData, 4);
    result->SetSampler();
    return result;
}

void FR::FRTextureLoader::Reload(FRTexture* pTexture, const std::string& pFilePath, FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap)
{
}

void FR::FRTextureLoader::Destroy(FRTexture*& pTexture)
{
    delete pTexture; pTexture = nullptr;
}
