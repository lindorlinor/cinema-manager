#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class Film;
class Trailer;
class Inserzione;
class Podcast;
class Puntata;

class MediaVisitor{
    public:
    virtual void visit(Film* film)=0;
    virtual void visit(Trailer* trailer) = 0;
    virtual void visit(Inserzione* inserzione) = 0;
    virtual void visit(Podcast* podcast) = 0;
    virtual void visit(Puntata* puntata) = 0;
    virtual ~MediaVisitor() = default;
};

#endif //MEDIAVISITOR_H