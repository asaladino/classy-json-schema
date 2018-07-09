//
// Created by Adam Saladino on 6/29/18.
//

#ifndef CLASSY_JSON_SCHEMA_SETTING_H
#define CLASSY_JSON_SCHEMA_SETTING_H


#include <string>

class Setting {

public:

    Setting(std::string &templateFile,
            std::string &schemaFolder,
            std::string &outputFolder,
            std::string &outputTyp,
            bool useCli);

    void build(int argc, char *argv[]);

    std::string &templateFile;
    std::string &schemaFolder;
    std::string &outputFolder;
    std::string &outputType;
    bool useCli;
};


#endif //CLASSY_JSON_SCHEMA_SETTING_H
