#pragma once

#include <string>
#include <memory>

namespace FR
{
	class FRInput;
	class FRImGuiHelper;
	class FREngineWarp;

	class ProjectHub
	{
	public:

		struct Result
		{
			bool ready{ false };
			std::string path;
			std::string name;
		};

		ProjectHub();

		Result Run();

	public:
		~ProjectHub() = default;

	private:
		bool mReadyToGo{ false };
		std::string mProjectPath;
		std::string mProjectName;

		uint64_t mSkippedFrames{ 0 };

		std::unique_ptr<FRInput> mInput;
		std::unique_ptr<FRImGuiHelper> mGuiHelper;

	};
}
