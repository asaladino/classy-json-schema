#include "Model/Setting.h"
#include "Controller/CliController.h"
#include "Controller/GuiController.h"

int main(int argc, char *argv[]) {
    auto setting = Setting(argc, argv);
    if (setting.useCli) {
        auto cliController = CliController(setting);
        return cliController.run();
    } else {
        auto guiController = GuiController(setting);
        return guiController.run(argc, argv);
    }
}