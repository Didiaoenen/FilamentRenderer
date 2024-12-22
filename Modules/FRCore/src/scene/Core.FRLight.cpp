#include "Core.FRLight.h"

#include <FREngineWarp.h>
#include <FRFilamentHelper.h>
#include <FRLightManagerWarp.h>

FR::FRLight::FRLight(FROptRef<FRTransform> pTransform)
	: FREntity(pTransform)
{

}

void FR::FRLight::CreateLight(ELightType pLightType)
{
	type = pLightType;
	auto engine = FRFilamentHelper::GetEngine();
	FRFilamentHelper::GetLightManager()->Destroy(mEntity);
	FRLightManagerWarp::Builder(ConvertEnum(pLightType)).Build(engine, mEntity);
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
	case FR::ELightType::SUN:
	case FR::ELightType::DIRECTIONAL:
		manager->SetIntensity(manager->GetInstance(mEntity), intensity);
		break;
	case FR::ELightType::POINT:
		manager->SetFalloff(manager->GetInstance(mEntity), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity), intensity, filament::LightManager::EFFICIENCY_LED);
		break;
	case FR::ELightType::FOCUSED_SPOT:
	case FR::ELightType::SPOT:
		manager->SetFalloff(manager->GetInstance(mEntity), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity), intensity, filament::LightManager::EFFICIENCY_LED);
		manager->SetSpotLightCone(manager->GetInstance(mEntity), inner, outer);
		break;
	default:
		break;
	}
}