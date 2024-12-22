#pragma once

namespace FR
{
	struct FRDrawable;

	class FRCompositeRenderer;

	class ARenderFeature
	{
		friend class FRCompositeRenderer;

	public:
		ARenderFeature(FRCompositeRenderer& pRenderer);

		void SetEnabled(bool pEnabled);

		bool IsEnabled() const;

	protected:
		virtual void OnBeginFrame();

		virtual void OnEndFrame();

		virtual void OnBeforeDraw(const FRDrawable& pDrawable);

		virtual void OnAfterDraw(const FRDrawable& pDrawable);

	public:
		virtual ~ARenderFeature() = default;

	protected:
		bool mEnabled = true;
		FRCompositeRenderer& mRenderer;

	};
}

