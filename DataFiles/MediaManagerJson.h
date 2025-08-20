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
        QList<FilmData*> loadFilms();
        QList<TrailerData*> loadTrailers();
        QList<InserzioniData*> loadInserzioni();
        QList<PodcastData*> loadPodcast();
        QList<PuntataData*> loadPuntate();
        QList<MediaData*> loadAll();

        //save
        void saveFilm(FilmData* film);
        void saveTrailer(TrailerData* trailer);
        void saveInserzione(InserzioniData* inserzione);
        void savePodcast(PodcastData* podcast);
        void savePuntata(PuntataData* puntata); 

    private:
        QString m_basePath;

        void saveCommonFields(const MediaData &data, QJsonObject &obj);
        void loadCommonFields(MediaData &data, const QJsonObject &obj);
        void saveJsonFile(const QString &filePath, const QJsonDocument &doc);
        QJsonDocument loadJsonFile(const QString &fileName); 
};

#endif// MEDIAMANAGERJSON_H 
