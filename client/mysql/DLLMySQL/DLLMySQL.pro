QT -= gui console
QT += core sql

TARGET = DLLMySQL
CONFIG += qt
TEMPLATE = lib

DEFINES += DLLMYSQL_LIBRARY

SOURCES += \
    dllmysql.cpp

HEADERS += \
    DLLMySQL_global.h \
    dllmysql.h

DESTDIR = "C:\BankSimul\exe"
