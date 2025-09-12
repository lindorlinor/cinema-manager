#ifndef XMLREADER_H
#define XMLREADER_H
#include <QDomDocument>
#include <QDomElement>
#include "../Podcast.h"
#include "../Puntata.h"
#include "../Inserzione.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../MediaVisitor.h"
#include <list>
class XmlReader {
public:
    static Film* fromXmlFilmElement(const QDomElement& elem);
    static Trailer* fromXmlTrailerElement(const QDomElement& elem,list<Media*> mediaList);
    static Inserzione* fromXmlInserzioneElement(const QDomElement& elem);
    static Podcast* fromXmlPodcastElement(const QDomElement& elem);
    static Puntata* fromXmlPuntataElement(const QDomElement& elem,list<Media*> mediaList);

private:
    static void populateCommonFields(const QDomElement& elem, Media* media);
    static Film* findFilmInList(const list<Media*>& mediaList,const string& titolo, const string& autore);
    static Podcast* findPodcastInList(const list<Media*>& mediaList, const string& titolo,const string& autore);
};
#endif //XMLREADER_H