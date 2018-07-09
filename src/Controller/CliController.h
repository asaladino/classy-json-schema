//
// Created by Adam Saladino on 7/2/18.
//

#ifndef CLASSY_JSON_SCHEMA_CLICONTROLLER_H
#define CLASSY_JSON_SCHEMA_CLICONTROLLER_H


#include "../Model/Setting.h"

class CliController {

public:
    explicit CliController(const Setting &setting);

    int run();

private:
    const Setting &setting;

};


#endif //CLASSY_JSON_SCHEMA_CLICONTROLLER_H
