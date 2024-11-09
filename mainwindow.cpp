#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resultsTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Open S57 File", "", "S57 Files (*.000);;All Files (*)");
    ui->filePathLineEdit->setText(filePath);
}

void MainWindow::on_processFileButton_clicked()
{
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a file first.");
        return;
    }

    loadS57File(filePath);
}

void MainWindow::on_saveResultsButton_clicked()
{
    QString saveFile = QFileDialog::getSaveFileName(this, "Save Results", "", "Text Files (*.txt);;All Files (*)");
    if (saveFile.isEmpty()) return;

    QFile file(saveFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->resultsTextEdit->toPlainText();  // Save displayed results
        file.close();
    }
}

void MainWindow::loadS57File(const QString &path)
{
    GDALAllRegister();

    GDALDataset *dataset = (GDALDataset*) GDALOpenEx(path.toStdString().c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (dataset == nullptr) {
        QMessageBox::warning(this, "Error", "Failed to open the file.");
        return;
    } else {
        qDebug() << "Successfully opened dataset: " << path;
    }

    QString resultText;
    OGRLayer *layer = nullptr;

    for (int i = 0; i < dataset->GetLayerCount(); i++) {
        layer = dataset->GetLayer(i);
        if (layer == nullptr) {
            qDebug() << "Layer " << i << " is null.";
            continue;
        } else {
            qDebug() << "Layer " << i << " successfully loaded.";
        }

        OGRFeature *feature = nullptr;
        layer->ResetReading();

        while ((feature = layer->GetNextFeature()) != nullptr) {
            OGRGeometry *geometry = feature->GetGeometryRef();
            if (geometry != nullptr) {
                if (wkbFlatten(geometry->getGeometryType()) == wkbPolygon) {
                    resultText += "Polygon detected:\n";

                    OGRPolygon *polygon = (OGRPolygon *)geometry;
                    OGRLinearRing *ring = polygon->getExteriorRing();
                    int numPoints = ring->getNumPoints();

                    resultText += "Coordinates:\n";
                    for (int j = 0; j < numPoints; j++) {
                        resultText += QString("Point %1: (%2, %3)\n")
                        .arg(j + 1)
                            .arg(ring->getX(j), 0, 'f', 6)  // X coordinate
                            .arg(ring->getY(j), 0, 'f', 6); // Y coordinate
                    }

                    resultText += "Attributes:\n";
                    for (int k = 0; k < feature->GetFieldCount(); k++) {
                        const char *fieldName = feature->GetFieldDefnRef(k)->GetNameRef();
                        const char *fieldValue = feature->GetFieldAsString(k);
                        resultText += QString("%1: %2\n").arg(fieldName).arg(fieldValue);
                    }
                }
            } else {
                qDebug() << "Feature geometry is null.";
            }
            OGRFeature::DestroyFeature(feature);
        }
    }

    ui->resultsTextEdit->setText(resultText);
    GDALClose(dataset);
}
