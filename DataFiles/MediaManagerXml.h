#ifndef MEDIAMANAGERXML_H
#define MEDIAMANAGERXML_H

#include <QString>
#include <QList>
#include <QDomDocument>

#include "Media.h"    
#include "Populate.h"  
#include "MediaManagerJson.h"

class MediaManagerXml {
public:
    MediaManagerXml();

    void setCinemaName(const QString& name);
    void setCinemaCover(const QString& cover);
    void setCinemaMediaList(const QList<Media*>& mediaList);

    const QString& getCinemaName() const; //to do
    const QString& getCinemaCover() const; //to do
    const QList<Media*>& getCinemaMediaList() const; //to do

    void exportSessionToXml();
    void exportMediaListToXml();

    bool importSessionFromXml(MediaManagerJson& jsonManager);
    bool importMediaListFromXml(MediaManagerJson& jsonManager);

private:
    void importMediaListFromXml(QDomElement& mediaElem, MediaManagerJson& jsonManager,const QString& cinemaName, const QString& cinemaCover);
    void createSessionDocument(QDomDocument& doc,QDomElement& root);
    void createMediaListDocument(QDomDocument& doc,QDomElement& root);
    void saveDocument();
    QDomDocument xmlDocument;
    QString cinemaName;
    QString cinemaCover;
    QList<Media*> mediaList;
};

#endif // MEDIAMANAGERXML_H
