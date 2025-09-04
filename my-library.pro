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
            Cinema.h \
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
            GUI/MediaView.h \
            GUI/FilmView.h \
            GUI/TrailerView.h \
            GUI/inserzioneView.h \
            GUI/PodcastView.h \
            GUI/PuntataView.h \
            GUI/ExpandableLabel.h \
            GUI/PreviewCard.h \
            GUI/DetailsPageButtons.h \
            GUI/MediaLibraryGenerale.h \
            GUI/MediaLibraryTutto.h \
            GUI/FlowLayout.h \
            GUI/LibraryObserver.h \
            GUI/Menu.h \
            GUI/FrameVisitor.h \
            GUI/ScrollListWidget.h \
            GUI/UpdateMediaLibrary.h \
            GUI/CinemaModifier.h \
            GUI/MediaInterface.h \
            GUI/EditMedia.h \
            DataFiles/CinemaRepositoryJson.h \
            DataFiles/JsonConverter.h \
            DataFiles/JsonVisitor.h \
            DataFiles/MediaManagerXml.h \
            DataFiles/XmlVisitor.h
SOURCES +=  \
            main.cpp \
            Inserzione.cpp \
            Media.cpp \
            Pubblicita.cpp \
            Trailer.cpp \
            Film.cpp \
            Podcast.cpp \
            Puntata.cpp \
            Cinema.cpp \
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
            GUI/MediaView.cpp \
            GUI/FilmView.cpp \
            GUI/inserzioneView.cpp \
            GUI/PodcastView.cpp \
            GUI/PuntataView.cpp \
            GUI/TrailerView.cpp \
            GUI/ExpandableLabel.cpp \
            GUI/PreviewCard.cpp \
            GUI/MediaLibraryGenerale.cpp \
            GUI/MediaLibraryTutto.cpp \
            GUI/DetailsPageButtons.cpp \
            GUI/ScrollListWidget.cpp \
            GUI/FlowLayout.cpp \
            GUI/UpdateMediaLibrary.cpp \
            GUI/Menu.cpp \
            GUI/FrameVisitor.cpp \
            GUI/CinemaModifier.cpp \
            GUI/MediaInterface.cpp \
            GUI/EditMedia.cpp \
            DataFiles/CinemaRepositoryJson.cpp \
            DataFiles/JsonConverter.cpp \
            DataFiles/JsonVisitor.cpp \
            DataFiles/MediaManagerXml.cpp \
            DataFiles/XmlVisitor.cpp
RESOURCES += GUI/resources.qrc
