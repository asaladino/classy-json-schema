//
// Created by Adam Saladino on 6/29/18.
//

#include "Setting.h"

Setting::Setting(std::string &templateFile,
                 std::string &schemaFolder,
                 std::string &outputFolder,
                 std::string &outputType,
                 bool useCli) :
        templateFile(templateFile),
        schemaFolder(schemaFolder),
        outputFolder(outputFolder),
        outputType(outputType),
        useCli(useCli) {

}

void Setting::build(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        std::string argValue(argv[i]);
        if (argValue.compare("--templateFile") == 0) {
            templateFile = std::string(argv[i + 1]);
        }
        if (argValue.compare("--schemaFolder") == 0) {
            schemaFolder = std::string(argv[i + 1]);
        }
        if (argValue.compare("--outputFolder") == 0) {
            outputFolder = std::string(argv[i + 1]);
        }
        if (argValue.compare("--outputType") == 0) {
            outputType = std::string(argv[i + 1]);
        }
        if (argValue.compare("--cli") == 0) {
            useCli = true;
        }
    }
}
