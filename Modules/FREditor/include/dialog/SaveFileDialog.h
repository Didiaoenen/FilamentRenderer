#pragma once

#include "FileDialog.h"

namespace FR
{
	class SaveFileDialog
		: public FileDialog
	{
	public:
		SaveFileDialog(const std::string& pDialogTitle);

		virtual void Show(EExplorerFlags pFlags = flags) override;

		void DefineExtension(const std::string& pLabel, const std::string& pExtension);

	private:
		void AddExtensionToFilePathAndName();

	private:
		std::string mExtension;

	};
}

