#ifndef FRMAEVISITOR_H
#define FRMAEVISITOR_H

#include <QJsonObject>

#include "MediaFrame.h"
#include "../MediaVisitor.h"
#include "../Media.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

class FrameVisitor : public MediaVisitor {

    private:
    Media* v_media;
    QWidget* v_container;
    MediaFrame* v_frame;
    QString v_filtro;

    public:
    explicit FrameVisitor(Media* media, QWidget* container, const QString& filtro);
    MediaFrame* getFrame();

    virtual void visit(Film* film) override;
    virtual void visit(Trailer* trailer) override;
    virtual void visit(Inserzione* inserzione) override;
    virtual void visit(Podcast* podcast) override;
    virtual void visit(Puntata* puntata) override;

    ~FrameVisitor();
};

#endif // FRMAEVISITOR_H
