#pragma once

#include "FileDialog.h"

namespace FR
{
	class OpenFileDialog
		: public FileDialog
	{
	public:
		OpenFileDialog(const std::string& pDialogTitle);

		void AddFileType(const std::string& pLabel, const std::string& pFilter);

	};
}

