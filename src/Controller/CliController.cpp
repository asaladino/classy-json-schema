//
// Created by Adam Saladino on 7/2/18.
//

#include <iostream>
#include "CliController.h"
#include "../Repository/JsonSchemaRepository.h"
#include "../Utility/ClassCreateUtility.h"

CliController::CliController(const Setting &setting) :
        setting(setting) {
}

int CliController::run() {
    // Find all json schema files.
    auto jsonSchemaRepository = JsonSchemaRepository(setting);
    auto files = jsonSchemaRepository.findAllFiles();

    // Creating class generator utility.
    auto classCreateUtility = ClassCreateUtility(setting);

    std::cout << "Template File: \t" << setting.templateFile << '\n';
    std::cout << "Schema Folder: \t" << setting.schemaFolder << '\n';
    std::cout << "Output Folder: \t" << setting.outputFolder << '\n';
    std::cout << "Output Type: \t" << setting.outputType << '\n';
    std::cout << "Schema Found: \t" << files.size() << '\n';

    std::cout << "\nGenerating Classes For..." << std::endl;

    auto className = std::string();
    for (const auto &file : files) {
        std::cout << file << '\n';
        classCreateUtility.classNameFromFile(file, className);
        auto json = jsonSchemaRepository.fileAsJson(file);
        classCreateUtility.writeClass(json, className, true);
    }
    return 0;
}
