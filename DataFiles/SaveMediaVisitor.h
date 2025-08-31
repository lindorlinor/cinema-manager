#ifndef SAVEMEDIAVISITOR_H
#define SAVEMEDIAVISITOR_H

#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "../MediaVisitor.h"
#include "../Media.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

class CinemaManager;

class SaveMediaVisitor : public MediaVisitor {

    private:
    CinemaManager* manager;
    Media* v_media;
    QJsonObject* v_obj;

    void saveCommonFields(const Media* media, QJsonObject &obj);
    void saveList(QList<Media*>& mediaList);
    void saveFilm(Film* film, QJsonObject& obj);
    void saveTrailer(Trailer* trailer, QJsonObject& obj);
    void saveInserzione(Inserzione* inserzione, QJsonObject& obj);
    void savePodcast(Podcast* podcast, QJsonObject& obj);
    void savePuntata(Puntata* puntata, QJsonObject& obj);  

public:
    explicit SaveMediaVisitor(Media* media, QJsonObject* obj);

    void visit(Film* film) override;
    void visit(Trailer* trailer) override;
    void visit(Inserzione* inserzione) override;
    void visit(Podcast* podcast) override;
    void visit(Puntata* puntata) override;

    ~SaveMediaVisitor();
};

#endif // SAVEMEDIAVISITOR_H
