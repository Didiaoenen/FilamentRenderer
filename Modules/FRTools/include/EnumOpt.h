#pragma once

#include <map>
#include <vector>

namespace FR
{
	#define ENUM_STR(ENUM) #ENUM

	#define ENUM_OPT(Enum) inline Enum operator~ (Enum a) { return (Enum)~(int)a; } \
		inline Enum operator| (Enum a, Enum b) { return (Enum)((int)a | (int)b); } \
		inline Enum operator& (Enum a, Enum b) { return (Enum)((int)a & (int)b); } \
		inline Enum operator^ (Enum a, Enum b) { return (Enum)((int)a ^ (int)b); } \
		inline Enum& operator|= (Enum& a, Enum b) { return (Enum&)((int&)a |= (int)b); } \
		inline Enum& operator&= (Enum& a, Enum b) { return (Enum&)((int&)a &= (int)b); } \
		inline Enum& operator^= (Enum& a, Enum b) { return (Enum&)((int&)a ^= (int)b); }

	#define ENUM_VEC(ENUM, ...) static std::vector<ENUM> ENUM##Vec { ##__VA_ARGS__ };

	#define ENUM_MAP(ENUM, ...) static std::map<std::string, ENUM> ENUM##Str { ##__VA_ARGS__ };
}