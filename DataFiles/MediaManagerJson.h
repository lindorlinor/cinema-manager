#ifndef MEDIAMANAGERJSON_H
#define MEDIAMANAGERJSON_H

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDir>
#include <QFileInfo>

#include "Popolate.h"
#include "../MediaVisitor.h"

class MediaManagerJson : public QObject, public MediaVisitor{
    Q_OBJECT
    public:
        explicit MediaManagerJson(const QString& basePath);

        void visit(Film* film) override{};
        void visit(Trailer* trailer) override{};
        void visit(Inserzione* inserzione) override{};
        void visit(Podcast* podcast) override{};
        void visit(Puntata* puntata) override{};

        //load 
        QList<FilmData> loadFilms();
        /* QList<TrailerData> loadTrailers(); */
        QList<InserzioniData> loadInserzioni();
        QList<PodcastData> loadPodcast();
        /* QList<PuntataData> loadPuntata(); */

        //save
        void saveFilm(const FilmData &film);
        /* void saveTrailer(const TrailerData &trailer); */
        void saveInserzione(const InserzioniData &inserzione);
        void savePodcast(const PodcastData &podcast);
        /* void savePuntata(const PuntataData &puntata);  */

    private:
        QString m_basePath;

        void saveCommonFields(const MediaData &data, QJsonObject &obj);
        void loadCommonFields(MediaData &data, const QJsonObject &obj);
        void saveJsonFile(const QString &filePath, const QJsonDocument &doc);
        QJsonDocument loadJsonFile(const QString &fileName); 
};

#endif// MEDIAMANAGERJSON_H 
