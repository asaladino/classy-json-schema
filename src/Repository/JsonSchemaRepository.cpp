//
// Created by Adam Saladino on 6/27/18.
//

#include <vector>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include "JsonSchemaRepository.h"

JsonSchemaRepository::JsonSchemaRepository(const Setting &setting) :
        setting(setting) {
}

std::vector<std::string> JsonSchemaRepository::findAllFiles() {
    std::vector<std::string> files {};
    if (auto dir = opendir(this->setting.schemaFolder.c_str())) {
        while (auto f = readdir(dir)) {
            if (isJson(f->d_name)) {
                files.push_back(f->d_name);
            }
        }
        closedir(dir);
    }
    return files;
}

bool JsonSchemaRepository::isJson(const std::string &str)
{
    std::string json(".json");
    return str.size() >= json.size() &&
           str.compare(str.size() - json.size(), json.size(), json) == 0;
}

json JsonSchemaRepository::fileAsJson(const std::string &file) {
    std::ifstream i(this->setting.schemaFolder + file);
    json j;
    i >> j;
    return j;
}
