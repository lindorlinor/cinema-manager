#include "Puntata.h"
#include "POdcast.h"

Puntata::Puntata(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                 year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti,
                 Podcast *podcast, unsigned int numeroPubblicita, const string &autore,
                 const string &path) : 
                            Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                            durataMinuti, podcast->getFormato(), podcast->getRisoluzione(), autore, path),p_podcast(podcast), 
                            p_numeroPubblicita(numeroPubblicita) {
                                p_podcast->aggiungiPuntata(this);
                            }


int Puntata::isOspiteIn(const std::string& ospite) const {
    auto it = std::find(p_ospiti.begin(), p_ospiti.end(), ospite);
    if (it != p_ospiti.end()) {
        return std::distance(p_ospiti.begin(), it);
    } else {
        return -1;
    }
}

void Puntata::aggiungiOspite(const std::string& ospite) {
    if (isOspiteIn(ospite) == -1) {
        p_ospiti.push_back(ospite);
    }
}

        
void Puntata::rimuoviOspite(const std::string& ospite) {
    int i_ospite = isOspiteIn(ospite);
    if (i_ospite != -1) {
        p_ospiti.erase(p_ospiti.begin() + i_ospite);
    }
}


double Puntata::calcolaIncasso(){
    return getVisualizzazioni()* (p_numeroPubblicita * 0.05); //5 centesimi per ogni visualizzazione di una pubblicità
}


void Puntata::estendiDataFineRilascio() {
    if (!FuoriProduzione() && p_podcast) {
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        setDataFineRilascio(dataFine+days{1});
        p_podcast->aggiornaDate();
    }
}

void Puntata::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio){
    if(p_podcast){
        Media::setDataFineRilascio(gg_mm_aaFineRilascio);
        p_podcast->aggiornaDate();
    }
}

void Puntata::setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio){
    if(p_podcast){
        Media::setDataInizioRilascio(gg_mm_aaInizioRilascio);
        p_podcast->aggiornaDate();
    }
}

vector<string> Puntata::getOspiti() const
{
    return p_ospiti;
}

void Puntata::associaPodcast(Podcast* podcast){
    if(!podcast || p_podcast == podcast) return; 
    if(p_podcast){
        p_podcast->disaccoppiaPuntata(this);
    } 
    p_podcast = podcast;
    p_podcast->aggiungiPuntata(this);
} 

Podcast* Puntata::getPodcast()const{
    return p_podcast;
}

void Puntata::aggiungiLingua(Lingua lingua){
    Media::aggiungiLingua(lingua);
    p_podcast->aggiungiLingua(lingua);
}
void Puntata::aggiungiSottotitolo(Lingua lingua){
    Media::aggiungiSottotitolo(lingua);
    p_podcast->aggiungiSottotitolo(lingua);
}

//visitor
void Puntata::accept(MediaVisitor* visitor) {
    visitor->visit(this);
}