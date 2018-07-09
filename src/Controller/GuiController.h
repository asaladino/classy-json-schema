//
// Created by Adam Saladino on 7/2/18.
//

#ifndef CLASSY_JSON_SCHEMA_GUICONTROLLER_H
#define CLASSY_JSON_SCHEMA_GUICONTROLLER_H


#include "../Model/Setting.h"

class GuiController {

public:
    explicit GuiController(Setting &setting);

    int run(int argc, char *argv[]);

private:
    Setting &setting;
};


#endif //CLASSY_JSON_SCHEMA_GUICONTROLLER_H
