#pragma once

#include <vector>

namespace FR
{
	class AnimancerLayer;
	class AnimancerPlayable;
	class AnimationPlayable;

	class LayerVec
	{
	public:
		LayerVec(AnimancerPlayable* pRoot, AnimationPlayable*& pPlayable);

		AnimancerLayer* GetLayer(int pIndex);

		void SetCapacity(int pCapacity);

		void SetMinCount(int pMinCount);

		void SetCount(int pCount);

		AnimancerLayer* Add();

		AnimancerLayer* operator[](int pIndex);

	public:
		virtual ~LayerVec();

	public:
		AnimancerPlayable* root{ nullptr };

		inline static int defaultCapacity{ 4 };

	private:
		int mCount{ 0 };

		int mCapacity{ 0 };

		std::vector<AnimancerLayer*> mLayers;

	};
}