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
    FlowLayout* flow; 
    const QString& filtro; 
public:
    explicit FlowVisitor(QWidget* l, FlowLayout* f, const QString& filter);

    void visit(Film* film) override;
    void visit(Trailer* trailer) override;
    void visit(Inserzione* inserzione) override;
    void visit(Podcast* podcast) override;
    void visit(Puntata* puntata) override;

    ~FlowVisitor();
};

#endif // FLOWVISITOR_H
