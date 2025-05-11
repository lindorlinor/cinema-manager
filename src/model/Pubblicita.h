#ifndef PUBBLICITA_H
#define PUBBLICITA_H


#include <string>
#include "Media.h"

class Pubblicita: public Media{
private:
    Classificazione _target;
    unsigned int _nProiezioniGiornaliere;
    //piattaforme?
public:
    Pubblicita(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti, Classificazione target,unsigned int nProiezioniGiornaliere);
    Classificazione getTarget() const;
    void getTarget(Classificazione target);
};

#endif 

