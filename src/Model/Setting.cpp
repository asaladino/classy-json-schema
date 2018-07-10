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
        if (argValue == "--templateFile") {
            templateFile = std::string(argv[i + 1]);
        }
        if (argValue == "--schemaFolder") {
            schemaFolder = std::string(argv[i + 1]);
        }
        if (argValue == "--outputFolder") {
            outputFolder = std::string(argv[i + 1]);
        }
        if (argValue == "--outputType") {
            outputType = std::string(argv[i + 1]);
        }
        if (argValue == "--cli") {
            useCli = true;
        }
    }
}
