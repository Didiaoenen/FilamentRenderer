#pragma once

#include <string>
#include <functional>
#include "EExplorerFlags.h"

struct tagOFNA;

namespace FR
{
	class FileDialog
	{
	public:
		using DialogCallback = std::function<int(tagOFNA*)>;

		FileDialog(DialogCallback pCallback, const std::string& pDialogTitle);

		void SetInitialDirectory(const std::string& pInitialDirectory);

		virtual void Show(EExplorerFlags pFlags = flags);

		std::string GetSelectedFileName();

		std::string GetSelectedFilePath();

		std::string GetErrorInfo();

		bool IsFileExisting();

		bool HasSucceeded();

	private:
		void HandleError();

	protected:
		inline static EExplorerFlags flags = EExplorerFlags::DONTADDTORECENT
			| EExplorerFlags::FILEMUSTEXIST
			| EExplorerFlags::HIDEREADONLY
			| EExplorerFlags::NOCHANGEDIR;

		DialogCallback mCallback;
		const std::string mDialogTitle;

		bool mSucceeded = false;

		std::string mFileName;
		std::string mFilePath;
		std::string mFilter;
		std::string mError;

	};
}

