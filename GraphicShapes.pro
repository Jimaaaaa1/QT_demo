#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T11:28:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicShapes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += shape/

SOURCES += \
    form.cpp \
        main.cpp \
        gsmainscene.cpp \
#    gsshapeitem.cpp \
    gstempcanvaslayer.cpp \
    gsrootitem.cpp \
    shape/gsshapebaseitem.cpp \
    shape/gsshapelineitem.cpp \
    shape/gsshapefactory.cpp \
    shape/gsshaperectangeitem.cpp \
    shape/gsshapecircleitem.cpp \
    shape/gsshapeovalitem.cpp

HEADERS += \
    form.h \
        gsmainscene.h \
    gscommondef.h \
#    gsshapeitem.h \
    gstempcanvaslayer.h \
    gsrootitem.h \
    shape/gsshapebaseitem.h \
    shape/gsshapelineitem.h \
    shape/gsshapefactory.h \
    shape/gsshaperectangeitem.h \
    shape/gsshapecircleitem.h \
    shape/gsshapeovalitem.h \
    util.h \
    vcd.h

FORMS += \
    form.ui
