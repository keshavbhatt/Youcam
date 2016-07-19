#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T19:10:40
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = youcam
TEMPLATE = app


SOURCES += main.cpp\
        youcam.cpp \
    aboutdialog.cpp

HEADERS  += youcam.h \
    aboutdialog.h

FORMS    += youcam.ui \
    aboutdialog.ui


#------------------------------------------
#dependencies
#qtvideonode-plugin
#------------------------------------------

RESOURCES += \
    rc.qrc

