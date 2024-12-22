#pragma once

#include <string>

namespace FR
{
	enum class EMessageType
	{
		QUESTION    = 0x00000020L,
		INFORMATION = 0x00000040L,
		WARNING     = 0x00000030L,
		ERROR       = 0x00000010L,
	};

	enum class EButtonLayout
	{
		OK                       = 0x00000000L,
		OK_CANCEL                = 0x00000001L,
		YES_NO                   = 0x00000004L,
		YES_NO_CANCEL            = 0x00000003L,
		RETRY_CANCEL             = 0x00000005L,
		ABORT_RETRY_IGNORE       = 0x00000002L,
		CANCEL_TRYAGAIN_CONTINUE = 0x00000006L,
		HELP                     = 0x00004000L,
	};

	enum class EUserAction
	{
		OK       = 1,
		CANCEL   = 2,
		RETRY    = 4,
		IGNORE   = 5,
		YES      = 6,
		NO       = 7,
		TRYAGAIN = 10,
		CONTINUE = 11,
	};

	class MessageBox
	{
	public:
		MessageBox(std::string pTitle, std::string pMessage, EMessageType pMessageType = EMessageType::INFORMATION, EButtonLayout pButtonLayout = EButtonLayout::OK, bool pAutoSpawn = true);

		void Spawn();

		const EUserAction& GetUserAction() const;

	private:
		std::string	mTitle;
		std::string	mMessage;
		EMessageType mMessageType;
		EButtonLayout mButtonLayout;

		EUserAction	mUserResult{ EUserAction::OK };

	};
}

