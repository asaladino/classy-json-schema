//
// Created by Adam Saladino on 6/27/18.
//

#ifndef CLASSY_JSON_SCHEMA_CLASSCREATEUTILITY_H
#define CLASSY_JSON_SCHEMA_CLASSCREATEUTILITY_H

#include <nlohmann/json.hpp>
#include <inja.hpp>

using namespace inja;
using json = nlohmann::json;

class ClassCreateUtility {
public:
    explicit ClassCreateUtility(const std::string &outputFolder,
                                const std::string &outputType,
                                const std::string &templateFile);

    void writeClass(const json &contents, const std::string &className, const bool isDataModel);

    void classNameFromFile(const std::string &file, std::string &className);

private:
    const std::string outputFolder;
    const std::string sourceType;
    Environment environment = Environment();
    std::string templateFileContents;

    bool doesFileExist(const std::string &name);

    void saveClass(const json &contents, const std::string &className, const bool isDataModel);

    void classNameFromProperty(std::string &propertyName);

    void populateTemplateContents(json &templateData, const json &contents);
};


#endif //CLASSY_JSON_SCHEMA_CLASSCREATEUTILITY_H
