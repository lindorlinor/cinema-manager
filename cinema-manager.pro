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
TARGET = release/cinema-manager
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
            GUI/MainWindow.h \
            GUI/CinemaSelectionPage.h \
            GUI/SearchPanel.h \
            GUI/InsertCinemaPage.h \
            GUI/Library/MediaLibraryGenerale.h \
            GUI/Library/MediaLibraryTutto.h \
            GUI/Library/LibraryObserver.h \
            GUI/Library/CardVisitor.h \
            GUI/Library/UpdateMediaLibrary.h \
            GUI/MediaEditor/InsertMedia.h \
            GUI/MediaEditor/MediaInterface.h \
            GUI/MediaEditor/EditMedia.h \
            GUI/Custom/Menu.h \
            GUI/Custom/SelectMediaReference.h \
            GUI/Custom/InsertImageFrame.h \
            GUI/Custom/ListPersone.h \
            GUI/Custom/MediaFrame.h \
            GUI/Custom/FlowLayout.h \
            GUI/Custom/ScrollListWidget.h \
            GUI/Custom/CinemaButton.h \
            GUI/Custom/CinemaModifier.h \
            GUI/Custom/HorizontalCard.h \
            GUI/Custom/CustomMessageBox.h \
            GUI/Custom/ExpandableLabel.h \
            GUI/Custom/DetailsPageButtons.h \
            GUI/Custom/PreviewCard.h \
            GUI/MediaViewPages/DetailPageVisitor.h \
            GUI/MediaViewPages/FilmView.h \
            GUI/MediaViewPages/TrailerView.h \
            GUI/MediaViewPages/inserzioneView.h \
            GUI/MediaViewPages/PodcastView.h \
            GUI/MediaViewPages/PuntataView.h \
            GUI/MediaViewPages/MediaView.h \
            DataFiles/CinemaRepositoryJson.h \
            DataFiles/JsonConverter.h \
            DataFiles/JsonVisitor.h \
            DataFiles/MediaManagerXml.h \
            DataFiles/XmlVisitor.h \
            DataFiles/XmlReader.h
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
            test/test.cpp \
            GUI/MainWindow.cpp \
            GUI/CinemaSelectionPage.cpp \
            GUI/SearchPanel.cpp \
            GUI/InsertCinemaPage.cpp \
            GUI/Library/MediaLibraryGenerale.cpp \
            GUI/Library/MediaLibraryTutto.cpp \
            GUI/Library/UpdateMediaLibrary.cpp \
            GUI/Library/CardVisitor.cpp \
            GUI/MediaEditor/InsertMedia.cpp \
            GUI/MediaEditor/MediaInterface.cpp \
            GUI/MediaEditor/EditMedia.cpp \
            GUI/Custom/CinemaModifier.cpp \
            GUI/Custom/CinemaButton.cpp \
            GUI/Custom/ListPersone.cpp \
            GUI/Custom/InsertImageFrame.cpp \
            GUI/Custom/MediaFrame.cpp \
            GUI/Custom/SelectMediaReference.cpp \
            GUI/Custom/ScrollListWidget.cpp \
            GUI/Custom/FlowLayout.cpp \
            GUI/Custom/HorizontalCard.cpp \
            GUI/Custom/Menu.cpp \
            GUI/Custom/CustomMessageBox.cpp \
            GUI/Custom/ExpandableLabel.cpp \
            GUI/Custom/DetailsPageButtons.cpp \
            GUI/Custom/PreviewCard.cpp \
            GUI/MediaViewPages/DetailPageVisitor.cpp \
            GUI/MediaViewPages/MediaView.cpp \
            GUI/MediaViewPages/FilmView.cpp \
            GUI/MediaViewPages/inserzioneView.cpp \
            GUI/MediaViewPages/PodcastView.cpp \
            GUI/MediaViewPages/PuntataView.cpp \
            GUI/MediaViewPages/TrailerView.cpp \
            DataFiles/CinemaRepositoryJson.cpp \
            DataFiles/JsonConverter.cpp \
            DataFiles/JsonVisitor.cpp \
            DataFiles/MediaManagerXml.cpp \
            DataFiles/XmlVisitor.cpp \
            DataFiles/XmlReader.cpp
RESOURCES += GUI/resources.qrc
