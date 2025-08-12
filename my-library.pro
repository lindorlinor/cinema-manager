CONFIG += c++20
CONFIG += console

CONFIG += debug
OBJECTS_DIR = release
MOC_DIR = release
RCC_DIR = release
UI_DIR = release

QT += widgets
QMAKE_CXXFLAGS += -g -O0


#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app
TARGET = release/my-library
INCLUDEPATH += .

# Input
HEADERS +=  \
            EnumClasses.h \
            Inserzione.h \
            Media.h \
            Pubblicita.h \
            Trailer.h \
            Film.h \
            Podcast.h \
            Puntata.h \
            catch.hpp \
            GUI/CinemaButton.h \
            GUI/MainWindow.h \
            GUI/CinemaSelectionPage.h \
            GUI/SearchPanel.h \
            GUI/InsertCinemaPage.h \
            GUI/PathButton.h \
            GUI/AddPanel.h 
SOURCES +=  \
            main.cpp \
            Inserzione.cpp \
            Media.cpp \
            Pubblicita.cpp \
            Trailer.cpp \
            Film.cpp \
            Podcast.cpp \
            Puntata.cpp \
            test/test.cpp \
            GUI/CinemaButton.cpp \
            GUI/MainWindow.cpp \
            GUI/CinemaSelectionPage.cpp \
            GUI/SearchPanel.cpp \
            GUI/InsertCinemaPage.cpp \
            GUI/PathButton.cpp \
            GUI/AddPanel.cpp
RESOURCES += GUI/resources.qrc
