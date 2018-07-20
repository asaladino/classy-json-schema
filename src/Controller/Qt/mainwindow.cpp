#include <iostream>
#include <src/Repository/JsonSchemaRepository.h>
#include <QFileDialog>
#include <QTreeView>
#include <QThread>
#include <QFutureWatcher>
#include "mainwindow.h"
#include "../../../cmake-build-debug/classy_json_schema_autogen/include/ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>
#include <src/Utility/FileValidator.h>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonStartGenerator, SIGNAL(released()), this, SLOT(startGeneratorThread()));
    connect(ui->pushButtonTemplateFile, SIGNAL(released()), this, SLOT(templateFileDialog()));
    connect(ui->pushButtonSchemaFolder, SIGNAL(released()), this, SLOT(schemaFolderDialog()));
    connect(ui->pushButtonOutputFolder, SIGNAL(released()), this, SLOT(outputFolderDialog()));

    connect(this, SIGNAL(progressStatusChanged(int, int, QString)),
            this, SLOT(setProgressStatus(int, int, QString)));

    connect(this, SIGNAL(validationLineEditChanged(bool, QLineEdit * )),
            this, SLOT(setValidationLineEdit(bool, QLineEdit * )));

    ui->lineEditTemplateFile->setValidator(new FileValidator(ui->lineEditTemplateFile));
    ui->lineEditSchemaFolder->setValidator(new FileValidator(ui->lineEditSchemaFolder));
    ui->lineEditOutputFolder->setValidator(new FileValidator(ui->lineEditOutputFolder));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateSetting(Setting &setting) {
    ui->lineEditTemplateFile->setText(QString::fromStdString(setting.templateFile));
    ui->lineEditSchemaFolder->setText(QString::fromStdString(setting.schemaFolder));
    ui->lineEditOutputFolder->setText(QString::fromStdString(setting.outputFolder));
    ui->lineEditType->setText(QString::fromStdString(setting.outputType));
}

void MainWindow::startGeneratorThread() {
    ui->pushButtonStartGenerator->setDisabled(true);
    // Create a QFutureWatcher and connect signals and slots.
    auto futureWatcher = QFutureWatcher<void>();
    auto future = QtConcurrent::run(this, &MainWindow::start);
    // Start the computation.
    futureWatcher.setFuture(future);
}

void MainWindow::start() {
    if (isInputValid()) {
        auto templateFile = ui->lineEditTemplateFile->text().toStdString();
        auto schemaFolder = ui->lineEditSchemaFolder->text().toStdString();
        auto outputFolder = ui->lineEditOutputFolder->text().toStdString();
        auto outputType = ui->lineEditType->text().toStdString();
        auto setting = Setting{templateFile, schemaFolder, outputFolder, outputType, false};

        // Find all json schema files.
        auto jsonSchemaRepository = JsonSchemaRepository(setting);
        auto files = jsonSchemaRepository.findAllFiles();

        auto classCreateUtility = ClassCreateUtility(setting);

        auto progress = 1;
        auto max = static_cast<int>(files.size());

        auto className = std::string();
        try {
            for (const auto &file : files) {
                classCreateUtility.classNameFromFile(file, className);
                auto json = jsonSchemaRepository.fileAsJson(file);
                classCreateUtility.writeClass(json, className, true);
                emit progressStatusChanged(progress++, max, QString::fromStdString(className));
            }

        } catch (const std::exception &ex) {
            std::cout << ex.what();
        }
    }
    emit progressStatusChanged(1, 1, "Done...");
}

void MainWindow::setProgressStatus(int value, int max, const QString &status) {
    if (value == max) {
        ui->progressBar->setMaximum(max);
        ui->labelStatus->setText("Ready for more.");
        ui->progressBar->setValue(0);
        ui->pushButtonStartGenerator->setDisabled(false);
    } else {
        ui->progressBar->setMaximum(max);
        ui->labelStatus->setText(status);
        ui->progressBar->setValue(value);
    }
}

bool MainWindow::isInputValid() {
    auto isValid = true;
    auto value = 0;
    auto qTemplateFile = ui->lineEditTemplateFile->text();
    if (ui->lineEditTemplateFile->validator()->validate(qTemplateFile, value) == QValidator::State::Invalid) {
        isValid = false;
        emit validationLineEditChanged(false, ui->lineEditTemplateFile);
    } else {
        emit validationLineEditChanged(true, ui->lineEditTemplateFile);
    }
    auto qSchemaFolder = ui->lineEditSchemaFolder->text();
    if (ui->lineEditSchemaFolder->validator()->validate(qSchemaFolder, value) == QValidator::State::Invalid) {
        isValid = false;
        emit validationLineEditChanged(false, ui->lineEditSchemaFolder);
    } else {
        emit validationLineEditChanged(true, ui->lineEditSchemaFolder);
    }
    auto qOutputFolder = ui->lineEditOutputFolder->text();
    if (ui->lineEditOutputFolder->validator()->validate(qOutputFolder, value) == QValidator::State::Invalid) {
        isValid = false;
        emit validationLineEditChanged(false, ui->lineEditOutputFolder);
    } else {
        emit validationLineEditChanged(true, ui->lineEditOutputFolder);
    }
    return isValid;
}


/**
 * @todo add check for empty string.
 */
void MainWindow::templateFileDialog() {
    auto fileName = QFileDialog::getOpenFileName(this, tr("Select Template"), "~/", tr("Template File (*.*)"));
    ui->lineEditTemplateFile->setText(fileName);
    ui->lineEditTemplateFile->setFocus();
}


/**
 * @todo add check for empty string.
 */
void MainWindow::schemaFolderDialog() {
    auto fileDialog = QFileDialog();
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);
    fileDialog.setViewMode(QFileDialog::Detail);
    if (fileDialog.exec()) {
        auto directory = fileDialog.selectedFiles()[0];
        ui->lineEditSchemaFolder->setText(directory);
        ui->lineEditSchemaFolder->setFocus();
    }
}

/**
 * @todo add check for empty string.
 */
void MainWindow::outputFolderDialog() {
    auto fileDialog = QFileDialog();
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);
    fileDialog.setViewMode(QFileDialog::Detail);
    if (fileDialog.exec()) {
        auto directory = fileDialog.selectedFiles()[0];
        ui->lineEditOutputFolder->setText(directory);
        ui->lineEditOutputFolder->setFocus();
    }
}

void MainWindow::setValidationLineEdit(bool isValid, QLineEdit *lineEdit) {
    if (isValid) {
        lineEdit->setStyleSheet("QLineEdit { background-color: white }");
    } else {
        lineEdit->setStyleSheet("QLineEdit { background-color: yellow }");
    }
}
