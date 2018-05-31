#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T17:59:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomRoller
TEMPLATE = app


SOURCES += main.cpp\
        mw.cpp \
    rand_alg.c

HEADERS  += mw.h \
    rand_alg.h

FORMS    += mw.ui
