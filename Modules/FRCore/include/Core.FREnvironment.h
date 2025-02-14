#pragma once

namespace FR
{
    class FRTexture;
    class FRSkyboxWarp;
    class FRIndirectLightWarp;

    class FREnvironment
    {
    public:
        FREnvironment(FRTexture* pSkybox, FRTexture* pIBL);

        FRSkyboxWarp* GetSkybox();

        FRIndirectLightWarp* GetIndirectLight();

    public:
        FRSkyboxWarp* mSkybox;

        FRIndirectLightWarp* mIndirectLight;

    };
}