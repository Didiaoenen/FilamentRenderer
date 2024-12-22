#include "SystemCalls.h"
#include "Tools.FRPathUtils.h"

#include <windows.h>

void FR::SystemCalls::ShowInExplorer(const std::string& pPath)
{
	ShellExecuteA(NULL, "open", FRPathUtils::MakeWindowsStyle(pPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void FR::SystemCalls::OpenFile(const std::string& pFile, const std::string& pWorkingDir)
{
	ShellExecuteA(NULL, "open", FRPathUtils::MakeWindowsStyle(pFile).c_str(), NULL, pWorkingDir.empty() ? NULL : FRPathUtils::MakeWindowsStyle(pWorkingDir).c_str(), SW_SHOWNORMAL);
}

void FR::SystemCalls::EditFile(const std::string& pFile)
{
	ShellExecuteW(NULL, NULL, std::wstring(pFile.begin(), pFile.end()).c_str(), NULL, NULL, SW_NORMAL);
}

void FR::SystemCalls::OpenURL(const std::string& pUrl)
{
	ShellExecute(0, 0, pUrl.c_str(), 0, 0, SW_SHOW);
}
