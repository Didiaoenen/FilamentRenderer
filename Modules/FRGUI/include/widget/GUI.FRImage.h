#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRImage
		: public FRAWidget
	{
	public:
		FRImage(void* pTextureID, const glm::vec2& pSize,
			const glm::vec2& pUV0 = { 0.f, 1.f }, const glm::vec2& pUV1 = { 1.f, 0.f });

	protected:
		void _Draw_Impl() override;

	public:
		void* textureID{ nullptr };

		glm::vec2 uv0{ 0.f, 1.f };
		glm::vec2 uv1{ 1.f, 0.f };

	};
}

