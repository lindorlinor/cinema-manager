#ifndef MEDIAUPDATEVISITOR_H
#define MEDIAUPDATEVISITOR_H

#include "../MediaVisitor.h"
#include "Populate.h"

class MediaManagerJson;

class MediaUpdateVisitor : public MediaVisitor {

    private:
    MediaData* newData;   // i dati aggiornati
    MediaData* currentData; // riferimento ai dati originali
    MediaManagerJson* manager; 
public:
    explicit MediaUpdateVisitor(MediaData* newD, MediaData* currD, MediaManagerJson* m);

    void visit(Film* film) override;
    void visit(Trailer* trailer) override;
    void visit(Inserzione* inserzione) override;
    void visit(Podcast* podcast) override;
    void visit(Puntata* puntata) override;

    ~MediaUpdateVisitor();
};

#endif // MEDIAUPDATEVISITOR_H
