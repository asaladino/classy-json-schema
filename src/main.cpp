#include <iostream>
#include <vector>
#include "Repository/JsonSchemaRepository.h"
#include "Utility/ClassCreateUtility.h"

// Move to controller class
void cli(const std::string &templateFile,
              const std::string &schemaFolder,
              const std::string &outputFolder,
              const std::string &outputType);

// Move to controller class.
void gui(const std::string &templateFile,
              const std::string &schemaFolder,
              const std::string &outputFolder,
              const std::string &outputType);

int main(int argc, char *argv[]) {
    // Move to settings model.
    std::string templateFile;
    std::string schemaFolder;
    std::string outputFolder;
    std::string outputType;
    bool showGui = false;

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
        if (argValue.compare("--gui") == 0) {
            showGui = true;
        }
    }

    if(showGui) {
        // Pass setting reference.
        gui(templateFile, schemaFolder, outputFolder, outputType);
    } else {
        // Pass setting reference.
        cli(templateFile, schemaFolder, outputFolder, outputType);
    }

    return 0;
}

void cli(const std::string &templateFile,
              const std::string &schemaFolder,
              const std::string &outputFolder,
              const std::string &outputType) {
    // Find all json schema files.
    auto jsonSchemaRepository = std::make_unique<JsonSchemaRepository>(schemaFolder);
    auto files = jsonSchemaRepository->findAllFiles();

    // Creating class generator utility.
    auto classCreateUtility = std::make_unique<ClassCreateUtility>(outputFolder, outputType, templateFile);

    std::cout << "Template File: \t" << templateFile << std::endl;
    std::cout << "Schema Folder: \t" << schemaFolder << std::endl;
    std::cout << "Output Folder: \t" << outputFolder << std::endl;
    std::cout << "Output Type: \t" << outputType << std::endl;
    std::cout << "Schema Found: \t" << files.size() << std::endl;

    std::cout << "\nGenerating Classes For..." << std::endl;

    for (auto file : files) {
        std::cout << file << std::endl;

        std::string className;
        classCreateUtility->classNameFromFile(file, className);
        auto json = jsonSchemaRepository->fileAsJson(file);
        classCreateUtility->writeClass(json, className, true);
    }
}

void gui(const std::string &templateFile,
          const std::string &schemaFolder,
          const std::string &outputFolder,
          const std::string &outputType) {

}