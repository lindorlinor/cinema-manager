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


#include "SaveMediaVisitor.h"
#include "../Cinema.h"
#include "../Media.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

class CinemaManager{

    private:
    QString c_basePath;
    QJsonDocument loadJsonFile(const QString &fileName);

    void saveJsonFile(const QString &fileName, const QJsonDocument &doc);

    Film* createFilm(QJsonObject& obj);
    Trailer* createTrailer(QList<Media*>c_mediaList, QJsonObject& obj);
    Inserzione* createInserzione(QJsonObject& obj);
    Podcast* createPodcast(QJsonObject& obj);
    Puntata* createPuntata(QList<Media*>c_mediaList, QJsonObject& obj);

    year_month_day convertDate(const QString& data);
    void addLingue(Media* media, QJsonObject& obj);
    void addSottotitoli(Media* media, QJsonObject& obj);
    void addGeneri(Film* film, QJsonObject& obj);
    void addAttore(Film* film, QJsonObject& obj);
    void addOspite(Puntata* puntata, QJsonObject& obj);
    void addFasceOrarie(Inserzione* inserzione, QJsonObject& obj);
    Media* findMediaReference(const QString& cinema, const QString& titolo, const QString& autore, const QString& tipo, QList<Media*>c_mediaList);

    public:
    CinemaManager(const QString& basePath = QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"));

    void saveCinemaInJson(Cinema* c_cinema);
    void saveMediaInJson(Media* c_media);
    
    void loadCinema(QList<Cinema*>& c_cinemaList);
    void loadMedia(QList<Media*>& c_mediaList);

    void updateJson(QList<Cinema*> c_cinemaList, QList<Media*> c_mediaList);
    void updateJson(QList<Media*> c_mediaList);

    void deleteCinema(QList<Cinema*>& c_cinemaList, Cinema* cinema);
    void deleteMedia(QList<Media*>& c_mediaList, Media* media);
};


#endif // CINEMAMANAGER_H
