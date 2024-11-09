QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = S57_Extractor
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

INCLUDEPATH += Gdal\include

LIBS += -L$$PWD/Gdal/lib -lgdal_i
LIBS += -lws2_32 -lwsock32
