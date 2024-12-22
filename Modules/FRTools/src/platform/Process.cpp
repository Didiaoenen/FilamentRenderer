#include "Process.h"

#include <Log.FRLogger.h>
#include <Tools.FRPathUtils.h>

#include <windows.h>

void FR::Process::StartProcess(const std::string& pCommandLine)
{
	auto commandLine = FR::FRPathUtils::MakeWindowsStyle(pCommandLine);
	TCHAR* szCommandLine = (TCHAR*)malloc(commandLine.length() * sizeof(TCHAR));
	mbstowcs_s(NULL, (wchar_t*)szCommandLine, commandLine.length() + 1, commandLine.c_str(), _TRUNCATE);

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	//
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	//
	BOOL success = CreateProcess(
		NULL,				//
		szCommandLine,		//
		NULL,               //
		NULL,               //
		FALSE,              //
		0,                  //
		NULL,               //
		NULL,               //
		&si,                //
		&pi                 //
	);

	if (success)
	{
		//
		WaitForSingleObject(pi.hProcess, INFINITE);

		//
		DWORD exitCode;
		GetExitCodeProcess(pi.hProcess, &exitCode);

		//
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		//
		if (exitCode == 0)
		{
			FRLogger::Log("Successful", FRILogHandler::ELogLevel::LOG_ERROR);
		}
		else
		{
			FRLogger::Log("Failed", FRILogHandler::ELogLevel::LOG_ERROR);
		}
	}
	else
	{
		FRLogger::Log("CreateProcess() Exec Failed", FRILogHandler::ELogLevel::LOG_ERROR);
	}
}