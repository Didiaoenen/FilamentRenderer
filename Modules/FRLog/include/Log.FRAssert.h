#pragma once

#include <string>
#include <cassert>

namespace FR
{
	class FRAssert
	{
	public:
		static void Assert(bool pCondition, const std::string& pMessage = "")
		{
			assert(pCondition && pMessage.c_str());
		}

	};
}