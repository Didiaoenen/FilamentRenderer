#pragma once

#include "Core.FRObject.h"
#include "Core.FRIInspectorItem.h"

#include <Tools.FREvent.h>

#include <glm/ext.hpp>

namespace FR
{
	class FRActor;

	class FRComponent
		: public FRObject, public FRIInspectorItem
	{
	public:

		enum class EComponentType : uint8_t
		{
			BEHAVIOUR,
			TRANSFORM,
			LIGHT,
			CAMERA,
			MODEL_RENDERER,
			MATERIAL_RENDERER,
			ANIMATOR,
		};

		FRComponent(FRActor& pOwner);

		virtual void OnAwake() {}

		virtual void OnStart() {}

		virtual void OnEnable() {}

		virtual void OnDisable() {}

		virtual void OnDestroy() {}

		virtual void OnUpdate(float pDeltaTime) {}

		virtual void OnFixedUpdate(float pDeltaTime) {}

		virtual void OnLateUpdate(float pDeltaTime) {}

		virtual const std::string GetName() = 0;

		virtual EComponentType GetType() = 0;

	public:
		virtual ~FRComponent();

	public:
		FRActor& owner;

	};
}

