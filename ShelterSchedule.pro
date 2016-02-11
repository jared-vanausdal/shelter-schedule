#-------------------------------------------------
#
# Project created by QtCreator 2016-02-06T17:15:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShelterSchedule
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES +=\
    database/shelterDB

RESOURCES += \
    ShelterRC.qrc

copydata.commands = $(COPY_DIR) $$PWD/database/ $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata
POST_TARGETDEPS += copydata

