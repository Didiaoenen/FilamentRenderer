
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
	std::string modelPath = "../../../Tools/Convert2OzzModel/Models/";//"../../../Projects/FET/Assets/Models/";
	auto directory = std::filesystem::directory_entry(modelPath);
	auto directoryItr = std::filesystem::directory_iterator(directory);
	
	for (const auto& item : directoryItr)
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
			
			std::string skelExeName = "";
			std::string modelExeName = "";
			if (extPath == "fbx")
			{
				skelExeName = utils::Path("../../../Resources/Bin/fbx2ozz").getAbsolutePath();
				modelExeName = utils::Path("../../../Resources/Bin/Fbx2Mesh").getAbsolutePath();
			}
			else if (extPath == "gltf")
			{
				skelExeName = utils::Path("../../../Resources/Bin/gltf2ozz").getAbsolutePath();
				modelExeName = utils::Path("../../../Resources/Bin/Gltf2Mesh").getAbsolutePath();
			}

			if (!skelExeName.empty() && !modelExeName.empty())
			{
				// skeleton
				std::string config = "{\"skeleton\":{\"filename\":\"{0}.skel\",\"import\":{\"enable\":true}}}";

				FR::StringExtension::Replace(name, "." + extPath, "");
				FR::StringExtension::Replace(config, "{0}", modelPath + name);

				std::string configPath = "../../../Resources/Bin/config.json";

				std::fstream file(configPath, std::ios::out);

				file << config;

				file.close();

				std::string pragmaList = { " --file={0} --config_file={1}" };

				std::string commandLine = skelExeName + pragmaList;

				FR::StringExtension::Replace(commandLine, "{0}", utils::Path(path).getAbsolutePath());
				FR::StringExtension::Replace(commandLine, "{1}", utils::Path(configPath).getAbsolutePath());

				FR::SystemExec::Exec(commandLine);

				// model
				pragmaList = { " --file={0} --skeleton={1}.skel --mesh={2}.ozz" };

				commandLine = modelExeName + pragmaList;

				FR::StringExtension::Replace(commandLine, "{0}", path);

				FR::StringExtension::Replace(name, "." + extPath, "");
				FR::StringExtension::Replace(commandLine, "{1}", modelPath + name);
				FR::StringExtension::Replace(commandLine, "{2}", modelPath + name);

				FR::SystemExec::Exec(commandLine);
			}
		}
	}
}
