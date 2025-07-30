#ifndef PUNTATA_H
#define PUNTATA_H

#include "Media.h"

class Podcast;

class Puntata: public Media{
    private:
        vector<string> p_ospiti;
        Podcast* p_podcast;
        unsigned int p_numeroPubblicita;
    public:
        Puntata(    const string& autore, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzazioni, unsigned int durataMinuti,const string& path, 
                    Formato formato, Podcast* podcast, unsigned int numeroPubblicita);
        void aggiungiOspite(const string& ospite);
        void rimuoviOspite(const string& ospite);
        void estendiDataFineRilascio() override; 
        double calcolaIncasso() override;
};

#endif //PUNTATA_H