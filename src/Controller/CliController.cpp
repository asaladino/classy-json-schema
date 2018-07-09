//
// Created by Adam Saladino on 7/2/18.
//

#include "CliController.h"
#include "../Repository/JsonSchemaRepository.h"
#include "../Utility/ClassCreateUtility.h"

CliController::CliController(const Setting &setting) :
        setting(setting) {
}

int CliController::run() {
    // Find all json schema files.
    JsonSchemaRepository jsonSchemaRepository(setting);
    auto files = jsonSchemaRepository.findAllFiles();

    // Creating class generator utility.
    ClassCreateUtility classCreateUtility(setting);

    std::cout << "Template File: \t" << setting.templateFile << std::endl;
    std::cout << "Schema Folder: \t" << setting.schemaFolder << std::endl;
    std::cout << "Output Folder: \t" << setting.outputFolder << std::endl;
    std::cout << "Output Type: \t" << setting.outputType << std::endl;
    std::cout << "Schema Found: \t" << files.size() << std::endl;

    std::cout << "\nGenerating Classes For..." << std::endl;

    for (auto file : files) {
        std::cout << file << std::endl;

        std::string className;
        classCreateUtility.classNameFromFile(file, className);
        auto json = jsonSchemaRepository.fileAsJson(file);
        classCreateUtility.writeClass(json, className, true);
    }
    return 0;
}
