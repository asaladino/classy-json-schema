//
// Created by Adam Saladino on 6/27/18.
//

#ifndef CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H
#define CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H


#include <string>
#include <nlohmann/json.hpp>
#include "../Model/Setting.h"

using json = nlohmann::json;

class JsonSchemaRepository {

public:
    explicit JsonSchemaRepository(const Setting &setting);

    std::vector<std::string> findAllFiles();

    json fileAsJson(const std::string &file);

    bool isJson(const std::string &str);

private:
    Setting setting;
};


#endif //CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H
