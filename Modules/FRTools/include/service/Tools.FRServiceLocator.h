#pragma once

#include <any>
#include <unordered_map>

namespace FR
{
	#define GetService(Type) FRServiceLocator::Get<Type>()

	class FRServiceLocator
	{
	public:
		template<typename T>
		static void Provide(T& pService)
		{
			__SERVICES[typeid(T).hash_code()] = std::any(&pService);
		}

		template<typename T>
		static T& Get()
		{
			return *std::any_cast<T*>(__SERVICES[typeid(T).hash_code()]);
		}

	private:
		inline static std::unordered_map<size_t, std::any> __SERVICES;

	};
}

