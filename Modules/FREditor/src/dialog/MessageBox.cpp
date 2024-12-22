#include "MessageBox.h"

#include <windows.h>

#undef MessageBox
#undef IGNORE
#undef ERROR

FR::MessageBox::MessageBox(std::string pTitle, std::string pMessage, EMessageType pMessageType, EButtonLayout pButtonLayout, bool pAutoSpawn)
	: mTitle(pTitle)
	, mMessage(pMessage)
	, mMessageType(pMessageType)
	, mButtonLayout(pButtonLayout)
{
	if (pAutoSpawn)
	{
		Spawn();
	}
}

void FR::MessageBox::Spawn()
{
	int msgboxID = MessageBoxA
	(
		nullptr,
		static_cast<LPCSTR>(mMessage.c_str()),
		static_cast<LPCSTR>(mTitle.c_str()),
		static_cast<UINT>(mMessageType) | static_cast<UINT>(mButtonLayout) | MB_DEFBUTTON2
	);

	mUserResult = static_cast<EUserAction>(msgboxID);
}

const FR::EUserAction& FR::MessageBox::GetUserAction() const
{
	return mUserResult;
}
