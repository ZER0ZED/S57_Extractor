#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QProgressBar>
#include <QDebug>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();
    void on_processFileButton_clicked();
    void on_saveResultsButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
    void loadS57File(const QString& path);
};

#endif
