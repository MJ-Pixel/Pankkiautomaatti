QT -= gui
QT += core sql

TARGET = DLLMySQL
CONFIG += qt
TEMPLATE = lib

DEFINES += DLLMYSQL_LIBRARY

# CONFIG += c++11

# LIBS +="C:/Users/Hadis/Documents/Qt/Olio-ohjelmoinnin_jatkokurssi/build-Exec-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/libmysql.dll"

SOURCES += \
    dllmysql.cpp

HEADERS += \
    DLLMySQL_global.h \
    dllmysql.h

DESTDIR = "C:\Users\Hadis\Documents\Qt\Olio-ohjelmoinnin_jatkokurssi\build-DLLMySQL-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug"
