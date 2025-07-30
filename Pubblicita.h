#ifndef PUBBLICITA_H
#define PUBBLICITA_H

#include <string>
#include "Media.h"

class Pubblicita : public Media
{
private:
    Classificazione p_target;
    unsigned int p_nProiezioniGiornaliere;

public:
    Pubblicita(     const string &autore, const string &titolo, const string &descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzaioni, unsigned int durataMinuti, Classificazione target, 
                    unsigned int nProiezioniGiornaliere);

    // Classificazione getTarget() const;
    unsigned int getNProiezioniGiornaliere() const; //TO DO
    // void setTarget(Classificazione target);
};

#endif
