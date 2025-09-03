#ifndef XMLVISITOR_H
#define XMLVISITOR_H

#include <QDomDocument>
#include <QDomElement>
#include "../Podcast.h"
#include "../Puntata.h"
#include "../Inserzione.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../MediaVisitor.h"
#include <list>

class XmlVisitor :public MediaVisitor {
private:
    static void populateCommonFields(const QDomElement& elem, Media* media);
    QDomElement xmlElement;
    QDomDocument * doc;
    QDomElement populateCommonFields(const Media* media);
    static Film* findFilmInList(const list<Media*>& mediaList,const string& titolo, const string& autore);
    static Podcast* findPodcastInList(const list<Media*>& mediaList, const string& titolo,const string& autore);

public:
    XmlVisitor(QDomDocument *d);
    ~XmlVisitor() = default;
    QDomElement getXmlElement() const;
    virtual void visit(Film* film) override;
    virtual void visit(Trailer* trailer) override;
    virtual void visit(Inserzione* inserzione) override;
    virtual void visit(Podcast* podcast) override;
    virtual void visit(Puntata* puntata) override;

    static Film* fromXmlFilmElement(const QDomElement& elem,unsigned int&);
    static Trailer* fromXmlTrailerElement(const QDomElement& elem,list<Media*> mediaList);
    static Inserzione* fromXmlInserzioneElement(const QDomElement& elem);
    static Podcast* fromXmlPodcastElement(const QDomElement& elem);
    static Puntata* fromXmlPuntataElement(const QDomElement& elem,list<Media*> mediaList);

};

#endif // XMLVISITOR_H
