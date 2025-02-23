#include "Core.FRLight.h"
#include "Core.FREntity.h"

#include <FREngineWarp.h>
#include <FRFilamentHelper.h>
#include <FRLightManagerWarp.h>

FR::FRLight::FRLight(FREntity* pEntity)
	: mEntity(pEntity)
{
}

void FR::FRLight::CreateLight(FRLightManagerWarp::EType pType)
{
	type = pType;
	auto engine = FRFilamentHelper::GetEngine();
	FRFilamentHelper::GetLightManager()->Destroy(mEntity->NatrivePtr());
	FRLightManagerWarp::Builder(pType).Build(engine, mEntity->NatrivePtr());
}

void FR::FRLight::UploadData()
{
	auto manager = FRFilamentHelper::GetLightManager();

	manager->SetColor(manager->GetInstance(mEntity->NatrivePtr()), color);
	manager->SetPosition(manager->GetInstance(mEntity->NatrivePtr()), mEntity->GetTransform().GetWorldPosition());
	manager->SetDirection(manager->GetInstance(mEntity->NatrivePtr()), -mEntity->GetTransform().GetWorldForward());
	manager->SetShadowCaster(manager->GetInstance(mEntity->NatrivePtr()), shadowCaster);

	switch (type)
	{
	case FRLightManagerWarp::EType::SUN:
	case FRLightManagerWarp::EType::DIRECTIONAL:
		manager->SetIntensity(manager->GetInstance(mEntity->NatrivePtr()), intensity);
		break;
	case FRLightManagerWarp::EType::POINT:
		manager->SetFalloff(manager->GetInstance(mEntity->NatrivePtr()), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity->NatrivePtr()), intensity, FRLightManagerWarp::C_EFFICIENCY_LED);
		break;
	case FRLightManagerWarp::EType::FOCUSED_SPOT:
	case FRLightManagerWarp::EType::SPOT:
		manager->SetFalloff(manager->GetInstance(mEntity->NatrivePtr()), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity->NatrivePtr()), intensity, FRLightManagerWarp::C_EFFICIENCY_LED);
		manager->SetSpotLightCone(manager->GetInstance(mEntity->NatrivePtr()), inner, outer);
		break;
	default:
		break;
	}
}

FR::FREntity* FR::FRLight::GetEntity()
{
	return mEntity;
}

FR::FRLight::~FRLight() = default;