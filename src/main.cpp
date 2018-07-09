#include "Model/Setting.h"
#include "Controller/CliController.h"
#include "Controller/GuiController.h"

int main(int argc, char *argv[]) {
    std::string templateFile;
    std::string schemaFolder;
    std::string outputFolder;
    std::string outputType;
    bool useCli = false;
    Setting setting(templateFile, schemaFolder, outputFolder, outputType, useCli);
    setting.build(argc, argv);

    if (setting.useCli) {
        CliController cliController(setting);
        return cliController.run();
    } else {
        GuiController guiController(setting);
        return guiController.run(argc, argv);
    }
}