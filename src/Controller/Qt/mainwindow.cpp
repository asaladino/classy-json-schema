#include <iostream>
#include <src/Repository/JsonSchemaRepository.h>
#include <src/Utility/ClassCreateUtility.h>
#include <QFileDialog>
#include <QTreeView>
#include <QThread>
#include <QFutureWatcher>
#include "mainwindow.h"
#include "../../../cmake-build-debug/classy_json_schema_autogen/include/ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>

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
    QFutureWatcher<void> futureWatcher;

    QFuture<void> f1 = QtConcurrent::run(this, &MainWindow::start);
    // Start the computation.
    futureWatcher.setFuture(f1);
}

void MainWindow::start() {
    std::string templateFile = ui->lineEditTemplateFile->text().toStdString();
    std::string schemaFolder = ui->lineEditSchemaFolder->text().toStdString();
    std::string outputFolder = ui->lineEditOutputFolder->text().toStdString();
    std::string outputType = ui->lineEditType->text().toStdString();
    Setting setting(templateFile, schemaFolder, outputFolder, outputType, false);

    // Find all json schema files.
    JsonSchemaRepository jsonSchemaRepository(setting);
    auto files = jsonSchemaRepository.findAllFiles();

    // Creating class generator utility.
    ClassCreateUtility classCreateUtility(setting);

    int progress = 1;
    auto max = static_cast<int>(files.size());

    for (const auto &file : files) {
        std::string className;
        classCreateUtility.classNameFromFile(file, className);
        auto json = jsonSchemaRepository.fileAsJson(file);
        classCreateUtility.writeClass(json, className, true);
        emit progressStatusChanged(progress++, max, QString::fromStdString(className));
    }
    emit progressStatusChanged(max, max, "Done...");
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

void MainWindow::templateFileDialog() {
    auto fileName = QFileDialog::getOpenFileName(this, tr("Select Template"), "~/", tr("Template File (*.*)"));
    ui->lineEditTemplateFile->setText(fileName);
    ui->lineEditTemplateFile->setFocus();
}

void MainWindow::schemaFolderDialog() {
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly);
    fd.setViewMode(QFileDialog::Detail);
    if (fd.exec()) {
        auto directory = fd.selectedFiles()[0];
        ui->lineEditSchemaFolder->setText(directory);
        ui->lineEditSchemaFolder->setFocus();
    }
}

void MainWindow::outputFolderDialog() {
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly);
    fd.setViewMode(QFileDialog::Detail);
    if (fd.exec()) {
        auto directory = fd.selectedFiles()[0];
        ui->lineEditOutputFolder->setText(directory);
        ui->lineEditOutputFolder->setFocus();
    }
}
