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
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"
/**
 * @brief Costruttore della classe MediaManagerJson.
 * @param basePath percorso base dove leggere/salvare i file JSON.
 */
class MediaManagerJson : public QObject, public MediaVisitor{
    Q_OBJECT
    public:
        explicit MediaManagerJson(const QString& basePath, QObject *parent = nullptr);

        void visit(Film* film) override{};
        void visit(Trailer* trailer) override{};
        void visit(Inserzione* inserzione) override{};
        void visit(Podcast* podcast) override{};
        void visit(Puntata* puntata) override{};

        /**
         * @brief Cancella tutti gli oggetti puntati dai puntatori nella lista e svuota la lista.
         * 
         * @param list Lista di puntatori a MediaData (o sue sottoclassi) da cancellare
         */
        void clearMediaList(QList<MediaData*>& list);


        //load Data
        /**
         * @brief Carica tutti i film dal file films.json come dati grezzi
         * 
         * @return QList<FilmData> Lista dei film caricati.
         */
        
        void loadFilmsData(QList<FilmData*>& films);
        void loadTrailersData(QList<TrailerData*>& trailers);
        void loadInserzioniData(QList<InserzioniData*>& inserzioni);
        void loadPodcastData(QList<PodcastData*>& podcasts);
        void loadPuntateData(QList<PuntataData*>& puntata);
        void loadCinemaData(QList<CinemaData*>& puntata);
        /* void loadAllDataAndCinema(QList<CinemaData*>& listMedia); */
        
        /**
        * @brief Carica tutti i media 
        * @note La lista risultante contiene puntatori che DEVONO essere distrutti dal chiamante
        */
        void loadAllData(QList<MediaData*>& media);
        
        //load Media
        /**
         * @brief Caricano i media con i dati ottenuti dalle struct Data
         * 
         * creano gli oggetti Media con i dati ottenuti dalle struct e li aggiungono alla lista m_mediaList
         */
        void loadFilms();
        void loadTrailers();
        void loadInserzioni();
        void loadPodcast();
        void loadPuntate();
        void loadAll();

        /**
         * @brief lista degli oggetti Media creatiù
         */
        QList<Media*>m_mediaList;


        //createMedia
        /**
         * @brief creano l'oggetto media
         * 
         * @return restituiscono l'oggetto media creato, per pooi metterlo nella QList m_mediaList
         */
        Film* createFilmFromData(const FilmData& data);
        Trailer* createTrailerFromData(const TrailerData& data);
        Inserzione* createInserzioneFromData(const InserzioniData& data);
        Podcast* createPodcastFromData(const PodcastData& data);
        Puntata* createPuntataFromData(const PuntataData& data);
        
        //findMedia
        /**
         * @brief Trova il film o il podcast di riferimento
         * 
         * Titolo e autore costituiscono un identificativo, vengono quindi passati alla funzione e viene fatta una ricerca sugli stessi
         * tra tutti gli oggetti Media presenti nella QList m_MediaList, l'oggetto corrispondente viene ritornato e sarà il media di riferimento
         * per trailer o puntata
         * 
         * @return Restituisce l'oggetto corrispondente alla ricerca effettuata
         */
        Media* findMedia(const QString& titolo, const QString& autore, const QString& tipo);


        //convertDate
        /**
         * @brief converte la data da QDate a year_month_day (chrono)
         * 
         * @return Restituisce la data in year_month_day
         */
        year_month_day convertDate(const QDate& data);

        //remove
        /**
         * @brief Elimina un oggetto passatogli
         * 
         */
        void remove(Media* media);

        //modified
        /**
         * @brief Modifica un oggetto passatogli
         * 
         * riceve in input il riferimento all'oggetto da modificare il puntatore all'oggetto struct modificato
         * 
         */
        void modified(Media& media, MediaData* data);
        
        //toMediaData
        /**
         * @brief converte un oggetto Media in un Data (struct)
         * 
         * riceve in input il riferimento all'oggetto da modificare, il riferimento all'oggetto da modificare nell'array ottenuto 
         * con il load del Json e il puntatore all'oggetto struct ottenuto dalle modifiche inserite
         * 
         */
        void updateFilm( Film& media, const FilmData* data);
        void updateTrailer( Trailer& media, const TrailerData* data);
        void updateInserzione( Inserzione& media, const InserzioniData* data);
        void updatePodcast( Podcast& media, const PodcastData* data);
        void updatePuntata( Puntata& media, const PuntataData* data);

        //updateCommonField
        /**
         * @brief aggiorna l'oggetto Media e il Json con le modifiche
         * 
         */
        void updateCommonField(Media& media, const MediaData *data);

        //clearMediaList
        /**
         * @brief Libera la memoria di tutti gli oggetti Media* nella lista m_mediList e la svuota
         * 
         */
        void clearMediaList();

        //save
        /**
         * @brief Salva un nuovo film nel file films.json.
         * 
         * Carica i film esistenti, aggiunge il nuovo e riscrive il file.
         * 
         * @param film Dati del film da salvare.
         */
        void saveMedia(MediaData* media);
        void saveList(QList<MediaData*>& mediaList);
        void saveFilm(FilmData* film, QJsonObject& obj);
        void saveTrailer(TrailerData* trailer, QJsonObject& obj);
        void saveInserzione(InserzioniData * inserzione, QJsonObject& obj);
        void savePodcast(PodcastData* podcast, QJsonObject& obj);
        void savePuntata(PuntataData* puntata, QJsonObject& obj); 
        void saveCinema(CinemaData* cinema); 

        /**
         * @brief ottiene il nome del cinema
         * 
         * il nome del cinema verrà utilizzato per importare solo i media relativi al cinema selezionato
         */
        void setNomeCinema(const QString& nome);

        ~MediaManagerJson();
        

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
