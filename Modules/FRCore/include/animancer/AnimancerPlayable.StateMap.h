#pragma once

#include <any>
#include <map>
#include <string>
#include <typeindex>
#include <functional>

namespace FR
{
	class AnimationClip;
	class AnimancerState;
	class AnimancerPlayable;

	class StateMap
	{
	public:
		StateMap(AnimancerPlayable* pRoot);

		AnimancerState* Create(AnimationClip* pClip);

		AnimancerState* Create(std::any pKey, AnimationClip* pClip);

		AnimancerState* GetOrCreate(AnimationClip* pClip, bool pAllowSetClip = false);

		AnimancerState* GetOrCreate(std::any pKey, AnimationClip* pClip, bool pAllowSetClip = false);

		AnimancerState* Current();

		void Register(AnimancerState* pState);

		void Unregister(AnimancerState* pState);

		bool TryGet(std::any pKey, AnimancerState*& pState);

		AnimancerState* operator[](AnimationClip* pClip);

	public:
		virtual ~StateMap();

	public:
		AnimancerPlayable* root{ nullptr };

	private:
		struct AnyComparator
		{
			bool operator()(const std::any& a, const std::any& b) const
			{
				auto getHash = [](const std::any& p)
					{
						size_t typeHash = std::type_index(p.type()).hash_code();

						if (p.type() == typeid(int))
						{
							return (typeHash << 32) | std::hash<int>{}(std::any_cast<int>(p));
						}
						else if (p.type() == typeid(std::string))
						{
							return (typeHash << 32) | std::hash<std::string>{}(std::any_cast<std::string>(p));
						}
						else if (p.type() == typeid(AnimationClip*))
						{
							return (typeHash << 32) | std::hash<AnimationClip*>{}(std::any_cast<AnimationClip*>(p));
						}

						return typeHash << 32;
					};

				return getHash(a) < getHash(b);
			}
		};

		std::map<std::any, AnimancerState*, AnyComparator> mStates;

	};
}