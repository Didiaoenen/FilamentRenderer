#include "ProjectHub.h"
#include "Editor.FRApplication.h"

static void TryRun(const std::string& pProjectPath, const std::string& pProjectName)
{
	FR::FRApplication* app = nullptr;

	try
	{
		app = FR::FRApplication::Instance();
		app->Initialize(pProjectPath, pProjectName);
	}
	catch (...)
	{

	}

	if (app)
	{
		app->TryRun();
	}

	app->Destroy();
}

#include <typeinfo>

int main(int argc, char** argv)
{
	FR::ProjectHub::Result result;

	{
		FR::ProjectHub hub;

		if (argc < 2)
		{
			result = hub.Run();
		}
	}

	if (result.ready)
	{
		TryRun(result.path, result.name);
	}

	return EXIT_SUCCESS;
}