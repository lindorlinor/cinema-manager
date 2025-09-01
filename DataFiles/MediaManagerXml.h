#ifndef MEDIAMANAGERXML_H
#define MEDIAMANAGERXML_H

#include <QString>
#include <list>
#include <QDomDocument>

#include "../Media.h"
#include "CinemaRepositoryJson.h"
#include "../Cinema.h"

class MediaManagerXml {
public:
    MediaManagerXml();

    void setCurrentCinema(Cinema*);

    Cinema* getCurrentCinema() const;

    void exportSessionToXml();
    void exportMediaListToXml();

    bool importSessionFromXml(CinemaRepositoryJson& jsonManager);
    bool importMediaListFromXml(CinemaRepositoryJson& jsonManager);

private:
    void importMediaListFromXml(QDomElement& mediaElem, CinemaRepositoryJson& jsonManager,const string& cinemaName);
    void createSessionDocument(QDomDocument& doc,QDomElement& root);
    void createMediaListDocument(QDomDocument& doc,QDomElement& root);
    void saveDocument();
    QDomDocument xmlDocument;
    Cinema* currentCinema;
};

#endif // MEDIAMANAGERXML_H
