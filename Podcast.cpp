#include "Podcast.h"
#include "Puntata.h"

Podcast::Podcast(const string &titolo, const string &descrizione,
                 Formato formato, Risoluzione risoluzione,
                 const string &autore, const string &path, const string &conduttore) : 
                                    Media(titolo, descrizione, year_month_day{floor<days>(system_clock::now())}, 
                                    year_month_day{floor<days>(system_clock::now())},
                                    0, formato, risoluzione, autore, path),p_conduttore(conduttore) {
                                        setVisualizzazioni(0);
                                    }

Podcast::~Podcast(){
    for (auto& p : p_elencoPuntate) {
        delete p;
        p = nullptr;
    }
    p_elencoPuntate.clear();
}

string Podcast::getConduttore() const{
    return p_conduttore;
}

void Podcast::setConduttore(const string& nome){
    p_conduttore = nome;
}

void Podcast::aggiungiPuntata(Puntata* puntata){
    if(puntata && isPuntataIn(puntata)==-1 && puntata->getPodcast() == this){

        setVisualizzazioni(getVisualizzazioni() + puntata->getVisualizzazioni());
        setDurataMinuti(getDurataMinuti() + puntata->getDurataMinuti());
        p_elencoPuntate.push_back(puntata);

        aggiornaDate();
        for(Lingua l: puntata->getLingue()){
            aggiungiLingua(l);
        }
        for(Lingua l: puntata->getSottotitoli()){
            aggiungiSottotitolo(l);
        }
    }
}

 int Podcast::isPuntataIn(Puntata* puntata) const {
    auto it = std::find(p_elencoPuntate.begin(), p_elencoPuntate.end(), puntata);
    if (it != p_elencoPuntate.end()) {
        return std::distance(p_elencoPuntate.begin(), it);
    } else {
        return -1;
    }
}

void Podcast::rimuoviPuntata(Puntata* puntata) {
    int i_puntata = isPuntataIn(puntata);
    if (i_puntata != -1) {

        setVisualizzazioni(getVisualizzazioni() - puntata->getVisualizzazioni());
        setDurataMinuti(getDurataMinuti() - puntata->getDurataMinuti());
        delete puntata;

        p_elencoPuntate.erase(p_elencoPuntate.begin() + i_puntata);

        aggiornaDate();
    }
}

double Podcast::calcolaIncasso()
{
    double tot = 0;
    for (Puntata *puntata : p_elencoPuntate)
    {
        if (puntata)
            tot += puntata->calcolaIncasso();
    }
    return tot;
}

void Podcast::estendiDataFineRilascio(){
    if (!FuoriProduzione()) {
        for(auto it=p_elencoPuntate.begin(); it!=p_elencoPuntate.end(); it++)
            (*it)->estendiDataFineRilascio();
    }
    aggiornaDate();
}

vector<Puntata *> Podcast::getElencoPuntate() const
{
    return p_elencoPuntate;
}

void Podcast::disaccoppiaPuntata(Puntata* puntata){
    int i_puntata= isPuntataIn(puntata);
    if (i_puntata != -1) {
        p_elencoPuntate.erase(p_elencoPuntate.begin() + i_puntata);
        aggiornaDate();
        for(Lingua l : puntata->getLingue()){
            rimuoviLingua(l);
        }
        for(Lingua l : puntata->getSottotitoli()){
            rimuoviSottotitolo(l);
        }
    }
}

void Podcast::aggiornaDate(){
    if(!p_elencoPuntate.empty()){
        //trovo la puntata con la data di inizio rilascio minore
        auto minPuntata = std::min_element(p_elencoPuntate.begin(), p_elencoPuntate.end(),
            [](Puntata* a, Puntata* b) {
                return a->getDataInizioRilascio() < b->getDataInizioRilascio();
        });
        setDataInizioRilascio((*minPuntata)->getDataInizioRilascio());
    
        //trovo la puntata con la data di fine rilascio maggiore
        auto maxPuntata = std::max_element(p_elencoPuntate.begin(), p_elencoPuntate.end(),
            [](Puntata* a, Puntata* b) {
                return a->getDataFineRilascio() < b->getDataFineRilascio();
        });

        setDataFineRilascio((*maxPuntata)->getDataFineRilascio());
    }
}

void Podcast::aggiungiLingua(Lingua lingua) {
    for(Puntata* p: p_elencoPuntate){
        if(std::find(p->getLingue().begin(), p->getLingue().end(), lingua) != p->getLingue().end()){
            Media::aggiungiLingua(lingua);
            return;
        }
    }
}

void Podcast::aggiungiSottotitolo(Lingua lingua) {
    for(Puntata* p: p_elencoPuntate){
        if(std::find(p->getSottotitoli().begin(), p->getSottotitoli().end(), lingua) != p->getSottotitoli().end()){
            Media::aggiungiLingua(lingua);
            return;
        }
    }
}

void Podcast::rimuoviLingua(Lingua lingua) {
    for(Puntata* p: p_elencoPuntate){
        if(std::find(p->getLingue().begin(), p->getLingue().end(), lingua) != p->getLingue().end()){
            return;
        }
        else{
            Media::rimuoviLingua(lingua);
        }
    }
}

void Podcast::rimuoviSottotitolo(Lingua lingua) {
    for(Puntata* p: p_elencoPuntate){
        if(std::find(p->getSottotitoli().begin(), p->getSottotitoli().end(), lingua) != p->getSottotitoli().end()){
            return;
        }
        else{
            Media::rimuoviSottotitolo(lingua);
        }
    }
}

//visitor
void Podcast::accept(MediaVisitor* visitor) {
    visitor->visit(this);
}