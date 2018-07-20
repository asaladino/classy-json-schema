//
// Created by adam on 7/19/18.
//

#include <iostream>
#include "FileValidator.h"

QValidator::State FileValidator::validate(QString &text, int &value) const {
    if (auto file = fopen(text.toStdString().c_str(), "r")) {
        fclose(file);
        return State::Acceptable;
    } else {
        return State::Invalid;
    }
}

void FileValidator::fixup(QString &value) const {
}