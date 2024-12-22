#include "OpenFileDialog.h"

#include <windows.h>

FR::OpenFileDialog::OpenFileDialog(const std::string& pDialogTitle)
	: FileDialog(GetOpenFileNameA, pDialogTitle)
{
}

void FR::OpenFileDialog::AddFileType(const std::string& pLabel, const std::string& pFilter)
{
	mFilter += pLabel + '\0' + pFilter + '\0';
}
