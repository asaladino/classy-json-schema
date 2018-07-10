#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/Model/Setting.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void updateSetting(Setting &setting);
    void start();

public slots:
    void startGeneratorThread();
    void templateFileDialog();
    void schemaFolderDialog();
    void outputFolderDialog();
    void setProgressStatus(int value, int max, const QString &status);

signals:
    void progressStatusChanged(int value, int max, const QString &status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
