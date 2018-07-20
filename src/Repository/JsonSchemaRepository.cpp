//
// Created by Adam Saladino on 6/27/18.
//

#include <vector>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include "JsonSchemaRepository.h"

using namespace std::literals;
namespace fs = boost::filesystem;

JsonSchemaRepository::JsonSchemaRepository(const Setting &setting) :
        setting(setting) {
}

std::vector<std::string> JsonSchemaRepository::findAllFiles() {
    std::vector<std::string> files {};
    if (auto dir = opendir(this->setting.schemaFolder.c_str())) {
        while (auto f = readdir(dir)) {
            if (isJson(f->d_name)) {
                files.emplace_back(f->d_name);
            }
        }
        closedir(dir);
    }
    return files;
}

bool JsonSchemaRepository::isJson(const std::string &str)
{
    auto json = ".json"s;
    return str.size() >= json.size() &&
           str.compare(str.size() - json.size(), json.size(), json) == 0;
}

json JsonSchemaRepository::fileAsJson(const std::string &file) {
    fs::path path(setting.schemaFolder);
    fs::path fullPath = path / file;

    auto ifstream = std::ifstream(fullPath);
    auto basicJson = json();
    ifstream >> basicJson;
    return basicJson;
}
