#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonObject>

#include "../MediaVisitor.h"
#include "JsonConverter.h"

class JsonVisitor : public MediaVisitor {

    private:
    QJsonObject v_obj;
    Media* v_media;

    public:
    explicit JsonVisitor(Media* media);
    QJsonObject getObj();

    virtual void visit(Film* film) override;
    virtual void visit(Trailer* trailer) override;
    virtual void visit(Inserzione* inserzione) override;
    virtual void visit(Podcast* podcast) override;
    virtual void visit(Puntata* puntata) override;

    ~JsonVisitor();
};

#endif // JSONVISITOR_H
