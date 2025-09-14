#ifndef CARDVISITOR_H
#define CARDVISITOR_H

#include "../../MediaVisitor.h"
#include "../Custom/FlowLayout.h"
#include "../Custom/MediaFrame.h"
#include "../Custom/HorizontalCard.h"
#include "../../Film.h"
#include "../../Trailer.h"
#include "../../Inserzione.h"
#include "../../Podcast.h"
#include "../../Puntata.h"

class CardVisitor : public MediaVisitor
{

private:
    QWidget *library;
    const QString &filtro;
    MediaFrame *frame;
    HorizontalCard *card;
    bool vista;

public:
    explicit CardVisitor(QWidget *l, const QString &filter, const bool &view);

    void visit(Film *film) override;
    void visit(Trailer *trailer) override;
    void visit(Inserzione *inserzione) override;
    void visit(Podcast *podcast) override;
    void visit(Puntata *puntata) override;

    MediaFrame *getWidgetFrame() const;
    HorizontalCard *getWidgetCard() const;

    ~CardVisitor();
};

#endif // CARDVISITOR_H
