#include "Core.FREnvironment.h"
#include "Core.FRTexture2D.h"

#include <FRSkyboxWarp.h>
#include <FRIndirectLightWarp.h>
#include <FRFilamentHelper.h>

FR::FREnvironment::FREnvironment(FRTexture2D* pSkybox, FRTexture2D* pIBL)
{
	auto engine = FRFilamentHelper::GetEngine();

	mSkybox = FRSkyboxWarp::Builder()
		.Environment(pSkybox->NativePtr())
		.ShowSun(true)
		.Build(engine);

	mIndirectLight = FRIndirectLightWarp::Builder()
		.Reflections(pIBL->NativePtr())
		.Intensity(30000.f)
		.Build(engine);
}

FR::FRSkyboxWarp* FR::FREnvironment::GetSkybox()
{
	return mSkybox;
}

FR::FRIndirectLightWarp* FR::FREnvironment::GetIndirectLight()
{
	return mIndirectLight;
}
