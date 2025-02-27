#pragma once

namespace FR
{
    class FRTexture2D;
    class FRSkyboxWarp;
    class FRIndirectLightWarp;

    class FREnvironment
    {
    public:
        FREnvironment(FRTexture2D* pSkybox, FRTexture2D* pIBL);

        FRSkyboxWarp* GetSkybox();

        FRIndirectLightWarp* GetIndirectLight();

    public:
        FRSkyboxWarp* mSkybox;

        FRIndirectLightWarp* mIndirectLight;

    };
}