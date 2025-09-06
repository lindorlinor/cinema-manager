#ifndef CINEMAMANAGER_H
#define CINEMAMANAGER_H

#include <QList>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDate>
#include <QDate>
#include <chrono>
#include <vector>


#include "JsonVisitor.h"
#include "JsonConverter.h"
#include "../Cinema.h"
#include "../Media.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

class CinemaRepositoryJson{

    private:
    JsonConverter* converter;
    QString c_basePath;
    QJsonDocument loadJsonFile(const QString &fileName);

    void saveJsonFile(const QString &fileName, const QJsonDocument &doc);
    
    
    public:
    CinemaRepositoryJson(const QString& basePath = QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"));
    
    void deleteMediaPointer(QList<Media*>& c_mediaList);
    void saveCinemaInJson(Cinema* c_cinema);
    void saveMediaInJson(Media* c_media, const QString& nomeCinema);
    
    void loadCinema(QList<Cinema*>& c_cinemaList);
    void loadMedia(QList<Media*>& c_mediaList, const QString& nomeCinema);

    void deleteCinemaInJson(QList<Cinema*> c_cinemaList);
    void updateCinemaInJson(const QString& nomeCinemaVecchio, Cinema* cinemaAggiornato);
    void updateMediaInJson(Cinema* cinemaSelezionato);
};


#endif // CINEMAMANAGER_H
