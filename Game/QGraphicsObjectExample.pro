#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T19:21:20
#
#-------------------------------------------------

#Здесь находятся различные настройки, которые позволяют программе работать
#и ссылки на файлы, которые есть в программе

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fly
TEMPLATE = app


SOURCES += main.cpp\
    apple.cpp \
    spider.cpp \
        widget.cpp \
    customscene.cpp \
    triangle.cpp

HEADERS  += widget.h \
    apple.h \
    customscene.h \
    spider.h \
    triangle.h

FORMS    += widget.ui

RESOURCES += \
    resorse.qrc
