#include "Podcast.h"
#include "Puntata.h"

Podcast::Podcast(   const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti, const string& path, 
                    Formato formato, const string& conduttore):
                    Media(autore, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, 
                    visualizzazioni, durataMinuti, path, formato), p_conduttore(conduttore){}

Podcast::~Podcast(){
    while (!p_elencoPuntate.empty()) {
        delete p_elencoPuntate.back();
        p_elencoPuntate.pop_back();
    }
}

void Podcast::aggiungiPuntata(Puntata* puntata){
    if(puntata && !isInPuntata(puntata)){
        if(!p_elencoPuntate.empty())
            if(puntata->getDataFineRilascio() < p_elencoPuntate.back()->getDataFineRilascio()){
                throw std::invalid_argument("La data di fine è inferiore a quella dell'ultima puntata aggiunta");
        }
        setDataFineRilascio(puntata->getDataFineRilascio());
        setDurataMinuti(getDurataMinuti() + puntata->getDurataMinuti());
        p_elencoPuntate.push_back(puntata);
    }
}

bool Podcast::isInPuntata(Puntata * puntata) const{
    if (p_elencoPuntate.empty())
        return false;
    for (Puntata* p : p_elencoPuntate)
    {
        if (p == puntata)
            return true;
    }
    return false;
}

void Podcast::rimuoviPuntata(Puntata* puntata){
    if (!p_elencoPuntate.empty()) {
        auto it = std::find(p_elencoPuntate.begin(), p_elencoPuntate.end(), puntata);
        if (it != p_elencoPuntate.end()){
            setDurataMinuti(getDurataMinuti() - puntata->getDurataMinuti());
            p_elencoPuntate.erase(it);
            if(getDataFineRilascio() != p_elencoPuntate.back()->getDataFineRilascio())
                setDataFineRilascio(p_elencoPuntate.back()->getDataFineRilascio());
        } 
    }
}

double Podcast::calcolaIncasso(){
    double tot=0;
    for(Puntata* puntata: p_elencoPuntate){
        if(puntata)
            tot+= puntata->calcolaIncasso();
    }
    return tot;
}

void Podcast::estendiDataFineRilascio(){
    if (!FuoriProduzione())
    {
        // Converti year_month_day a sys_days per sommare giorni
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        dataFine += std::chrono::days{7};                           // aggiungi 7 giorni
        setDataFineRilascio(std::chrono::year_month_day{dataFine}); // aggiorna

        //non ha alcuna azione sulle puntate perché la data di fine rilascio del podcast dipende da quella
        //di fine rilascio delle stesse puntate, quindi non è possibile estendere la fine del podcast senza 
        //prima estendere quella delle puntate, il quale metodo richiama questo stesso metodo per aggiornare
        // la data di fine rilascio del podcast
    }
} 

vector<Puntata*> Podcast::getElencoPuntate()const{
    return p_elencoPuntate;
}

