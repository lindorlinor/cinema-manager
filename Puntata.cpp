#include "Puntata.h"
#include "POdcast.h"

Puntata::Puntata(   const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti, const string& path, 
                    Formato formato, Podcast* podcast, unsigned int numeroPubblicita):
                    Media(autore, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, 
                    visualizzazioni, durataMinuti, path, formato), p_podcast(podcast),p_numeroPubblicita(numeroPubblicita){};


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
        const vector<Puntata*>& elenco = p_podcast->getElencoPuntate();
        auto it = std::find(elenco.begin(), elenco.end(), this);
        while(it!=elenco.end()){
            auto dataFine = std::chrono::sys_days((*it)->getDataFineRilascio());
            dataFine += std::chrono::days{1};                           
            (*it)->setDataFineRilascio(std::chrono::year_month_day{dataFine}); 
            it++;
        }
        p_podcast->estendiDataFineRilascio();
    }
}

vector<string> Puntata::getOspiti() const{
    return p_ospiti;
};