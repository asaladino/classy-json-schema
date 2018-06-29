//
// Created by Adam Saladino on 6/27/18.
//

#ifndef CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H
#define CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H


#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonSchemaRepository {

public:
    explicit JsonSchemaRepository(const std::string &folder);

    std::vector<std::string> findAllFiles();

    json fileAsJson(const std::string &file);

    std::string &getFolder();

private:
    std::string folder;
};


#endif //CLASSY_JSON_SCHEMA_JSONSCHEMAREPOSITORY_H
