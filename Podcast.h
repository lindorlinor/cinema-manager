#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"

class Puntata; //dichiarazione incompleta

class Podcast:public Media{
    private:
        string p_conduttore;
        vector<Puntata*> p_elencoPuntate;
    public:
        Podcast(    const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti, string& conduttore);

        void aggiungiPuntata(Puntata* puntata);
        void rimuoviPuntata(Puntata* puntata);

        void estendiDataFineRilascio() override; 
        double calcolaIncasso() override;
};

#endif //PODCAST_H