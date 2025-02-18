#pragma once

#include "Core.FREntity.h"

#include <Color.h>
#include <FRLightManagerWarp.h>

namespace FR
{
	class FRLight
		: public FREntity
	{
	public:
		FRLight(FREntityWarp* pEntity, FROptRef<FRTransform> pTransform = std::nullopt);

		void CreateLight(FRLightManagerWarp::EType pType);

		void UploadData();

	public:
		virtual ~FRLight();

	public:
		FRLightManagerWarp::EType type{ FRLightManagerWarp::EType::DIRECTIONAL };

		glm::vec3 position{ 0.f };
		glm::vec3 direction{ 0.f };

		bool shadowCaster{ true };

		float inner{ glm::pi<float>() / 8 };
		float outer{ (glm::pi<float>() / 8) * 1.1 };
		float falloff{ 10.f };
		float intensity{ 32000.f };
		float sunAngular{ 1.9f };
		float outerCutoff{ 15.f };
		float quadratic{ 1.f };
		float constant{ 0.f };
		float cutoff{ 12.f };
		float linear{ 0.f };

		Color color{ 255 / 255.f, 244 / 255.f, 214 / 255.f };

	};
}