#include "Puntata.h"
#include "POdcast.h"

Puntata::Puntata(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                 year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti,
                 Podcast *podcast, unsigned int numeroPubblicita, const string &autore,
                 const string &path) : 
                            Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                            durataMinuti, podcast->getFormato(), podcast->getRisoluzione(), autore, path),p_podcast(podcast), 
                            p_numeroPubblicita(numeroPubblicita) {}


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
        IteraModificaDataFineRilascioPuntate(1);
        p_podcast->estendiDataFineRilascio();
    }
}

void Puntata::IteraModificaDataFineRilascioPuntate(int n){
    const vector<Puntata*>& elenco = p_podcast->getElencoPuntate();
    auto it = std::find(elenco.begin(), elenco.end(), this);

    while (it != elenco.end()){
            auto dataFine = std::chrono::sys_days((*it)->getDataFineRilascio());
            dataFine += std::chrono::days{n};                           
            (*it)->Media::setDataFineRilascio(std::chrono::year_month_day{dataFine}); 
            it++;
    }
}

void Puntata::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio){
    if(p_podcast){
        sys_days prima = getDataFineRilascio();
        sys_days dopo = gg_mm_aaFineRilascio;
        int giorni = (dopo-prima).count();
        IteraModificaDataFineRilascioPuntate(giorni);
        //non faccio il controllo per vedere se ci sono effettivamente delle puntate perché
        //questo richiamo avviene perché si sta modificando una puntata
        year_month_day nuova_data = p_podcast->getElencoPuntate().back()->getDataFineRilascio();
        p_podcast->setDataFineRilascio(nuova_data);
    }
}

vector<string> Puntata::getOspiti() const
{
    return p_ospiti;
};