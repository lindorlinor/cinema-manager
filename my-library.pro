CONFIG += c++20
CONFIG += console

CONFIG += debug
OBJECTS_DIR = release
MOC_DIR = release
RCC_DIR = release
UI_DIR = release

QT += widgets xml
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
            MediaVisitor.h \
            DetailPageVisitor.h \
            GUI/CinemaButton.h \
            GUI/MainWindow.h \
            GUI/CinemaSelectionPage.h \
            GUI/SearchPanel.h \
            GUI/InsertCinemaPage.h \
            GUI/InsertMedia.h \
            GUI/ListPersone.h \
            GUI/InsertImageFrame.h \
            GUI/MediaFrame.h \
            GUI/SelectMediaReference.h \
            GUI/FilmView.h \
            GUI/ExpandableLabel.h \
            GUI/CardTrailer.h \
            GUI/DetailsPageButtons.h \
            DataFiles/CinemaXmlRepository.h \
            DataFiles/MediaManagerJson.h 
SOURCES +=  \
            main.cpp \
            Inserzione.cpp \
            Media.cpp \
            Pubblicita.cpp \
            Trailer.cpp \
            Film.cpp \
            Podcast.cpp \
            Puntata.cpp \
            DetailPageVisitor.cpp \
            test/test.cpp \
            GUI/CinemaButton.cpp \
            GUI/MainWindow.cpp \
            GUI/CinemaSelectionPage.cpp \
            GUI/SearchPanel.cpp \
            GUI/InsertCinemaPage.cpp \
            GUI/InsertMedia.cpp \
            GUI/ListPersone.cpp \
            GUI/InsertImageFrame.cpp \
            GUI/MediaFrame.cpp \
            GUI/SelectMediaReference.cpp \
            GUI/FilmView.cpp \
            GUI/ExpandableLabel.cpp \
            GUI/CardTrailer.cpp \
            GUI/DetailsPageButtons.cpp \
            DataFiles/CinemaXmlRepository.cpp \
            DataFiles/MediaManagerJson.cpp
RESOURCES += GUI/resources.qrc
