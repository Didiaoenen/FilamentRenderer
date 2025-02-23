#pragma once

#include <tinyxml2.h>

namespace FR
{
	class FRISerializable
	{
	public:
		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) = 0;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) = 0;
	};
}