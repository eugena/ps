QT += core network
QT -= gui

CONFIG += c++11

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    calculator.cpp

HEADERS += \
    server.h \
    calculator.h
