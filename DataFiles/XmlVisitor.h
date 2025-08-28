#ifndef XMLVISITOR_H
#define XMLVISITOR_H
#include <QDomDocument>
#include "../MediaVisitor.h"

class XmlVisitor: public MediaVisitor{
private:
    QDomElement xmlElement;
    QDomDocument doc;
public:
    XmlVisitor(QDomDocument& d) : doc(d) {}
    virtual void visit(Film* film) override;
    virtual void visit(Trailer* trailer) override;
    virtual void visit(Inserzione* inserzione) override;
    virtual void visit(Podcast* podcast) override;
    virtual void visit(Puntata* puntata) override;
    QDomElement getXmlElement() const;
};
#endif