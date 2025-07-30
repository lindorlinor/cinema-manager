#include "Podcast.h"
#include "Puntata.h"

Podcast::Podcast(    const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti, string& conduttore):
                    Media(autore, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, 
                    visualizzazioni, durataMinuti), p_conduttore(conduttore){};

void Podcast::aggiungiPuntata(Puntata* puntata){
    p_elencoPuntate.push_back(puntata);
}

void Podcast::rimuoviPuntata(Puntata* puntata){
    if (!p_elencoPuntate.empty()) {
        auto it = std::find(p_elencoPuntate.begin(), p_elencoPuntate.end(), puntata);
        if (it != p_elencoPuntate.end()) p_elencoPuntate.erase(it);
    }
}

double Podcast::calcolaIncasso(){
    double tot=0;
    for(auto puntata: p_elencoPuntate){
        tot+= puntata->calcolaIncasso();
    }
}

void Podcast::estendiDataFineRilascio(){
    if (!FuoriProduzione())
    {
        // Converti year_month_day a sys_days per sommare giorni
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        dataFine += std::chrono::days{7};                           // aggiungi 7 giorni
        setDataFineRilascio(std::chrono::year_month_day{dataFine}); // aggiorna
        
        for (auto puntata : p_elencoPuntate)
        {
            if (puntata && !(puntata->FuoriProduzione()))
            {
                puntata->estendiDataFineRilascio();
            }
        }
    }
} 
