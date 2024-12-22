#pragma once

#include <functional>
#include "GUI.FRAWidget.h"
#include "GUI.FRPluginTarget.h"
#include "GUI.FRWidgetContainer.h"

namespace FR::GUI
{
	class FRText;
	class FRGroup;
	class FRButton;
	class FRButtonSmall;

	class FRItemSelect
		: public FRAWidget, public FRWidgetContainer
	{
	public:
	
		enum class EItemType : uint8_t
		{
			MODEL,
			SHADER,
			MATERIAL,
			SKELETON,
			ANIMATION,
		};
		
		FRItemSelect(EItemType pType, const std::string& pText, glm::vec2 pPosition = { 120.f, 0.f });

		template<typename T, typename... TArgs>
		void SetDataReceivedChanged(T* tObject, void(T::* tCallback)(TArgs...), auto... tArgs)
		{
			auto argsTuple = std::make_tuple(tArgs...);
			mDataReceivedEvent += [this, tObject, tCallback, argsTuple = std::move(argsTuple)](std::pair<std::string, FRGroup*> p) mutable
				{
					std::apply([this, tObject, tCallback, p](auto&&... args) mutable
						{
							(tObject->*tCallback)(mContext, p, std::forward<decltype(args)>(args)...);
						}, argsTuple);
				};
		}

		void SetTextReceivedEvent(std::function<void(std::string&, std::pair<std::string, FRGroup*>)> pEvent);

		void SetText(const std::string& content);

		FRText* GetText();

	private:
		const char* GetItemIcon(EItemType pType);

	protected:

		virtual void _Draw_Impl() override;

	private:
		glm::vec2 mPosition;
		std::string mContext;
		EItemType mItemType;

		FRText* mIcon{ nullptr };
		FRText* mText{ nullptr };
		FRButton* mBG{ nullptr };
		FRButton* mSelect{ nullptr };

		FREvent<std::pair<std::string, FRGroup*>> mDataReceivedEvent;

	};
}

