#include "GUI.FRLayout.h"

FR::GUI::FRDummy::FRDummy(const glm::vec2& pSize)
{
	size = pSize;
}

void FR::GUI::FRDummy::_Draw_Impl()
{
	ImGui::Dummy(MathConvert::ToImVec2(size));
}

FR::GUI::FRGroup::FRGroup(const std::string& pName)
	: FRAWidget(pName)
{
}

void FR::GUI::FRGroup::_Draw_Impl()
{
	DrawWidgets();
}

FR::GUI::FRGroupCollapsable::FRGroupCollapsable(const std::string& pName)
	: name(pName)
{
}

void FR::GUI::FRGroupCollapsable::_Draw_Impl()
{
	bool previouslyOpened = opened;

	if (ImGui::CollapsingHeader(name.c_str(), closable ? &opened : nullptr))
	{
		FRGroup::_Draw_Impl();
	}

	if (opened != previouslyOpened)
	{
		if (opened)
		{
			OpenEvent.Invoke();
		}
		else
		{
			CloseEvent.Invoke();
		}
	}
}

void FR::GUI::FRNewLine::_Draw_Impl()
{
	ImGui::NewLine();
}

FR::GUI::FRSpacing::FRSpacing(uint16_t pSpaces)
	: spaces(pSpaces)
{
}

void FR::GUI::FRSpacing::_Draw_Impl()
{
	for (uint16_t i = 0; i < spaces; ++i)
	{
		ImGui::Spacing();

		if (i + 1 < spaces)
		{
			ImGui::SameLine();
		}
	}
}

FR::GUI::FRTreeNode::FRTreeNode(const std::string& pName, const std::string& pOpenIcon, const std::string& pCloseIcon, bool pArrowClickToOpen)
	: FRDataWidget(name)
	, name(pName)
	, mOpenIcon(pOpenIcon)
	, mCloseIcon(pCloseIcon)
	, mArrowClickToOpen(pArrowClickToOpen)
{
	mAutoExecutePlugins = false;
}

void FR::GUI::FRTreeNode::Open()
{
	mShouldOpen = true;
	mShouldClose = false;
}

void FR::GUI::FRTreeNode::Close()
{
	mShouldClose = true;
	mShouldOpen = false;
}

bool FR::GUI::FRTreeNode::IsOpened() const
{
	return mOpened;
}

void FR::GUI::FRTreeNode::_Draw_Impl()
{
	SetItemLayout();

	bool prevOpened = mOpened;

	if (mShouldOpen || prevOpened)
	{
		ImGui::SetNextItemOpen(true);
		mShouldOpen = false;
	}
	else if (mShouldClose || !prevOpened)
	{
		ImGui::SetNextItemOpen(false);
		mShouldClose = false;
	}

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	if (mArrowClickToOpen)	flags |= ImGuiTreeNodeFlags_OpenOnArrow;
	if (selected)			flags |= ImGuiTreeNodeFlags_Selected;
	if (framed)				flags |= ImGuiTreeNodeFlags_Framed;
	if (leaf)				flags |= ImGuiTreeNodeFlags_Leaf;

	bool opened;
	if (prevOpened)
	{
		opened = ImGui::TreeNodeEx(((mOpenIcon != "" ? mOpenIcon + " " : "") + name + mWidgetID).c_str(), flags);
	}
	else
	{
		opened = ImGui::TreeNodeEx(((mCloseIcon != "" ? mCloseIcon + " " : "") + name + mWidgetID).c_str(), flags);
	}

	if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
	{
		ClickedEvent.Invoke();

		if (ImGui::IsMouseDoubleClicked(0))
		{
			DoubleClickedEvent.Invoke();
		}
	}

	if (opened)
	{
		if (!prevOpened)
		{
			OpenedEvent.Invoke();
		}

		mOpened = true;

		ExecutePlugins();

		DrawWidgets();

		ImGui::TreePop();
	}
	else
	{
		if (prevOpened)
		{
			ClosedEvent.Invoke();
		}

		mOpened = false;

		ExecutePlugins();
	}
}
