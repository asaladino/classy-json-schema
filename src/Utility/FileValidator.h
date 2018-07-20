//
// Created by adam on 7/19/18.
//

#ifndef CLASSY_JSON_SCHEMA_FILEVALIDATOR_H
#define CLASSY_JSON_SCHEMA_FILEVALIDATOR_H


#include <QtGui/QValidator>
#include <QtWidgets/QLineEdit>

class FileValidator : public QValidator {
Q_OBJECT;

public:
    explicit FileValidator(QObject* parent = nullptr) : QValidator(parent){}

    State validate(QString &, int &) const override;
    void fixup(QString &) const override;
};


#endif //CLASSY_JSON_SCHEMA_FILEVALIDATOR_H
