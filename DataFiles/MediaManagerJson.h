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
/**
 * @brief Costruttore della classe MediaManagerJson.
 * @param basePath percorso base dove leggere/salvare i file JSON.
 */
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
        /**
         * @brief Carica tutti i film dal file films.json.
         * 
         * @return QList<FilmData> Lista dei film caricati.
         */
        QList<FilmData> loadFilms();
        QList<TrailerData> loadTrailers();
        QList<InserzioniData> loadInserzioni();
        QList<PodcastData> loadPodcast();
        QList<PuntataData> loadPuntate();

        //save
        /**
         * @brief Salva un nuovo film nel file films.json.
         * 
         * Carica i film esistenti, aggiunge il nuovo e riscrive il file.
         * 
         * @param film Dati del film da salvare.
         */
        void saveFilm(const FilmData &film);
        void saveTrailer(const TrailerData &trailer);
        void saveInserzione(const InserzioniData &inserzione);
        void savePodcast(const PodcastData &podcast);
        void savePuntata(const PuntataData &puntata); 

        /**
         * @brief Carica informazioni basilari (titolo, autore) da tutti i media.
         * 
         * Legge film, trailer, podcast, puntate e inserzioni e ne restituisce
         * solo i campi base.
         * 
         * @return QList<MediaData> Lista di media con dati essenziali.
         */
        QList<MediaData> loadAllMediaBasic();

    private:
        QString m_basePath;
        /**
         * @brief Salva i campi comuni di un contenuto multimediale in un oggetto JSON.
         * 
         * @param data Struttura MediaData (o derivata) da convertire in JSON.
         * @param obj Oggetto JSON da riempire con i dati.
         */
        void saveCommonFields(const MediaData &data, QJsonObject &obj);
        /**
         * @brief Carica i campi comuni di un contenuto multimediale da un oggetto JSON.
         * 
         * @param data Struttura MediaData (o derivata) da riempire.
         * @param obj Oggetto JSON da cui leggere i dati.
         */
        void loadCommonFields(MediaData &data, const QJsonObject &obj);
        /**
         * @brief Scrive un documento JSON su file.
         * 
         * @param fileName Nome del file JSON (relativo a m_basePath).
         * @param doc Documento JSON da salvare.
         */
        void saveJsonFile(const QString &filePath, const QJsonDocument &doc);
        /**
         * @brief Carica un documento JSON da file.
         * 
         * @param fileName Nome del file JSON (relativo a m_basePath).
         * @return QJsonDocument Documento JSON letto, vuoto se il file non è accessibile.
         */
        QJsonDocument loadJsonFile(const QString &fileName); 
};

#endif// MEDIAMANAGERJSON_H 
