//
// Created by Adam Saladino on 7/2/18.
//
//
#include <QApplication>
#include <src/Controller/Qt/mainwindow.h>

#include "GuiController.h"

GuiController::GuiController(Setting &setting) :
        setting(setting) {
}

int GuiController::run(int argc, char *argv[]) {
    auto app = QApplication(argc, argv);
    auto window = MainWindow();
    window.updateSetting(setting);
    window.show();
    return QApplication::exec();
}
