#include "GUI.FRAPanelTrans.h"

#include <MathConvert.h>

#include <imgui.h>

FR::GUI::FRAPanelTrans::FRAPanelTrans(glm::vec2 pDefaultPosition, glm::vec2 pDefaultSize,
	EPanelHorizontal pDefaultHAlignment, EPanelVertical pDefaultVAlignment, bool pIgnoreConfigFile)
	: mDefaultPosition(pDefaultPosition)
	, mDefaultSize(pDefaultSize)
	, mDefaultHAlignment(pDefaultHAlignment)
	, mDefaultVAlignment(pDefaultVAlignment)
	, mIgnoreConfigFile(pIgnoreConfigFile)
{
}

void FR::GUI::FRAPanelTrans::SetPosition(glm::vec2 pPosition)
{
	mPosition = pPosition;
	mPositionChanged = true;
}

void FR::GUI::FRAPanelTrans::SetSize(glm::vec2 pSize)
{
	mSize = pSize;
	mSizeChanged = true;
}

void FR::GUI::FRAPanelTrans::SetAlignment(EPanelHorizontal pHAlignment, EPanelVertical pVAlignment)
{
	mHAlignment = pHAlignment;
	mVAlignment = pVAlignment;
	mAlignmentChanged = true;
}

const glm::vec2& FR::GUI::FRAPanelTrans::GetPosition() const
{
	return mPosition;
}

const glm::vec2& FR::GUI::FRAPanelTrans::GetSize() const
{
	return mSize;
}

FR::GUI::EPanelHorizontal FR::GUI::FRAPanelTrans::GetHorizontalAlignment() const
{
	return mHAlignment;
}

FR::GUI::EPanelVertical FR::GUI::FRAPanelTrans::GetVerticalAlignment() const
{
	return mVAlignment;
}

void FR::GUI::FRAPanelTrans::Update()
{
	if (!mFirstFrame)
	{
		if (!autoSize)
		{
			UpdateSize();
		}
		CopyImGuiSize();

		UpdatePosition();
		CopyImGuiPosition();
	}

	mFirstFrame = false;
}

glm::vec2 FR::GUI::FRAPanelTrans::CalculatePositionAlignmentOffset(bool pDefault)
{
	glm::vec2 result(0.0f, 0.0f);

	switch (pDefault ? mDefaultHAlignment : mHAlignment)
	{
	case EPanelHorizontal::CENTER:
		result.x -= mSize.x / 2.0f;
		break;
	case EPanelHorizontal::RIGHT:
		result.x -= mSize.x;
		break;
	}

	switch (pDefault ? mDefaultVAlignment : mVAlignment)
	{
	case EPanelVertical::MIDDLE:
		result.y -= mSize.y / 2.0f;
		break;
	case EPanelVertical::BOTTOM:
		result.y -= mSize.y;
		break;
	}

	return result;
}

void FR::GUI::FRAPanelTrans::UpdatePosition()
{
	if (mDefaultPosition != glm::vec2(-1.f, -1.f))
	{
		glm::vec2 offsettedDefaultPos = mDefaultPosition + CalculatePositionAlignmentOffset(true);
		ImGui::SetWindowPos(MathConvert::ToImVec2(offsettedDefaultPos), mIgnoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
	}

	if (mPositionChanged || mAlignmentChanged)
	{
		glm::vec2 offset = CalculatePositionAlignmentOffset(false);
		glm::vec2 offsettedPos(mPosition.x + offset.x, mPosition.y + offset.y);
		ImGui::SetWindowPos(MathConvert::ToImVec2(offsettedPos), mIgnoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
		mPositionChanged = false;
		mAlignmentChanged = false;
	}
}

void FR::GUI::FRAPanelTrans::UpdateSize()
{
	if (mSizeChanged)
	{
		mSizeChanged = false;
		ImGui::SetWindowSize(MathConvert::ToImVec2(mSize), ImGuiCond_Always);
	}
}

void FR::GUI::FRAPanelTrans::CopyImGuiPosition()
{
	mPosition = MathConvert::ToGlmVec2(ImGui::GetWindowPos());
}

void FR::GUI::FRAPanelTrans::CopyImGuiSize()
{
	mSize = MathConvert::ToGlmVec2(ImGui::GetWindowSize());
}
