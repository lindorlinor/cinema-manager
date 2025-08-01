#ifndef PUBBLICITA_H
#define PUBBLICITA_H

#include <string>
#include "Media.h"

class Pubblicita : public Media
{
private:
    unsigned int p_nProiezioniGiornaliere;

public:
    Pubblicita(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
               year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
               unsigned int nProiezioniGiornaliere, const string &autore = "Sconosciuto", const string &path = "immGrigia");

    // Classificazione getTarget() const;
    unsigned int getNProiezioniGiornaliere() const;
    // void setTarget(Classificazione target);
};

#endif
