#include "Puntata.h"
#include "POdcast.h"

Puntata::Puntata(   const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti, const string& path, 
                    Formato formato, Podcast* podcast, unsigned int numeroPubblicita):
                    Media(autore, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, 
                    visualizzazioni, durataMinuti, path, formato), p_podcast(podcast),p_numeroPubblicita(numeroPubblicita){};

void Puntata::aggiungiOspite(const string& ospite){
    p_ospiti.push_back(ospite);
}
        
void Puntata::rimuoviOspite(const string& ospite) {
    if (!p_ospiti.empty()) {
        auto it = std::find(p_ospiti.begin(), p_ospiti.end(), ospite);
        if (it != p_ospiti.end()) p_ospiti.erase(it);
    }
}

double Puntata::calcolaIncasso(){
    return getVisualizzazioni()* (p_numeroPubblicita * 0.005); //5 centesimi per ogni visualizzazione si una pubblicità
}

void Puntata::estendiDataFineRilascio() {
    if (!FuoriProduzione() && p_podcast) {
        setDataFineRilascio(p_podcast->getDataFineRilascio());
    }
}
