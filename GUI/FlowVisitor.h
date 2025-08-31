#ifndef FLOWVISITOR_H
#define FLOWVISITOR_H

#include "../MediaVisitor.h"
#include "FlowLayout.h"
#include "MediaFrame.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"


class FlowVisitor : public MediaVisitor {

    private:
    QWidget* library; 
    const QString& filtro; 
    MediaFrame* frame;
public:
    explicit FlowVisitor(QWidget* l, const QString& filter);

    void visit(Film* film) override;
    void visit(Trailer* trailer) override;
    void visit(Inserzione* inserzione) override;
    void visit(Podcast* podcast) override;
    void visit(Puntata* puntata) override;

    MediaFrame* getWidget() const;

    ~FlowVisitor();
};

#endif // FLOWVISITOR_H
