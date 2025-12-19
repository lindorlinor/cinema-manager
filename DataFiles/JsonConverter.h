#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "../Cinema.h"    
#include "../Film.h"    
#include "../Trailer.h"    
#include "../Inserzione.h"    
#include "../Podcast.h"    
#include "../Puntata.h"    

class JsonConverter{

    private:
    QString cinemaName;
    year_month_day convertDate(const QString& data);
    void addLingue(Media* media, QJsonObject obj);
    void addSottotitoli(Media* media, QJsonObject obj);
    void addGeneri(Film* film, QJsonObject obj);
    void addAttore(Film* film, QJsonObject obj);
    void addOspite(Puntata* puntata, QJsonObject obj);
    void addFasceOrarie(Inserzione* inserzione, QJsonObject obj);
    Media* findMediaReference(const QString& titolo, const QString& autore, const QString& tipo, QList<Media*>c_mediaList);
    void saveCommonFields(const Media& media, QJsonObject &obj);

    public:
    JsonConverter(QString cName);
    QJsonObject serialize(Cinema* media);
    QJsonObject serialize(Film* media);
    QJsonObject serialize(Trailer* media);
    QJsonObject serialize(Inserzione* media);
    QJsonObject serialize(Podcast* media);
    QJsonObject serialize(Puntata* media);

    Cinema* deserializeCinema(QJsonObject obj);
    Film* deserializeFilm(QJsonObject obj);
    Trailer* deserializeTrailer(QList<Media*> c_mediaList, QJsonObject obj);
    Inserzione* deserializeInserzione(QJsonObject obj);
    Podcast* deserializePodcast(QJsonObject obj);
    Puntata* deserializePuntata(QList<Media*> c_mediaList, QJsonObject obj);
};

#endif // JSONCONVERTER_H
