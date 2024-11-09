#ifndef EXTRACTOR_GM_H
#define EXTRACTOR_GM_H

#include <QString>
#include <QList>
#include <QPointF>
#include <QColor>
#include <QProgressBar>
#include <QDebug>

struct Polygon {
    QList<QPointF> points;
    QColor color;
    QString value;
};

class extractor_gm {
public:
    extractor_gm();
    QList<Polygon> readFile(const QString& filePath, QProgressBar* progressBar);  // Progress bar included
    QString displayPolygons(const QList<Polygon>& polygons);  // Function declaration
};

#endif
