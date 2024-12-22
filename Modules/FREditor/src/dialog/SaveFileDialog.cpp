#include "SaveFileDialog.h"

#include <windows.h>

FR::SaveFileDialog::SaveFileDialog(const std::string& pDialogTitle)
	: FileDialog(GetSaveFileNameA, pDialogTitle)
{
}

void FR::SaveFileDialog::Show(EExplorerFlags pFlags)
{
	FileDialog::Show(pFlags);

	if (mSucceeded)
	{
		AddExtensionToFilePathAndName();
	}
}

void FR::SaveFileDialog::DefineExtension(const std::string& pLabel, const std::string& pExtension)
{
	mFilter = pLabel + '\0' + '*' + pExtension + '\0';
	mExtension = pExtension;
}

void FR::SaveFileDialog::AddExtensionToFilePathAndName()
{
	if (mFileName.size() >= mExtension.size())
	{
		std::string fileEnd(mFileName.data() + mFileName.size() - mExtension.size(), mFileName.data() + mFileName.size());

		if (fileEnd != mExtension)
		{
			mFilePath += mExtension;
			mFileName += mExtension;
		}
	}
	else
	{
		mFilePath += mExtension;
		mFileName += mExtension;
	}
}
