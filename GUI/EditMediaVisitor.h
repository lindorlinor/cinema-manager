#ifndef EDITMEDIAVISITOR_H
#define EDITMEDIAVISITOR_H

#include "../MediaVisitor.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"


class EditMediaVisitor : public MediaVisitor {

private:
    int index;

public:
    explicit EditMediaVisitor();

    void visit(Film* film) override;
    void visit(Trailer* trailer) override;
    void visit(Inserzione* inserzione) override;
    void visit(Podcast* podcast) override;
    void visit(Puntata* puntata) override;

    int getIndex() const;

    ~EditMediaVisitor();
};

#endif // EDITMEDIAVISITOR_H
