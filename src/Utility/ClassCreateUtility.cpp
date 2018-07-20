//
// Created by Adam Saladino on 6/27/18.
//

#include <regex>
#include <iostream>
#include "ClassCreateUtility.h"
#include <fstream>
#include <streambuf>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

ClassCreateUtility::ClassCreateUtility(const Setting &setting) :
        setting(setting) {
    std::ifstream t(setting.templateFile);
    templateFileContents = std::string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

void ClassCreateUtility::writeClass(const json &contents, const std::string &className, bool isDataModel) {
    saveClass(contents, className, isDataModel);
    for (auto property = contents.at("properties").begin(); property != contents.at("properties").end(); ++property) {
        auto type = std::string("string");
        try {
            type = property.value().at("type");
            if (type == "object") {
                auto propertyName = property.key();
                classNameFromProperty(propertyName);
                writeClass(property.value(), propertyName, false);
            }
            if (type == "array") {
                auto arrayType = property.value().at("items").at("type").get<std::string>();
                if (arrayType == "object") {
                    auto propertyName = property.key();
                    classNameFromProperty(propertyName);
                    writeClass(property.value().at("items"), propertyName, false);
                }
            }
        } catch (json::exception &e) {
        }
    }
}

void ClassCreateUtility::saveClass(const json &contents, const std::string &className, bool isDataModel) {
    // Generating template data.
    auto templateData = json();
    templateData["className"] = className;
    templateData["isDataModel"] = isDataModel;
    populateTemplateContents(templateData, contents);

    // Populating template with data.
    auto renderedFile = environment.render(templateFileContents, templateData);

    // Write class to file.
    fs::path path(setting.outputFolder);
    fs::path outputFile(templateData.at("className").get<std::string>() + "." + setting.outputType);
    fs::path fullPath = path / outputFile;

    if (!boost::filesystem::exists(fullPath)) {
        auto output_file = std::ofstream(fullPath);
        output_file << renderedFile;
    }
}


void ClassCreateUtility::classNameFromProperty(std::string &propertyName) {
    propertyName[0] = static_cast<char>(std::toupper(propertyName[0]));
}


void ClassCreateUtility::classNameFromFile(const std::string &file, std::string &className) {
    auto active = true;
    className = std::regex_replace(file, std::regex(R"(\.json)"), " ");
    className = std::regex_replace(className, std::regex(R"(\-)"), " ");

    for (int i = 0; className[i] != '\0'; i++) {
        if (std::isalpha(className[i])) {
            if (active) {
                className[i] = static_cast<char>(std::toupper(className[i]));
                active = false;
            } else {
                className[i] = static_cast<char>(std::tolower(className[i]));
            }
        } else if (className[i] == ' ') {
            active = true;
        }
    }
    className = std::regex_replace(className, std::regex(R"(\s)"), "");
}

void ClassCreateUtility::populateTemplateContents(json &templateData, const json &contents) {
    templateData["description"] = contents.at("description");
    templateData["properties"] = {};

    for (auto property = contents.at("properties").begin(); property != contents.at("properties").end(); ++property) {
        auto type = std::string("string");
        auto variableName = property.key();
        auto isArray = false;
        auto isUnknownObject = false;
        try {
            type = property.value().at("type");
            if (type == "object") {
                auto propertyName = property.key();
                classNameFromProperty(propertyName);
                type = propertyName;
            }
            if (type == "array") {
                type = property.value().at("items").at("type").get<std::string>();
                isArray = true;
                if (type == "object") {
                    auto propertyName = property.key();
                    classNameFromProperty(propertyName);
                    type = propertyName;
                }
            }
        } catch (json::exception &e) {
            try {
                isUnknownObject = true;
                type = "object";
            } catch (json::exception &e) {}
        }
        templateData.at("properties").push_back({
                                                        {"type",            type},
                                                        {"description",     property.value().at("description")},
                                                        {"isArray",         isArray},
                                                        {"isUnknownObject", isUnknownObject},
                                                        {"isString",        type == "string"},
                                                        {"variableName",    variableName}
                                                });
    }
}
