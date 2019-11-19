#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T11:45:42
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = impCheck
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        ledindicator.cpp \
        eemagine/sdk/wrapper.cc \
        aspectratiolabel.cpp

HEADERS +=  mainwindow.h \
            ledindicator.h \
            aspectratiolabel.h

RESOURCES += impCheck.qrc

FORMS += mainwindow.ui

CONFIG += qt warn_on\
          c++11\


unix:!macx: {
    LIBS += -leego-SDK -ldl
}

win32: {
    LIBS += -L$$PWD -leego-SDK
    INCLUDEPATH += $(BOOST_ROOT)
}
