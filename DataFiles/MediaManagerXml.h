#ifndef MEDIAMANAGERXML_H
#define MEDIAMANAGERXML_H

#include <QString>
#include <QList>
#include <QDomDocument>

#include "Media.h"    
#include "Popolate.h"  
#include "ConverterXml.h" 

class MediaManagerXml {
public:
    MediaManagerXml();

    void setCinemaName(const QString& name);
    void setCinemaCover(const QString& cover);
    void setCinemaMediaList(const QList<Media*>& mediaList);

    void exportSessionToXml();

private:
    QDomDocument createDocument(); //to do
    void saveDocument(); //to do
    QDomDocument xmlDocument;
    QString cinemaName;
    QString cinemaCover;
    QList<Media*> mediaList;
};

#endif // MEDIAMANAGERXML_H
