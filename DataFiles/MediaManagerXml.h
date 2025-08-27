#ifndef MEDIAMANAGERXML_H
#define MEDIAMANAGERXML_H

#include <QString>
#include <QList>
#include <QDomDocument>

#include "Media.h"    
#include "Populate.h"  
#include "ConverterXml.h" 

class MediaManagerXml {
public:
    MediaManagerXml();

    void setCinemaName(const QString& name);
    void setCinemaCover(const QString& cover);
    void setCinemaMediaList(const QList<Media*>& mediaList);

    void exportSessionToXml();
    void exportMediaListToXml();

private:
    void createSessionDocument(QDomDocument& doc,QDomElement& root);
    void createMediaListDocument(QDomDocument& doc,QDomElement& root);
    void saveDocument();
    QDomDocument xmlDocument;
    QString cinemaName;
    QString cinemaCover;
    QList<Media*> mediaList;
};

#endif // MEDIAMANAGERXML_H
