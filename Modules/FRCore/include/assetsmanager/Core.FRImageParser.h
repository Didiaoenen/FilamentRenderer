#pragma once

#include <string>

namespace FR
{
	class FRImageParser
	{
	public:
		bool LoadImage(const std::string& pFileName, uint8_t** pData, uint32_t* pSize, uint32_t* pWidth, uint32_t* pHeight);
	
	};
}

