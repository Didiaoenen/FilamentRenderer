#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Core.FRARenderer.h"
#include "Core.FRDescribable.h"

namespace FR
{
	class FRView;
	class ARenderFeature;

	class FRCompositeRenderer
		: public FRARenderer, public FRDescribable
	{
	public:
		FRCompositeRenderer();

		virtual bool BeginFrame(const FRFrameDescriptor& pFrameDescriptor);

		virtual void DrawFrame(FRView* pView) final;

		virtual void EndFrame() override;

		template<typename T, typename ... Args>
		T& AddFeature(Args&&... pArgs);

		template<typename T>
		bool RemoveFeature();

		template<typename T>
		T& GetFeature() const;

		template<typename T>
		bool HasFeature() const;

	protected:
		std::unordered_map<std::type_index, std::unique_ptr<ARenderFeature>> mFeatures;

	};
}

#include "Core.FRCompositeRenderer.inl"