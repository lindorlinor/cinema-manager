CONFIG += c++20

QMAKE_CXXFLAGS += -std=c++20

QT += widgets

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app
TARGET = my-library
INCLUDEPATH += .

# Input
HEADERS +=  \
            EnumClasses.h \
            MainWindow.h \
            EnumClasses.h \
            Inserzione.h \
            Media.h \
            Pubblicita.h \
            Trailer.h \
            Film.h \
            catch.hpp
SOURCES +=  \
            main.cpp \
            MainWindow.cpp \
            Inserzione.cpp \
            Media.cpp \
            Pubblicita.cpp \
            Trailer.cpp \
            Film.cpp 
