
#include <Process.h>
#include <SystemExec.h>
#include <StringExtension.h>
#include <Tools.FRPathUtils.h>

#include <utils/Path.h>

#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>

int main()
{
	std::string modelPath = "../../../Tools/Convert2OzzAnimation/Animations/";//"../../../Projects/FET/Assets/Animations/";
	auto directory = std::filesystem::directory_entry(modelPath);
	for (const auto& item : std::filesystem::directory_iterator(directory))
	{
		if (item.is_directory())
		{

		}
		else
		{
			auto path = item.path().string();
			auto name = FR::FRPathUtils::GetElementName(path);
			auto extPath = FR::FRPathUtils::GetExtension(path);
			std::transform(extPath.begin(), extPath.end(), extPath.begin(), ::tolower);
			
			std::string exeName = "";
			if (extPath == "fbx")
			{
				exeName = utils::Path("../../../Resources/Bin/fbx2ozz").getAbsolutePath();
			}
			else if (extPath == "gltf")
			{
				exeName = utils::Path("../../../Resources/Bin/gltf2ozz").getAbsolutePath();
			}

			if (!exeName.empty())
			{
				std::string config = "{\"animations\":[{\"filename\":\"{0}.anim\"}]}";

				FR::StringExtension::Replace(name, "." + extPath, "");
				FR::StringExtension::Replace(config, "{0}", modelPath + name);

				std::string configPath = "../../../Resources/Bin/config.json";

				std::fstream file(configPath, std::ios::out);

				file << config;

				file.close();

				std::string pragmaList = { " --file={0} --config_file={1}" };

				std::string commandLine = exeName + pragmaList;

				FR::StringExtension::Replace(commandLine, "{0}", utils::Path(path).getAbsolutePath());
				FR::StringExtension::Replace(commandLine, "{1}", utils::Path(configPath).getAbsolutePath());

				FR::SystemExec::Exec(commandLine);
			}
		}
	}
}
