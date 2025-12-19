#ifndef DETAILPAGEVISITOR_H
#define DETAILPAGEVISITOR_H

#include <QWidget>
#include "../../MediaVisitor.h"
#include "MediaView.h"
class MediaView;
class DetailPageVisitor : public MediaVisitor
{
private:
    MediaView *detailPage;

public:
    DetailPageVisitor();
    ~DetailPageVisitor() override = default;

    MediaView *getWidget() const;

    void visit(Film *film) override;
    void visit(Trailer *trailer) override;
    void visit(Inserzione *inserzione) override;
    void visit(Podcast *podcast) override;
    void visit(Puntata *puntata) override;
};

#endif // DETAILPAGEVISITOR_H
