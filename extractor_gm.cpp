#include "extractor_gm.h"
#include <QFile>
#include <QTextStream>

extractor_gm::extractor_gm() {}

// Function to read file and update progress bar
QList<Polygon> extractor_gm::readFile(const QString& filePath, QProgressBar* progressBar) {
    QList<Polygon> polygons;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file!";
        return polygons;
    }

    QTextStream in(&file);
    int totalLines = 0;

    // Count total lines
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.trimmed().isEmpty()) {
            totalLines++;
        }
    }

    if (totalLines == 0) {
        if (progressBar) progressBar->setValue(100);
        return polygons;  // Return empty list for empty file
    }

    file.seek(0);  // Reset the file position
    int processedLines = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;  // Skip empty lines

        Polygon poly;
        poly.points = { QPointF(0, 0), QPointF(1, 1), QPointF(2, 2) };  // Example points
        poly.color = Qt::red;
        poly.value = line;
        polygons.append(poly);

        // Update progress bar
        processedLines++;
        int progress = (processedLines * 100) / totalLines;
        if (progressBar) {
            progressBar->setValue(progress);
        }
    }

    file.close();
    return polygons;
}

// Function to display polygons as a formatted string
QString extractor_gm::displayPolygons(const QList<Polygon>& polygons) {
    QString result;
    for (const Polygon& poly : polygons) {
        result += "Polygon:\n";
        result += "Points: ";
        for (const QPointF& point : poly.points) {
            result += QString("(%1, %2) ").arg(point.x()).arg(point.y());
        }
        result += "\nColor: " + poly.color.name() + "\n";  // Convert color to string
        result += "Value: " + poly.value + "\n\n";
    }
    return result;  // Return formatted string
}
