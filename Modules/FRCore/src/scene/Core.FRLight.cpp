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
	FRFilamentHelper::GetLightManager()->Destroy(mEntity->GetEntity());
	FRLightManagerWarp::Builder(pType).Build(engine, mEntity->GetEntity());
}

void FR::FRLight::UploadData()
{
	auto manager = FRFilamentHelper::GetLightManager();

	manager->SetColor(manager->GetInstance(mEntity->GetEntity()), color);
	manager->SetPosition(manager->GetInstance(mEntity->GetEntity()), mEntity->GetTransform().GetWorldPosition());
	manager->SetDirection(manager->GetInstance(mEntity->GetEntity()), -mEntity->GetTransform().GetWorldForward());
	manager->SetShadowCaster(manager->GetInstance(mEntity->GetEntity()), shadowCaster);

	switch (type)
	{
	case FRLightManagerWarp::EType::SUN:
	case FRLightManagerWarp::EType::DIRECTIONAL:
		manager->SetIntensity(manager->GetInstance(mEntity->GetEntity()), intensity);
		break;
	case FRLightManagerWarp::EType::POINT:
		manager->SetFalloff(manager->GetInstance(mEntity->GetEntity()), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity->GetEntity()), intensity, FRLightManagerWarp::C_EFFICIENCY_LED);
		break;
	case FRLightManagerWarp::EType::FOCUSED_SPOT:
	case FRLightManagerWarp::EType::SPOT:
		manager->SetFalloff(manager->GetInstance(mEntity->GetEntity()), falloff);
		manager->SetIntensity(manager->GetInstance(mEntity->GetEntity()), intensity, FRLightManagerWarp::C_EFFICIENCY_LED);
		manager->SetSpotLightCone(manager->GetInstance(mEntity->GetEntity()), inner, outer);
		break;
	default:
		break;
	}
}

FR::FREntityWarp* FR::FRLight::GetEntity() const
{
	return mEntity->GetEntity();
}

FR::FRLight::~FRLight()
{
}
