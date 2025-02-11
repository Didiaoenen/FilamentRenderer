#include "Core.FRLight.h"

#include <FREngineWarp.h>
#include <FRFilamentHelper.h>
#include <FRLightManagerWarp.h>

FR::FRLight::FRLight(FROptRef<FRTransform> pTransform)
	: FREntity(pTransform)
{
}

void FR::FRLight::CreateLight(FRLightManagerWarp::EType pType)
{
	type = pType;
	auto engine = FRFilamentHelper::GetEngine();
	FRFilamentHelper::GetLightManager()->Destroy(mEntity);
	FRLightManagerWarp::Builder(pType).Build(engine, mEntity);
}

void FR::FRLight::UploadData()
{
	auto manager = FRFilamentHelper::GetLightManager();

	manager->SetColor(manager->GetInstance(mEntity), color);
	manager->SetPosition(manager->GetInstance(mEntity), transform->GetWorldPosition());
	manager->SetDirection(manager->GetInstance(mEntity), -transform->GetWorldForward());
	manager->SetShadowCaster(manager->GetInstance(mEntity), shadowCaster);

	switch (type)
	{
	case FRLightManagerWarp::EType::SUN:
	case FRLightManagerWarp::EType::DIRECTIONAL:
		manager->SetIntensity(manager->GetInstance(mEntity), intensity);
		break;
	case FRLightManagerWarp::EType::POINT:
		manager->SetFalloff(manager->GetInstance(mEntity), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity), intensity, filament::LightManager::EFFICIENCY_LED);
		break;
	case FRLightManagerWarp::EType::FOCUSED_SPOT:
	case FRLightManagerWarp::EType::SPOT:
		manager->SetFalloff(manager->GetInstance(mEntity), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity), intensity, filament::LightManager::EFFICIENCY_LED);
		manager->SetSpotLightCone(manager->GetInstance(mEntity), inner, outer);
		break;
	default:
		break;
	}
}