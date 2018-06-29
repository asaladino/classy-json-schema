//
// Created by Adam Saladino on 6/27/18.
//

#include <vector>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include "JsonSchemaRepository.h"

JsonSchemaRepository::JsonSchemaRepository(const std::string &folder) :
        folder(folder) {
}

std::vector<std::string> JsonSchemaRepository::findAllFiles() {
    std::vector<std::string> files {};
    if (auto dir = opendir(this->getFolder().c_str())) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] != '.') {
                files.push_back(f->d_name);
            }
        }
        closedir(dir);
    }
    return files;
}

std::string &JsonSchemaRepository::getFolder() {
    return this->folder;
}

json JsonSchemaRepository::fileAsJson(const std::string &file) {
    std::ifstream i(this->getFolder() + file);
    json j;
    i >> j;
    return j;
}
