#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace FR
{
	class FRFile
	{
	public:
		static std::vector<uint8_t> ReadBinaryFile(const std::string& pFileName)
		{
			std::ifstream file;

			std::vector<uint8_t> data;

			try
			{
				file.open(pFileName, std::ios::in | std::ios::binary);

				file.seekg(0, std::ios::end);
				size_t read_count = static_cast<size_t>(file.tellg());

				file.seekg(0, std::ios::beg);

				data.resize(read_count);
				file.read(reinterpret_cast<char*>(data.data()), read_count);
				file.close();
			}
			catch (std::ifstream::failure)
			{
				throw std::runtime_error("Failed to open file: " + pFileName);
			}

			return data;
		}
	};
}