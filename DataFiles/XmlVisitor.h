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
   
    QDomElement xmlElement;
    QDomDocument * doc;
    QDomElement populateCommonFields(const Media* media);
   

public:
    XmlVisitor(QDomDocument *d);
    ~XmlVisitor() = default;
    QDomElement getXmlElement() const;
    virtual void visit(Film* film) override;
    virtual void visit(Trailer* trailer) override;
    virtual void visit(Inserzione* inserzione) override;
    virtual void visit(Podcast* podcast) override;
    virtual void visit(Puntata* puntata) override;

    

};

#endif // XMLVISITOR_H
