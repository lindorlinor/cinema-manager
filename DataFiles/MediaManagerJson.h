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
#include <QApplication>

#include "Populate.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"
/**
 * @brief Costruttore della classe MediaManagerJson.
 * @param basePath percorso base dove leggere/salvare i file JSON.
 */

class MediaUpdateVisitor;

class MediaManagerJson : public QObject{
    Q_OBJECT
    public:
        explicit MediaManagerJson(QList<Media*>& mediaList, const QString& basePath = QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"), QObject *parent = nullptr);

        //convertDate
        /**
         * @brief converte la data da QDate a year_month_day (chrono)
         * 
         * @return Restituisce la data in year_month_day
         */
        year_month_day convertDate(const QDate& data);

        /**
        * @brief carica tutti i cinema nel Json
        */
        void loadCinemaData(QList<CinemaData*>& puntata);
        
        /**
        * @brief Carica tutti i media 
        * @note La lista risultante contiene puntatori che DEVONO essere distrutti dal chiamante
        */
        void loadAllData(QList<MediaData*>& media);
        
        /**
        * @brief Crea tutti gli oggetti contenuti nel Json del rispettivo cinema chiamato
        */
        void loadAll();

        /**
        * @brief Elimina tutti gli oggetti creati
        */
        void removeAll();

        //remove
        /**
         * @brief Elimina un oggetto passatogli
         * 
         */
        void removeMedia(Media* media);

        //modified
        /**
         * @brief Modifica un oggetto passatogli
         * 
         * riceve in input il riferimento all'oggetto da modificare il puntatore all'oggetto struct modificato
         * 
         */
        void modified(Media& media, MediaData* data);
    

        //updateCommonField
        /**
         * @brief aggiorna l'oggetto Media e il Json con le modifiche
         * 
         */
        void updateCommonField(Media& media, const MediaData *data);

        //saveMedia
        /**
         * @brief Salva un nuovo media nel file films.json.
         * 
         * Carica i film esistenti, aggiunge il nuovo e riscrive il file.
         * 
         * @param film Dati del film da salvare.
         */
        void saveMedia(MediaData* media);
        
        //saveCinema
        /**
         * @brief salva il nuovo cinema inserito nel Json
         */

        void saveCinema(CinemaData* cinema);

        void getCinemaNome(const QString& nomeCinema);
        

    private:
        QString m_basePath;
        QList<Media*>& mediaList;
        QString cinemaAttuale;

        //load Data
        /**
         * @brief Carica tutti i media dal file media.json come dati grezzi
         */
        
        void loadFilmsData(QList<FilmData*>& films);
        void loadTrailersData(QList<TrailerData*>& trailers);
        void loadInserzioniData(QList<InserzioneData*>& inserzioni);
        void loadPodcastData(QList<PodcastData*>& podcasts);
        void loadPuntateData(QList<PuntataData*>& puntata);

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

        //createMedia
        /**
         * @brief creano l'oggetto media
         * 
         * @return restituiscono l'oggetto media creato, per pooi metterlo nella QList m_mediaList
         */
        Film* createFilmFromData(const FilmData& data);
        Trailer* createTrailerFromData(const TrailerData& data);
        Inserzione* createInserzioneFromData(const InserzioneData& data);
        Podcast* createPodcastFromData(const PodcastData& data);
        Puntata* createPuntataFromData(const PuntataData& data);
        void createMedia(const MediaData& data);

        //findMediaReference
        /**
         * @brief Trova il film o il podcast di riferimento
         * 
         * Titolo e autore costituiscono un identificativo, vengono quindi passati alla funzione e viene fatta una ricerca sugli stessi
         * tra tutti gli oggetti Media presenti nella QList m_MediaList, l'oggetto corrispondente viene ritornato e sarà il media di riferimento
         * per trailer o puntata
         * 
         * @return Restituisce l'oggetto corrispondente alla ricerca effettuata
         */
        Media* findMediaReference(const QString& titolo, const QString& autore, const QString& tipo);

        /**
         * @brief salvano i nuovi oggetti nel json e li creano
         */
        void saveList(QList<MediaData*>& mediaList);
        void saveFilm(FilmData* film, QJsonObject& obj);
        void saveTrailer(TrailerData* trailer, QJsonObject& obj);
        void saveInserzione(InserzioneData * inserzione, QJsonObject& obj);
        void savePodcast(PodcastData* podcast, QJsonObject& obj);
        void savePuntata(PuntataData* puntata, QJsonObject& obj);  

        //update
        /**
         * @brief aggiorna gli oggetti e il json
         * 
         * riceve in input il riferimento all'oggetto da modificare, il riferimento all'oggetto da modificare nell'array ottenuto 
         * con il load del Json e il puntatore all'oggetto struct ottenuto dalle modifiche inserite
         * 
         */
        void updateFilm( Film& media, const FilmData* data);
        void updateTrailer( Trailer& media, const TrailerData* data);
        void updateInserzione( Inserzione& media, const InserzioneData* data);
        void updatePodcast( Podcast& media, const PodcastData* data);
        void updatePuntata( Puntata& media, const PuntataData* data);

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

        friend class MediaUpdateVisitor;
};

#endif// MEDIAMANAGERJSON_H 
