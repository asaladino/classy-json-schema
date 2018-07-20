//
// Created by Adam Saladino on 6/29/18.
//

#ifndef CLASSY_JSON_SCHEMA_SETTING_H
#define CLASSY_JSON_SCHEMA_SETTING_H


#include <string>

class Setting {

public:

    Setting() = default;

    Setting(int argc, char **argv);

    Setting(std::string &templateFile,
            std::string &schemaFolder,
            std::string &outputFolder,
            std::string &outputTyp,
            bool useCli);

    void build(int argc, char *argv[]);

    mutable std::string templateFile;
    mutable std::string schemaFolder;
    mutable std::string outputFolder;
    mutable std::string outputType;
    mutable bool useCli = false;
};


#endif //CLASSY_JSON_SCHEMA_SETTING_H
