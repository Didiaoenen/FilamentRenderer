#pragma once

#include <Event.h>

namespace FR
{
	class FREditorSettings
	{
	public:
		template<typename T>
		class Property
		{
		public:
			Property(T pValue)
				: mValue(pValue)
			{
			}

			inline T& operator=(T pValue)
			{
				Set(pValue);
				return mValue;
			}

			inline void Set(T pValue)
			{
				mValue = pValue;
				OnValueChanged.Invoke(mValue);
			}

			inline operator T()
			{
				return mValue;
			}

			inline T Get() const
			{
				return mValue;
			}

		public:
			FREvent<T> OnValueChanged;

		private:
			T mValue;
		};

		FREditorSettings() = delete;

		inline static Property<bool> ShowGeometryBounds = { false };
		inline static Property<bool> ShowLightBounds = { false };
		inline static Property<bool> ShowGeometryFrustumCullingInSceneView = { false };
		inline static Property<bool> ShowLightFrustumCullingInSceneView = { false };
		inline static Property<float> LightBillboardScale = { 0.5f };
		inline static Property<float> TranslationSnapUnit = { 1.0f };
		inline static Property<float> RotationSnapUnit = { 15.0f };
		inline static Property<float> ScalingSnapUnit = { 1.0f };

	};
}