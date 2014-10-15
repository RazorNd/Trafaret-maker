#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T14:19:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mask_for_polygone_stripple
TEMPLATE = app


SOURCES += main.cpp\
    mask.cpp \
    maskstriple.cpp \
    mainwindow.cpp

HEADERS  += \
    mask.h \
    maskstriple.h \
    mainwindow.h

FORMS +=

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ico.rc

win32:RC_FILE = ico.rc
