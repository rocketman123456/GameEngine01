#ifndef _FILEUTILS_
#define _FILEUTILS_

#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace GameEngine {
	//////////////////////////////////////////////////////////////////////////////////

	static std::string read_file(const char *filepath) {
		FILE *file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char *data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);
		std::string result(data);
		delete[] data;
		return result;
	}

	// 参数读取类
	// 用法 atoi(pd.getData("end_index").c_str());
	class ParameterReader {
	public:
		ParameterReader(std::string filename = "parameters.txt") {
			std::ifstream fin(filename.c_str());
			if (!fin) {
				std::cerr << "parameter file does not exist." << std::endl;
				return;
			}
			while (!fin.eof()) {
				std::string str;
				std::getline(fin, str);
				if (str[0] == '#') {
					// 以‘＃’开头的是注释
					continue;
				}

				int pos = str.find("=");
				if (pos == -1)
					continue;
				std::string key = str.substr(0, pos);
				std::string value = str.substr(pos + 1, str.length());
				data[key] = value;

				if (!fin.good())
					break;
			}
		}
		std::string getData(std::string key) {
			std::map<std::string, std::string>::iterator iter = data.find(key);
			if (iter == data.end()) {
				std::cerr << "Parameter name " << key << " not found!" << std::endl;
				return std::string("NOT_FOUND");
			}
			return iter->second;
		}
	public:
		std::map<std::string, std::string> data;
	};

	//////////////////////////////////////////////////////////////////////////////////
}

#endif
